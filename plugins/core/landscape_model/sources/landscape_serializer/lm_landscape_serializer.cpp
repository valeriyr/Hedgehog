
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"
#include "landscape_model/ih/lm_iunit.hpp"


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

	unsigned int unitsCount = 0;
	fileStream >> unitsCount;

	for ( unsigned int i = 0; i < unitsCount; ++i )
	{
		QString objectName;
		unsigned int left = 0;
		unsigned int right = 0;
		unsigned int bottom = 0;
		unsigned int top = 0;

		fileStream >> objectName;
		fileStream >> left;
		fileStream >> right;
		fileStream >> bottom;
		fileStream >> top;

		_landscape.createObject( QPoint( left, top ), objectName );
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

	fileStream << _landscape.getUnitsCount();

	ILandscape::UnitsCollection unitsCollection;
	_landscape.fetchUnits( unitsCollection );

	ILandscape::UnitsCollectionIterator
			begin = unitsCollection.begin()
		,	end = unitsCollection.end();

	for ( ; begin != end; ++begin )
	{
		fileStream << ( *begin )->getType()->getName();
		fileStream << ( *begin )->getPosition().left();
		fileStream << ( *begin )->getPosition().right();
		fileStream << ( *begin )->getPosition().bottom();
		fileStream << ( *begin )->getPosition().top();
	}

} // LandscapeSerializer::save


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
