
#ifndef __LM_IPATH_FINDER_HPP__
#define __LM_IPATH_FINDER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_iunit.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape;

/*---------------------------------------------------------------------------*/

struct IPathFinder
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef std::list< QPoint > PointsCollection;
	typedef PointsCollection::iterator PointsCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual void findPath(	PointsCollection& _pointsCollection
						 ,	const ILandscape& _landscape
						 ,	const IUnit& _forUnit
						 ,	const QPoint& _toPoint ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPATH_FINDER_HPP__
