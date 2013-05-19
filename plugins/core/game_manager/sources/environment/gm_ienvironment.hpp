
#ifndef __GM_IENVIRONMENT_HPP__
#define __GM_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "multithreading_manager/h/mm_runnable_function.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct IEditableLandscape;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< LandscapeModel::IEditableLandscape > getCurrentLandscape() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void runThread(
			const QString& _threadName
		,	Framework::Core::MultithreadingManager::RunnableFunction _function ) const = 0;

	virtual void stopThread( const QString& _threadName ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void playSound( const QString& _resourcePath ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_IENVIRONMENT_HPP__
