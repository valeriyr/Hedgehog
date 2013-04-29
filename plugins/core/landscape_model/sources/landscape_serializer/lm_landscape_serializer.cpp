
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_iunits_cache.hpp"
#include "landscape_model/ih/lm_iunit.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeSerializer::LandscapeSerializer(
		const ISurfaceItemsCache& _surfaceItemsCache
	,	const IUnitsCache& _unitsCache
	)
	:	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_unitsCache( _unitsCache )
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
			_landscape.setSurfaceItem(
					i
				,	j
				,	m_surfaceItemsCache.getSurfaceItem( surfaceItemIndex ) );
		}
	}

	unsigned int unitsCount = 0;
	fileStream >> unitsCount;

	for ( unsigned int i = 0; i < unitsCount; ++i )
	{
		QString unitName;
		unsigned int positionByX = 0;
		unsigned int positionByY = 0;

		fileStream >> unitName;
		fileStream >> positionByX;
		fileStream >> positionByY;

		_landscape.setUnit( positionByX, positionByY, m_unitsCache.cloneUnit( unitName ) );
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
			fileStream << _landscape.getSurfaceItem( i, j )->getIndex();

	fileStream << _landscape.getUnitsCount();

	ILandscape::UnitsIteratorPtr unitsIterator = _landscape.getUnitsIterator();

	while ( unitsIterator->isValid() )
	{
		fileStream << unitsIterator->current()->getName();
		fileStream << _landscape.getUnitPosition( unitsIterator->current() ).first;
		fileStream << _landscape.getUnitPosition( unitsIterator->current() ).second;

		unitsIterator->next();
	}

} // LandscapeSerializer::save


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
