
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

struct IBuildersHolder;
struct IStaticData;

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
		,	IBuildersHolder& _buildersHolder
		,	const IStaticData& _staticData
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

	void startBuild(
			const Object::Id& _id
		,	const QString& _objectName
		,	const QPoint& _location );

	void stopBuild( const Object::Id& _id );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IBuildersHolder& m_buildersHolder;

	const IStaticData& m_staticData;

	const QString m_objectName;
	const QRect m_atRect;

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
