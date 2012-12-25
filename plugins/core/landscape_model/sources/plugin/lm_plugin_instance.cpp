
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/plugin/lm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "landscape_model/sources/landscape_editor/lm_landscape_editor.hpp"
#include "landscape_model/sources/landscape_manager/lm_landscape_manager.hpp"
#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_LANDSCAPE_EDITOR, m_landscapeEditor.get() )
	INTERFACE_DECLARATION( IID_LANDSCAPE_MANAGER, m_landscapeManager.get() )

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
	m_landscapeSerializer.reset( new LandscapeSerializer() );
	m_landscapeEditor.reset( new LandscapeEditor( *m_landscapeSerializer ) );
	m_landscapeManager.reset( new LandscapeManager( *m_landscapeSerializer ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_landscapeManager.reset();
	m_landscapeEditor.reset();
	m_landscapeSerializer.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
