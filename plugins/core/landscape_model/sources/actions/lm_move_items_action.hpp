
#ifndef __LM_MOVE_ITEMS_ACTION_HPP__
#define __LM_MOVE_ITEMS_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/ih/lm_iobject.hpp"

#include "landscape_model/sources/path_finders/lm_ipath_finder.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class MoveAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

	struct MovingData
	{
		MovingData()
			:	m_path()
			,	m_movingProgress( 0.0 )
		{}

		IPathFinder::PointsCollection m_path;
		float m_movingProgress;
	};

	typedef
		std::map< IObject::IdType, MovingData >
		MovingDataCollection;
	typedef
		MovingDataCollection::iterator
		MovingDataCollectionIterator;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MoveAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	boost::intrusive_ptr< IPathFinder > _pathFinder
		,	const QPoint& _to );

	virtual ~MoveAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ void unprocessAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IPathFinder > m_pathFinder;

	const QPoint m_to;

	MovingDataCollection m_movingData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MOVE_ITEMS_ACTION_HPP__
