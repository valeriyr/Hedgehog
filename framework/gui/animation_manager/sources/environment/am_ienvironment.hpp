
#ifndef __AM_IENVIRONMENT_HPP__
#define __AM_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "images_manager/ih/im_iimages_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual Core::MultithreadingManager::TaskHandle
		pushPeriodicalTask(
					const QString& _threadName
				,	const Core::MultithreadingManager::RunnableFunction& _function ) const = 0;

	virtual void removeTask( const Core::MultithreadingManager::TaskHandle& _taskHandle ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap(
			const QString& _resourcePath
		,	const Framework::GUI::ImagesManager::IImagesManager::TransformationData& _transformationData ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_IENVIRONMENT_HPP__
