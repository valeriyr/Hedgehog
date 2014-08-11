
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
	:	m_currentLoadLandscape( NULL )
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

	m_currentLoadLandscape = &_landscape;

	Tools::Core::XmlLibrary::Tag rule
		=
		Tools::Core::XmlLibrary::Tag( Resources::HMapTagName )
			[
					Tools::Core::XmlLibrary::Attribute( Resources::VersionAttributeName, Tools::Core::XmlLibrary::AttributeType::String )
				&&
					Tools::Core::XmlLibrary::Attribute( Resources::WidthAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
				&&
					Tools::Core::XmlLibrary::Attribute( Resources::HeightAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
			]
			[
					Tools::Core::XmlLibrary::Tag( Resources::SurfaceTagName )
					[
						Tools::Core::XmlLibrary::CDATA()
					]
					.handle(
							boost::bind( &LandscapeSerializer::onSurfaceElement, this, _1 )
						,	Tools::Core::XmlLibrary::CDATAExtructor()
						)
				||
					Tools::Core::XmlLibrary::Tag( Resources::StartPointsTagName )
					[
						+Tools::Core::XmlLibrary::Tag( Resources::StartPointTagName )
						[
								Tools::Core::XmlLibrary::Attribute( Resources::IdAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
							&&
								Tools::Core::XmlLibrary::Attribute( Resources::XAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
							&&
								Tools::Core::XmlLibrary::Attribute( Resources::YAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
						]
						.handle(
								boost::bind( &LandscapeSerializer::onStartPoint, this, _1, _2, _3 )
							,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::IdAttributeName )
							,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::XAttributeName )
							,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::YAttributeName )
							)
					]
			]
			.handle(
					boost::bind( &LandscapeSerializer::onHMapElement, this, _1, _2, _3 )
				,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::VersionAttributeName )
				,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::WidthAttributeName )
				,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::HeightAttributeName )
				)
			.postHandle( boost::bind( &LandscapeSerializer::onFinishParsing, this ) );

	Tools::Core::XmlLibrary::Parser::parse( *rule.getElement(), file );

} // LandscapeSerializer::load


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::loadObjects( const ILandscapeModel& _landscapeModel, ILandscape& _landscape, const QString& _filePath )
{
	QFile file( _filePath );
	if ( !file.open( QIODevice::ReadOnly ) )
		throw std::exception();

	m_currentLoadLandscape = &_landscape;

	Tools::Core::XmlLibrary::Tag rule
		=
		Tools::Core::XmlLibrary::Tag( Resources::HMapTagName )
			[
					*Tools::Core::XmlLibrary::Tag( Resources::ObjectsTagName )
					[
							+Tools::Core::XmlLibrary::Tag( Resources::ObjectTagName )
							[
								Tools::Core::XmlLibrary::Attribute( Resources::NameAttributeName, Tools::Core::XmlLibrary::AttributeType::String )
							]
							[
									Tools::Core::XmlLibrary::Tag( Resources::LocationTagName )
									[
											Tools::Core::XmlLibrary::Attribute( Resources::XAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
										&&
											Tools::Core::XmlLibrary::Attribute( Resources::YAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
									]
								||
									Tools::Core::XmlLibrary::Tag( Resources::StartPointTagName )
									[
										Tools::Core::XmlLibrary::Attribute( Resources::IdAttributeName, Tools::Core::XmlLibrary::AttributeType::Integer )
									]
							]
							.handle(
										boost::bind( &LandscapeSerializer::onObjectElement, this, boost::ref( _landscapeModel ), _1, _2, _3, _4 )
									,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::NameAttributeName )
									,	Tools::Core::XmlLibrary::ChildTagIntAttributeExtructor( Resources::LocationTagName, Resources::XAttributeName )
									,	Tools::Core::XmlLibrary::ChildTagIntAttributeExtructor( Resources::LocationTagName, Resources::YAttributeName )
									,	Tools::Core::XmlLibrary::ChildTagIntAttributeExtructor( Resources::StartPointTagName, Resources::IdAttributeName )
									)
					]
			]
			.postHandle( boost::bind( &LandscapeSerializer::onFinishParsing, this ) );

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

    xmlStream.writeDTD( Resources::DocTypeString );

    xmlStream.writeStartElement( Resources::HMapTagName );

	xmlStream.writeAttribute( Resources::VersionAttributeName, Resources::LandscapeVersion );
	xmlStream.writeAttribute( Resources::WidthAttributeName, QString::number( _landscape.getWidth() ) );
	xmlStream.writeAttribute( Resources::HeightAttributeName, QString::number( _landscape.getHeight() ) );

	xmlStream.writeStartElement( Resources::SurfaceTagName );

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

	xmlStream.writeStartElement( Resources::StartPointsTagName );

	ILandscape::StartPointsIterator startPoints = _landscape.getStartPointsIterator();

	while( startPoints->isValid() )
	{
		xmlStream.writeStartElement( Resources::StartPointTagName );

		xmlStream.writeAttribute( Resources::IdAttributeName, QString::number( startPoints->current().m_id ) );
		xmlStream.writeAttribute( Resources::XAttributeName, QString::number( startPoints->current().m_point.x() ) );
		xmlStream.writeAttribute( Resources::YAttributeName, QString::number( startPoints->current().m_point.y() ) );

		xmlStream.writeEndElement();

		startPoints->next();
	}

	xmlStream.writeEndElement();

	xmlStream.writeStartElement( Resources::ObjectsTagName );

	xmlStream.writeAttribute( Resources::CountAttributeName, QString::number( _landscape.getObjectsCount() ) );

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

		xmlStream.writeStartElement( Resources::ObjectTagName );

		xmlStream.writeAttribute( Resources::NameAttributeName, ( *begin )->getName() );

		xmlStream.writeStartElement( Resources::LocationTagName );

		xmlStream.writeAttribute( Resources::XAttributeName, QString::number( locateComponent->getLocation().x() ) );
		xmlStream.writeAttribute( Resources::YAttributeName, QString::number( locateComponent->getLocation().y() ) );

		xmlStream.writeEndElement();

		if ( playerComponent )
		{
			xmlStream.writeStartElement( Resources::StartPointsTagName );

			xmlStream.writeAttribute( Resources::IdAttributeName, QString::number( _landscapeModel.getPlayer( playerComponent->getPlayerId() )->getStartPointId() ) );

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
LandscapeSerializer::onHMapElement( const QString& _version, const int _width, const int _height )
{
	assert( m_currentLoadLandscape );

	if ( _version != Resources::LandscapeVersion )
	{
		m_currentLoadLandscape = NULL;
		throw std::exception();
	}

	m_currentLoadLandscape->setSize( _width, _height );

} // LandscapeSerializer::onHMapElement


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onSurfaceElement( const QString& _data )
{
	std::string data( _data.toLocal8Bit().data() );
	assert( m_currentLoadLandscape );

	QStringList surfaceItems( _data.split( " " ) );

	for ( int i = 0; i < m_currentLoadLandscape->getHeight(); ++i )
	{
		for ( int j = 0; j < m_currentLoadLandscape->getHeight(); ++j )
		{
			m_currentLoadLandscape->setSurfaceItem( QPoint( i, j ), surfaceItems.front().toInt() );
			surfaceItems.pop_front();
		}
	}

} // LandscapeSerializer::onSurfaceElement


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onObjectElement( const ILandscapeModel& _landscapeModel, const QString& _name, const int _x, const int _y, const StartPoint::Id& _id )
{
	assert( m_currentLoadLandscape );

	boost::intrusive_ptr< IPlayer > player = _landscapeModel.getPlayerByStartPoint( _id );

	m_currentLoadLandscape->createObject( _name, QPoint( _x, _y ), player ? player->getUniqueId() : IPlayer::ms_wrondId );

} // LandscapeSerializer::onObjectElement


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onStartPoint( const StartPoint::Id& _id, const int _x, const int _y )
{
	assert( m_currentLoadLandscape );
	m_currentLoadLandscape->addStartPoint( StartPoint( _id, QPoint( _x, _y ) ) );

} // LandscapeSerializer::onStartPoint


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onFinishParsing()
{
	assert( m_currentLoadLandscape );
	m_currentLoadLandscape = NULL;

} // LandscapeSerializer::onFinishParsing


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
