
#ifndef __LV_INTERNAL_RESOURCES_HPP__
#define __LV_INTERNAL_RESOURCES_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {
namespace Resources {

/*---------------------------------------------------------------------------*/

	extern const char* const ModuleName;

/*---------------------------------------------------------------------------*/

	extern const char* const ConfigurationScriptsDirectory;

/*---------------------------------------------------------------------------*/

namespace Views {

/*---------------------------------------------------------------------------*/

	extern const char* const LandscapeViewTitle;

	extern const char* const MinimapViewTitle;

	extern const char* const ObjectsViewTitle;

	extern const char* const ObjectsViewColumnName;

	extern const char* const DescriptionViewTitle;

	extern const char* const SettingsViewTitle;

	extern const char* const SelectionViewTitle;

	extern const char* const ActionPanelViewTitle;

	extern const char* const CreateObjectLabelFormat;

	extern const char* const ObjectStatusViewTitle;

	extern const char* const ObjectInfoViewTitle;

	extern const char* const PlayerInfoViewTitle;

	extern const char* const EditorViewDefaultTitle;

	extern const char* const TarrainMapVisibilityCheckboxName;

	extern const char* const SkinIdLabel;

	extern const char* const UpdateMinimapCheckboxName;

	extern const char* const PlaySoundCheckboxName;

	extern const char* const IpLabel;

	extern const char* const PortLabel;

/*---------------------------------------------------------------------------*/

	extern const char* const LandscapeDescriptionDefaultText;

	extern const char* const LandscapeDescriptionFormat;

/*---------------------------------------------------------------------------*/

	extern const char* const ObjectInfoDefaultText;

	extern const char* const ObjectInfoFormat;

	extern const char* const DamageInfoFormat;

	extern const char* const ResourcesSourceFormat;

	extern const char* const ResourcesHoldFormat;

	extern const char* const NoneString;

/*---------------------------------------------------------------------------*/

	extern const char* const PlayerInfoDefaultText;

	extern const char* const PlayersInfoTextFormat;

	extern const char* const PlayerInfoTextFormat;

	extern const char* const PlayerResourceInfoFormat;

	extern const char* const TickInfoTextFormat;

/*---------------------------------------------------------------------------*/

	extern const char* const CreateButtonName;

	extern const char* const ConnectButtonName;

	extern const char* const StartButtonName;

/*---------------------------------------------------------------------------*/

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Animations {

/*---------------------------------------------------------------------------*/

	extern const char* const AnimationNameFormat;

/*---------------------------------------------------------------------------*/

} // namespace Animations

/*---------------------------------------------------------------------------*/

namespace Landscape {

/*---------------------------------------------------------------------------*/

	extern const int CellSize;

/*---------------------------------------------------------------------------*/

} // namespace Landscape

/*---------------------------------------------------------------------------*/

namespace Commands {

/*---------------------------------------------------------------------------*/

	extern const char* const NewLandscapeCommandName;

	extern const char* const OpenLandscapeCommandName;

	extern const char* const CloseLandscapeCommandName;

	extern const char* const SaveLandscapeCommandName;

	extern const char* const SaveAsLandscapeCommandName;

	extern const char* const StartMultiplayerGameCommandName;

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

namespace Properties {

/*---------------------------------------------------------------------------*/

	extern const char* const TerrainMapVisibility;

	extern const char* const SkinId;

	extern const char* const UpdateMinimap;

	extern const char* const Port;

	extern const char* const Ip;

/*---------------------------------------------------------------------------*/

} // namespace Properties

/*---------------------------------------------------------------------------*/

namespace Sounds {

/*---------------------------------------------------------------------------*/

	extern const char* const PlacementError;

	extern const char* const PlacementSuccess;

/*---------------------------------------------------------------------------*/

} // namespace Sounds

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_INTERNAL_RESOURCES_HPP__
