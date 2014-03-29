
#include "animation_manager/sources/ph/am_ph.hpp"

#include "animation_manager/sources/plugin/am_plugin_instance.hpp"

#include "animation_manager/sources/animation_manager/am_animation_manager.hpp"
#include "animation_manager/sources/animations_cache/am_animations_cache.hpp"

#include "animation_manager/sources/environment/am_environment.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"
#include "images_manager/h/im_plugin_id.hpp"

#include "multithreading_manager/h/mm_plugin_id.hpp"
#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

#include "script_engine/ih/se_iexporter.hpp"
#include "script_engine/h/se_plugin_id.hpp"

#include "messenger/ms_imessenger.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_ANIMATION_MANAGER, m_animationManager )
	INTERFACE_DECLARATION( IID_ANIMATIONS_CACHE, m_animationsCache )

END_INTERFACE_MAP()


/*---------------------------------------------------------------------------*/


PluginInstance::PluginInstance()
{
} // PluginInstance::PluginInstance


/*---------------------------------------------------------------------------*/


PluginInstance::~PluginInstance()
{
} // PluginInstance::~PluginInstance


/*---------------------------------------------------------------------------*/


void
PluginInstance::initialize()
{
	m_environment.reset( new Environment( *this ) );
	m_animationsCache.reset( new AnimationsCache() );
	m_animationManager.reset( new AnimationManager( *m_environment, *m_animationsCache ) );

	exportScriptAPI();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_animationManager.reset();
	m_animationsCache.reset();
	m_environment.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Tools::Core::IMessenger >
PluginInstance::getSystemMessenger() const
{
	return
		getPluginInterface< Tools::Core::IMessenger >(
				Framework::Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Tools::Core::IID_MESSENGER );

} // PluginInstance::getSystemMessenger


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
PluginInstance::getImagesManager() const
{
	return
		getPluginInterface< Framework::GUI::ImagesManager::IImagesManager >(
				Framework::GUI::ImagesManager::PID_IMAGES_MANAGER
			,	Framework::GUI::ImagesManager::IID_IMAGES_MANAGER );

} // PluginInstance::getImageManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::MultithreadingManager::IMultithreadingManager >
PluginInstance::getMultithreadingManager() const
{
	return
		getPluginInterface< Framework::Core::MultithreadingManager::IMultithreadingManager >(
				Framework::Core::MultithreadingManager::PID_MULTITHREADING_MANAGER
			,	Framework::Core::MultithreadingManager::IID_MULTITHREADING_MANAGER );

} // PluginInstance::getMultithreadingManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::ScriptEngine::IExporter >
PluginInstance::getScriptExporter() const
{
	return
		getPluginInterface< Framework::Core::ScriptEngine::IExporter >(
				Framework::Core::ScriptEngine::PID_SCRIPT_ENGINE
			,	Framework::Core::ScriptEngine::IID_EXPORTER );

} // PluginInstance::getScriptExporter


/*---------------------------------------------------------------------------*/


void
PluginInstance::exportScriptAPI()
{
	Framework::Core::ScriptEngine::DataExporter exporter = getScriptExporter()->getDataExporter();

	exporter.exportClass< FrameInfo >( "FrameInfo" )
		->withConstructor< const int, const QRect&, const bool >()
		.withConstructor< const int, const QRect& >();

	exporter.exportClass< AnimationInfo >( "AnimationInfo" )
		->withConstructor< const QString&, const QString& >()
		.withMethod( "addFrame", &AnimationInfo::addFrame );

	exporter.exportClass< IAnimationsCache >( "IAnimationsCache" )
		->withMethod( "regAnimation", &IAnimationsCache::regAnimation );

	exporter.exportVariable( "AnimationsCache", m_animationsCache.get() );

} // PluginInstance::exportScriptAPI


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
