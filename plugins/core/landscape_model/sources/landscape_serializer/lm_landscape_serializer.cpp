
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"

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
			Tools::Core::XmlLibrary::Tag( "hmap" )
			[
					Tools::Core::XmlLibrary::Tag( "surface" )
					[
						Tools::Core::XmlLibrary::CDATA()
					]
					.handle(
							boost::bind( &LandscapeSerializer::onSurfaceElement, this, _1 )
						,	Tools::Core::XmlLibrary::CDATAExtructor()
						)
				||	*Tools::Core::XmlLibrary::Tag( "objects" )
					[
							+Tools::Core::XmlLibrary::Tag( "object" )
							[
								Tools::Core::XmlLibrary::Attribute( "name", Tools::Core::XmlLibrary::AttributeType::String )
							]
							[
								Tools::Core::XmlLibrary::Tag( "location" )
								[
										Tools::Core::XmlLibrary::Attribute( "x", Tools::Core::XmlLibrary::AttributeType::Integer )
									&&
										Tools::Core::XmlLibrary::Attribute( "y", Tools::Core::XmlLibrary::AttributeType::Integer )
								]
								.handle(
										boost::bind( &LandscapeSerializer::onObjectElement, this, _1, _2, _3 )
									,	Tools::Core::XmlLibrary::ParentStringAttributeExtructor( "name" )
									,	Tools::Core::XmlLibrary::IntAttributeExtructor( "x" )
									,	Tools::Core::XmlLibrary::IntAttributeExtructor( "y" )
									)
							]
					]
			]
			.handle(
					boost::bind( &LandscapeSerializer::onHMapElement, this, _1, _2, _3 )
				,	Tools::Core::XmlLibrary::FloatAttributeExtructor( "version" )
				,	Tools::Core::XmlLibrary::IntAttributeExtructor( "width" )
				,	Tools::Core::XmlLibrary::IntAttributeExtructor( "height" )
				)
			.postHandle( boost::bind( &LandscapeSerializer::onFinishParsing, this ) );

	Tools::Core::XmlLibrary::Parser::parse( *rule.getElement(), file );

} // LandscapeSerializer::load


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::save(
		const ILandscape& _landscape
	,	const QString& _filePath ) const
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

    xmlStream.writeDTD("<!DOCTYPE hmap>");

    xmlStream.writeStartElement("hmap");

	xmlStream.writeAttribute("version", QString::number( Resources::LandscapeVersion ) );
	xmlStream.writeAttribute("width", QString::number( _landscape.getWidth() ) );
	xmlStream.writeAttribute("height", QString::number( _landscape.getHeight() ) );

	xmlStream.writeStartElement("surface");

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

	xmlStream.writeCDATA( surfaceData );

	xmlStream.writeEndElement();

	xmlStream.writeStartElement("objects");

	xmlStream.writeAttribute( "count", QString::number( _landscape.getObjectsCount() ) );

	ILandscape::ObjectsCollection objectsCollection;
	_landscape.fetchObjects( objectsCollection );

	ILandscape::ObjectsCollectionIterator
			begin = objectsCollection.begin()
		,	end = objectsCollection.end();

	for ( ; begin != end; ++begin )
	{
		boost::intrusive_ptr< ILocateComponent > locateComponent
			= ( *begin )->getComponent< ILocateComponent >( ComponentId::Locate );

		xmlStream.writeStartElement("object");

		xmlStream.writeAttribute( "name", ( *begin )->getName() );

		xmlStream.writeStartElement("location");

		xmlStream.writeAttribute( "x", QString::number( locateComponent->getLocation().x() ) );
		xmlStream.writeAttribute( "y", QString::number( locateComponent->getLocation().y() ) );

		xmlStream.writeEndElement();
		xmlStream.writeEndElement();
	}

	xmlStream.writeEndElement();
	xmlStream.writeEndElement();

	xmlStream.writeEndDocument();

} // LandscapeSerializer::save


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onHMapElement( const float _version, const int _width, const int _height )
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
LandscapeSerializer::onObjectElement( const QString& _name, const int _x, const int _y )
{
	assert( m_currentLoadLandscape );
	m_currentLoadLandscape->createObject( QPoint( _x, _y ), _name );

} // LandscapeSerializer::onObjectElement


/*---------------------------------------------------------------------------*/


void
LandscapeSerializer::onFinishParsing()
{
	assert( m_currentLoadLandscape );
	m_currentLoadLandscape = NULL;

} // LandscapeSerializer::onHMapElement


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
