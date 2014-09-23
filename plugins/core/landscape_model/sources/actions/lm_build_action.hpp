
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

struct IWorkersHolder;

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
		,	IWorkersHolder& _workersHolder
		,	Object& _object
		,	const QString& _objectName
		,	const QPoint& _atLocation );

	virtual ~BuildAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool prepareToProcessingInternal();

	/*virtual*/ bool cancelProcessingInternal();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void startBuild(
			const Tools::Core::Generators::IGenerator::IdType& _id
		,	const QString& _objectName
		,	const QPoint& _location );

	void stopBuild( const Tools::Core::Generators::IGenerator::IdType& _id );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IWorkersHolder& m_workersHolder;

	const QString m_objectName;
	const QRect m_atRect;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILD_ACTION_HPP__
