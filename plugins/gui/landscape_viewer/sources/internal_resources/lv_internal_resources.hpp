
#ifndef __LV_INTERNAL_RESOURCES_HPP__
#define __LV_INTERNAL_RESOURCES_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {
namespace Resources {

/*---------------------------------------------------------------------------*/

namespace Views {

/*---------------------------------------------------------------------------*/

	extern const char* const LandscapeViewTitle;

	extern const char* const MinimapViewTitle;

	extern const char* const ObjectsViewTitle;

	extern const char* const ObjectsViewColumnName;

	extern const char* const DescriptionViewTitle;

	extern const char* const SettingsViewTitle;

	extern const char* const EditorViewDefaultTitle;

	extern const char* const TarrainMapVisibilityCheckboxName;

/*---------------------------------------------------------------------------*/

	extern const char* const LandscapeDescriptionDefaultText;

	extern const char* const LandscapeDescriptionFormat;

/*---------------------------------------------------------------------------*/

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Landscape {

/*---------------------------------------------------------------------------*/

	extern const unsigned int CellSize;

	extern const char* const SkinId;

/*---------------------------------------------------------------------------*/

} // namespace Landscape

/*---------------------------------------------------------------------------*/

namespace Commands {

/*---------------------------------------------------------------------------*/

	extern const char* const RunGameCommandName;

	extern const char* const StopGameCommandName;

	extern const char* const NewLandscapeCommandName;

	extern const char* const OpenLandscapeCommandName;

	extern const char* const CloseLandscapeCommandName;

	extern const char* const SaveLandscapeCommandName;

	extern const char* const SaveAsLandscapeCommandName;

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_INTERNAL_RESOURCES_HPP__
