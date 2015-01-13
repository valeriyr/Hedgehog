
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iplayer_component.hpp"

#include "xml_library/sources/rules/xl_tag_rule.hpp"
#include "xml_library/sources/rules/xl_attribute_rule.hpp"
#include "xml_library/sources/rules/xl_cdata_rule.hpp"
#include "xml_library/sources/visitors/xl_xml_parser.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeSerializer::LandscapeSerializer()
{
} // LandscapeSerializer::LandscapeSerializer


/*---------------------------------------------------------------------------*/


LandscapeSerializer::~LandscapeSerializer()
{
} // LandscapeSerializer::~LandscapeSerializer


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::load( ILandscape& _landscape, const QString& _filePath )
{
	QFile file( _filePath );
	if ( !file.open( QIODevice::ReadOnly ) )
		throw std::exception();

	Tools::Core::XmlLibrary::Tag rule
		=
		Tools::Core::XmlLibrary::Tag( Resources::Xml::HMap )
		[
				Tools::Core::XmlLibrary::Attribute( Resources::Xml::Version, Tools::Core::XmlLibrary::AttributeType::String )
			&&
				Tools::Core::XmlLibrary::Attribute( Resources::Xml::Width, Tools::Core::XmlLibrary::AttributeType::Integer )
			&&
				Tools::Core::XmlLibrary::Attribute( Resources::Xml::Height, Tools::Core::XmlLibrary::AttributeType::Integer )
		]
		[
				Tools::Core::XmlLibrary::Tag( Resources::Xml::Surface )
				[
					Tools::Core::XmlLibrary::CDATA()
				]
				.handle(
						boost::bind( &LandscapeSerializer::onSurfaceElement, this, boost::ref( _landscape ), _1 )
					,	Tools::Core::XmlLibrary::CDATAExtructor()
					)
			||
				Tools::Core::XmlLibrary::Tag( Resources::Xml::StartPoints )
				[
					+Tools::Core::XmlLibrary::Tag( Resources::Xml::StartPoint )
					[
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Id, Tools::Core::XmlLibrary::AttributeType::Integer )
						&&
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::X, Tools::Core::XmlLibrary::AttributeType::Integer )
						&&
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Y, Tools::Core::XmlLibrary::AttributeType::Integer )
					]
					.handle(
							boost::bind( &LandscapeSerializer::onStartPoint, this, boost::ref( _landscape ), _1, _2, _3 )
						,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Id )
						,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::X )
						,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Y )
						)
				]
		]
		.handle(
				boost::bind( &LandscapeSerializer::onHMapElement, this, boost::ref( _landscape ), _1, _2, _3 )
			,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Version )
			,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Width )
			,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Height )
			);

	Tools::Core::XmlLibrary::Parser::parse( *rule.getElement(), file );

} // LandscapeSerializer::load


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::loadObjects( const ILandscapeModel& _landscapeModel, ILandscape& _landscape, const QString& _filePath )
{
	QFile file( _filePath );
	if ( !file.open( QIODevice::ReadOnly ) )
		throw std::exception();

	Tools::Core::XmlLibrary::Tag rule
		=
		Tools::Core::XmlLibrary::Tag( Resources::Xml::HMap )
		[
				*Tools::Core::XmlLibrary::Tag( Resources::Xml::Objects )
				[
						+Tools::Core::XmlLibrary::Tag( Resources::Xml::Object )
						[
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Name, Tools::Core::XmlLibrary::AttributeType::String )
						]
						[
								Tools::Core::XmlLibrary::Tag( Resources::Xml::Location )
								[
										Tools::Core::XmlLibrary::Attribute( Resources::Xml::X, Tools::Core::XmlLibrary::AttributeType::Integer )
									&&
										Tools::Core::XmlLibrary::Attribute( Resources::Xml::Y, Tools::Core::XmlLibrary::AttributeType::Integer )
								]
							||
								Tools::Core::XmlLibrary::Tag( Resources::Xml::StartPoint )
								[
									Tools::Core::XmlLibrary::Attribute( Resources::Xml::Id, Tools::Core::XmlLibrary::AttributeType::Integer )
								]
						]
						.handle(
									boost::bind( &LandscapeSerializer::onObjectElement, this, boost::ref( _landscapeModel ), boost::ref( _landscape ), _1, _2, _3, _4 )
								,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Name )
								,	Tools::Core::XmlLibrary::ChildTagIntAttributeExtructor( Resources::Xml::Location, Resources::Xml::X )
								,	Tools::Core::XmlLibrary::ChildTagIntAttributeExtructor( Resources::Xml::Location, Resources::Xml::Y )
								,	Tools::Core::XmlLibrary::ChildTagIntAttributeExtructor( Resources::Xml::StartPoint, Resources::Xml::Id )
								)
				]
		];

	Tools::Core::XmlLibrary::Parser::parse( *rule.getElement(), file );

} // LandscapeSerializer::loadObjects


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::save( const ILandscapeModel& _landscapeModel, const ILandscape& _landscape, const QString& _filePath ) const
{
	QFileInfo fileInfo( _filePath );
	if ( !fileInfo.absoluteDir().mkpath(".") )
		throw std::exception();

	QFile file( _filePath );

	if ( !file.open( QIODevice::WriteOnly ) )
		throw std::exception();

	QXmlStreamWriter xmlStream( &file );
	xmlStream. setAutoFormatting( true );

	xmlStream.writeStartDocument();

    xmlStream.writeDTD( Resources::Xml::LandscapeDocTypeString );

    xmlStream.writeStartElement( Resources::Xml::HMap );

	xmlStream.writeAttribute( Resources::Xml::Version, Resources::LandscapeVersion );
	xmlStream.writeAttribute( Resources::Xml::Width, QString::number( _landscape.getWidth() ) );
	xmlStream.writeAttribute( Resources::Xml::Height, QString::number( _landscape.getHeight() ) );

	xmlStream.writeStartElement( Resources::Xml::Surface );

	QString surfaceData;

	for ( int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			if ( !surfaceData.isEmpty() )
				surfaceData += " ";
			surfaceData += QString::number( _landscape.getSurfaceItem( QPoint( i, j ) )->getId() );
		}
	}

	// xmlStream.writeCDATA( QString( qCompress( surfaceData.toUtf8(), 9 ) ) );
	xmlStream.writeCDATA( surfaceData );

	xmlStream.writeEndElement();

	xmlStream.writeStartElement( Resources::Xml::StartPoints );

	ILandscape::StartPointsIterator startPoints = _landscape.getStartPointsIterator();

	while( startPoints->isValid() )
	{
		xmlStream.writeStartElement( Resources::Xml::StartPoint );

		xmlStream.writeAttribute( Resources::Xml::Id, QString::number( startPoints->current().getMember< Tools::Core::Generators::IGenerator::IdType >( StartPoint::ms_id ) ) );
		xmlStream.writeAttribute( Resources::Xml::X, QString::number( startPoints->current().getMember< QPoint >( StartPoint::ms_point ).x() ) );
		xmlStream.writeAttribute( Resources::Xml::Y, QString::number( startPoints->current().getMember< QPoint >( StartPoint::ms_point ).y() ) );

		xmlStream.writeEndElement();

		startPoints->next();
	}

	xmlStream.writeEndElement();

	xmlStream.writeStartElement( Resources::Xml::Objects );

	xmlStream.writeAttribute( Resources::Xml::Count, QString::number( _landscape.getObjectsCount() ) );

	ILandscape::ObjectsCollection objectsCollection;
	_landscape.fetchObjects( objectsCollection );

	ILandscape::ObjectsCollectionIterator
			begin = objectsCollection.begin()
		,	end = objectsCollection.end();

	for ( ; begin != end; ++begin )
	{
		boost::intrusive_ptr< ILocateComponent > locateComponent
			= ( *begin )->getComponent< ILocateComponent >( ComponentId::Locate );
		boost::intrusive_ptr< IPlayerComponent > playerComponent
			= ( *begin )->getComponent< IPlayerComponent >( ComponentId::Player );

		xmlStream.writeStartElement( Resources::Xml::Object );

		xmlStream.writeAttribute( Resources::Xml::Name, ( *begin )->getMember< QString >( ObjectNameKey ) );

		xmlStream.writeStartElement( Resources::Xml::Location );

		xmlStream.writeAttribute( Resources::Xml::X, QString::number( locateComponent->getLocation().x() ) );
		xmlStream.writeAttribute( Resources::Xml::Y, QString::number( locateComponent->getLocation().y() ) );

		xmlStream.writeEndElement();

		if ( playerComponent )
		{
			xmlStream.writeStartElement( Resources::Xml::StartPoints );

			xmlStream.writeAttribute( Resources::Xml::Id, QString::number( _landscapeModel.getPlayer( playerComponent->getPlayerId() )->getStartPointId() ) );

			xmlStream.writeEndElement();
		}

		xmlStream.writeEndElement();
	}

	xmlStream.writeEndElement();
	xmlStream.writeEndElement();

	xmlStream.writeEndDocument();

} // LandscapeSerializer::save


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onHMapElement( ILandscape& _landscape, const QString& _version, const int _width, const int _height )
{
	if ( _version != Resources::LandscapeVersion )
		throw std::exception();

	_landscape.setSize( _width, _height );

} // LandscapeSerializer::onHMapElement


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onSurfaceElement( ILandscape& _landscape, const QString& _data )
{
	std::string data( _data.toLocal8Bit().data() );

	QStringList surfaceItems( _data.split( " " ) );

	for ( int i = 0; i < _landscape.getHeight(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			_landscape.setSurfaceItem( QPoint( i, j ), surfaceItems.front().toInt() );
			surfaceItems.pop_front();
		}
	}

} // LandscapeSerializer::onSurfaceElement


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onObjectElement(
		const ILandscapeModel& _landscapeModel
	,	ILandscape& _landscape
	,	const QString& _name
	,	const int _x
	,	const int _y
	,	const Tools::Core::Generators::IGenerator::IdType& _id )
{
	if ( _id == INT_MAX )
	{
		_landscape.createObject( _name, QPoint( _x, _y ), Tools::Core::Generators::IGenerator::ms_wrongId );
	}
	else
	{
		boost::intrusive_ptr< IPlayer > player = _landscapeModel.getPlayerByStartPoint( _id );

		if ( player && PlayerType::isActivated( player->getType() ) )
			_landscape.createObject( _name, QPoint( _x, _y ), player->getUniqueId() );
	}

} // LandscapeSerializer::onObjectElement


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onStartPoint( ILandscape& _landscape, const Tools::Core::Generators::IGenerator::IdType& _id, const int _x, const int _y )
{
	Tools::Core::Object startPoint;

	startPoint
		.pushMember( StartPoint::ms_id, _id )
		.pushMember( StartPoint::ms_point, QPoint( _x, _y ) );

	_landscape.addStartPoint( startPoint );

} // LandscapeSerializer::onStartPoint


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
