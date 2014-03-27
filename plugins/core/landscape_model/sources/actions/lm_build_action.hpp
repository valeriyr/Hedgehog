
#ifndef __LM_BUILD_ACTION_HPP__
#define __LM_BUILD_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class MoveAction;

/*---------------------------------------------------------------------------*/

class BuildAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BuildAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	Object& _object
		,	const QString& _objectName
		,	const QPoint& _atLocation );

	virtual ~BuildAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool prepareToProcessingInternal();

	/*virtual*/ bool cancelProcessingInternal();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QString m_objectName;

	const QPoint m_atLocation;

	bool m_buildingFinished;

	boost::intrusive_ptr< MoveAction > m_moveAction;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILD_ACTION_HPP__
