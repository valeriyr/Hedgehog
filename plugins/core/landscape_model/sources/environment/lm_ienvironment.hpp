
#ifndef __LM_IENVIRONMENT_HPP__
#define __LM_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "multithreading_manager/h/mm_runnable_function.hpp"
#include "multithreading_manager/h/mm_task_handle.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void startThread( const QString& _threadName ) const = 0;

	virtual void stopThread( const QString& _threadName ) const = 0;

	virtual Framework::Core::MultithreadingManager::TaskHandle
		pushTask(
			const QString& _threadName
		,	Framework::Core::MultithreadingManager::RunnableFunction _function
		,	const qint64 _period ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void printMessage( const QString& _message ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IENVIRONMENT_HPP__
