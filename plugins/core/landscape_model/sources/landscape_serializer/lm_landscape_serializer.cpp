
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"


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
LandscapeSerializer::load(
		ILandscape& _landscape
	,	const QString& _filePath ) const
{
	QFile file( _filePath );
	if ( !file.open( QIODevice::ReadOnly ) )
		throw std::exception();

	QDataStream fileStream( &file );

	float version = 0.0f;
	fileStream >> version;

	if ( version != Resources::LandscapeVersion )
		throw std::exception();

	int width = 0;
	int height = 0;

	fileStream >> width;
	fileStream >> height;

	_landscape.setSize( width, height );

	int surfaceItemIndex = 0;

	for ( int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			fileStream >> surfaceItemIndex;
			_landscape.setSurfaceItem( QPoint( i, j ), surfaceItemIndex );
		}
	}

	int objectsCount = 0;
	fileStream >> objectsCount;

	for ( int i = 0; i < objectsCount; ++i )
	{
		QString objectName;
		int x = 0;
		int y = 0;

		fileStream >> objectName;
		fileStream >> x;
		fileStream >> y;

		_landscape.createObject( QPoint( x, y ), objectName );
	}

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

	QDataStream fileStream( &file );

	fileStream << Resources::LandscapeVersion;

	fileStream << _landscape.getWidth();
	fileStream << _landscape.getHeight();

	for ( int i = 0; i < _landscape.getWidth(); ++i )
		for ( int j = 0; j < _landscape.getHeight(); ++j )
			fileStream << _landscape.getSurfaceItem( QPoint( i, j ) )->getId();

	fileStream << _landscape.getObjectsCount();

	ILandscape::ObjectsCollection objectsCollection;
	_landscape.fetchObjects( objectsCollection );

	ILandscape::ObjectsCollectionIterator
			begin = objectsCollection.begin()
		,	end = objectsCollection.end();

	for ( ; begin != end; ++begin )
	{
		boost::intrusive_ptr< ILocateComponent > locateComponent
			= ( *begin )->getComponent< ILocateComponent >( ComponentId::Locate );

		fileStream << ( *begin )->getName();
		fileStream << locateComponent->getLocation().x();
		fileStream << locateComponent->getLocation().y();
	}

} // LandscapeSerializer::save


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
