
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/units_cache/lm_units_cache.hpp"

#include "landscape_model/sources/unit/lm_unit.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


UnitsCache::UnitsCache()
	:	m_unitsCollection()
{
} // UnitsCache::UnitsCache


/*---------------------------------------------------------------------------*/


UnitsCache::~UnitsCache()
{
} // UnitsCache::~UnitsCache


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IUnit >
UnitsCache::cloneUnit( const QString& _name ) const
{
	UnitsCollectionIterator iterator( m_unitsCollection.find( _name ) );

	if ( iterator != m_unitsCollection.end() )
		return iterator->second->clone();

	return boost::intrusive_ptr< IUnit >();

} // UnitsCache::cloneUnit


/*---------------------------------------------------------------------------*/


void
UnitsCache::addUnit(
		const QString& _name
	,	const QString& _bundlePath
	,	const QRect& _rectInBundle
	)
{
	m_unitsCollection.insert(
		std::make_pair(
				_name
			,	boost::intrusive_ptr< IUnit >( new Unit( _name, _bundlePath, _rectInBundle ) ) ) );

} // SurfaceItemsCache::addSurfaceItem


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
