
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"
#include "landscape_model/ih/lm_iobject.hpp"


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
		IEditableLandscape& _landscape
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

	unsigned int width = 0;
	unsigned int height = 0;

	fileStream >> width;
	fileStream >> height;

	_landscape.setSize( width, height );

	unsigned int surfaceItemIndex = 0;

	for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( unsigned int j = 0; j < _landscape.getHeight(); ++j )
		{
			fileStream >> surfaceItemIndex;
			_landscape.setSurfaceItem( QPoint( i, j ), surfaceItemIndex );
		}
	}

	unsigned int objectsCount = 0;
	fileStream >> objectsCount;

	for ( unsigned int i = 0; i < objectsCount; ++i )
	{
		QString objectName;
		unsigned int x = 0;
		unsigned int y = 0;

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

	for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
		for ( unsigned int j = 0; j < _landscape.getHeight(); ++j )
			fileStream << _landscape.getSurfaceItem( QPoint( i, j ) )->getId();

	fileStream << _landscape.getObjectsCount();

	ILandscape::ObjectsCollection objectsCollection;
	_landscape.fetchObjects( objectsCollection );

	ILandscape::ObjectsCollectionIterator
			begin = objectsCollection.begin()
		,	end = objectsCollection.end();

	for ( ; begin != end; ++begin )
	{
		fileStream << ( *begin )->getType()->getName();
		fileStream << ( *begin )->getPosition().x();
		fileStream << ( *begin )->getPosition().y();
	}

} // LandscapeSerializer::save


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
