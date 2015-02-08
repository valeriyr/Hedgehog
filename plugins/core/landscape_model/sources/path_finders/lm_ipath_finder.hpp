
#ifndef __LM_IPATH_FINDER_HPP__
#define __LM_IPATH_FINDER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape;

class GameObject;

/*---------------------------------------------------------------------------*/

struct IPathFinder
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef std::list< QPoint > PointsCollection;
	typedef PointsCollection::iterator PointsCollectionIterator;
	typedef PointsCollection::const_iterator PointsCollectionConstIterator;

/*---------------------------------------------------------------------------*/

	virtual void findPath(	PointsCollection& _pointsCollection
						 ,	const ILandscape& _landscape
						 ,	const GameObject& _object
						 ,	const PointsCollection& _targets ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPATH_FINDER_HPP__
