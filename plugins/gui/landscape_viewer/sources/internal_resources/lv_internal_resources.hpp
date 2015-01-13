
#ifndef __LV_INTERNAL_RESOURCES_HPP__
#define __LV_INTERNAL_RESOURCES_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {
namespace Resources {

/*---------------------------------------------------------------------------*/

	extern const QString ModuleName;

/*---------------------------------------------------------------------------*/

	extern const QString ConfigurationScriptsDirectory;

/*---------------------------------------------------------------------------*/

namespace Views {

/*---------------------------------------------------------------------------*/

	extern const QString LandscapeViewTitle;

	extern const QString MinimapViewTitle;

	extern const QString ObjectsViewTitle;

	extern const QString ObjectsViewColumnName;

	extern const QString DescriptionViewTitle;

	extern const QString SettingsViewTitle;

	extern const QString SelectionViewTitle;

	extern const QString ActionPanelViewTitle;

	extern const QString CreateObjectLabelFormat;

	extern const QString ObjectStatusViewTitle;

	extern const QString ObjectInfoViewTitle;

	extern const QString PlayerInfoViewTitle;

	extern const QString EditorViewDefaultTitle;

	extern const QString TarrainMapVisibilityCheckboxName;

	extern const QString SkinIdLabel;

	extern const QString UpdateMinimapCheckboxName;

	extern const QString PlaySoundCheckboxName;

	extern const QString IpLabel;

	extern const QString PortLabel;

	extern const QString RaceLabel;

	extern const QString ColorLabel;

	extern const QString VictoryCondition;

	extern const QString ConnectionTimeOutLabel;

	extern const QString PlayerNameLabel;

	extern const QString PlayerByStartPointLabelFormat;

/*---------------------------------------------------------------------------*/

	extern const QString LandscapeDescriptionDefaultText;

	extern const QString LandscapeDescriptionFormat;

/*---------------------------------------------------------------------------*/

	extern const QString ObjectInfoDefaultText;

	extern const QString ObjectInfoFormat;

	extern const QString DamageInfoFormat;

	extern const QString ResourcesSourceFormat;

	extern const QString ResourcesHoldFormat;

	extern const QString NoneString;

/*---------------------------------------------------------------------------*/

	extern const QString PlayerInfoDefaultText;

	extern const QString PlayersInfoTextFormat;

	extern const QString PlayerInfoTextFormat;

	extern const QString PlayerResourceInfoFormat;

	extern const QString TickInfoTextFormat;

/*---------------------------------------------------------------------------*/

	extern const QString CreateButtonName;

	extern const QString ConnectButtonName;

	extern const QString StartButtonName;

	extern const QString CancelButtonName;

/*---------------------------------------------------------------------------*/

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Messages {

/*---------------------------------------------------------------------------*/

	extern const QString SimulationIsRunningNow;

/*---------------------------------------------------------------------------*/

} // namespace Messages

/*---------------------------------------------------------------------------*/

namespace Animations {

/*---------------------------------------------------------------------------*/

	extern const QString AnimationNameFormat;

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

	extern const QString NewLandscapeCommandName;

	extern const QString OpenLandscapeCommandName;

	extern const QString CloseLandscapeCommandName;

	extern const QString SaveLandscapeCommandName;

	extern const QString SaveAsLandscapeCommandName;

	extern const QString StartGameCommandName;

	extern const QString StartReplayCommandName;

	extern const QString SaveReplayCommandName;

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

namespace Properties {

/*---------------------------------------------------------------------------*/

	extern const QString TerrainMapVisibility;

	extern const QString SkinId;

	extern const QString UpdateMinimap;

/*---------------------------------------------------------------------------*/

} // namespace Properties

/*---------------------------------------------------------------------------*/

namespace Sounds {

/*---------------------------------------------------------------------------*/

	extern const QString PlacementError;

	extern const QString PlacementSuccess;

/*---------------------------------------------------------------------------*/

} // namespace Sounds

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_INTERNAL_RESOURCES_HPP__
