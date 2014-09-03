
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const char* const ModuleName = "LANDSCAPE_VIEWER";

/*---------------------------------------------------------------------------*/

	const char* const ConfigurationScriptsDirectory = "landscape_viewer";

/*---------------------------------------------------------------------------*/

namespace Views {

/*---------------------------------------------------------------------------*/

	const char* const LandscapeViewTitle = "Landscape";

	const char* const MinimapViewTitle = "Mini Map";

	const char* const ObjectsViewTitle = "Landscape Objects";

	const char* const ObjectsViewColumnName = "Landscape Items";

	const char* const DescriptionViewTitle = "Landscape Description";

	const char* const SettingsViewTitle = "Settings";

	const char* const SelectionViewTitle = "Selection";

	const char* const ActionPanelViewTitle = "Actions";

	const char* const CreateObjectLabelFormat = "Create '%1'";

	const char* const ObjectStatusViewTitle = "Status";

	const char* const ObjectInfoViewTitle = "Object Information";

	const char* const PlayerInfoViewTitle = "Players Information";

	const char* const EditorViewDefaultTitle = "Landscape Editor";

	const char* const TarrainMapVisibilityCheckboxName = "Show tarrain map";

	const char* const SkinIdLabel = "Skin Id:";

	const char* const UpdateMinimapCheckboxName = "Update minimap";

	const char* const PlaySoundCheckboxName = "Play sound";

	const char* const IpLabel = "Ip:";

	const char* const PortLabel = "Port:";

	const char* const RaceLabel = "Race:";

	const char* const ColorLabel = "Color:";

	const char* const VictoryCondition = "Victory condition:";

	const char* const ConnectionTimeOutLabel = "Connection timeout (ms):";

	const char* const PlayerNameLabel = "Player name:";

	const char* const PlayerByStartPointLabelFormat = "SP %1 ( %2 )";

/*---------------------------------------------------------------------------*/

	const char* const LandscapeDescriptionDefaultText
		=	"<html>																		"	\
			"	<head></head>															"	\
			"	<body>																	"	\
			"		<font><center><i>													"	\
			"			You should open some landscape to see its description.			"	\
			"		</i></center></font>												"	\
			"	</body>																	"	\
			"</html>																	";

	const char* const LandscapeDescriptionFormat
		=	"<html>																		"	\
			"	<head></head>															"	\
			"	<body>																	"	\
			"		<font><center><b>Description</b></center></font>					"	\
			"		<ul>																"	\
			"			<li><b>File path:</b> '%1'</li>									"	\
			"			<br>															"	\
			"			<li><b>Landscape size:</b> %2 on %3</li>						"	\
			"		</ul>																"	\
			"	</body>																	"	\
			"</html>																	";

/*---------------------------------------------------------------------------*/

	const char* const ObjectInfoDefaultText
		=	"<html>																				"	\
			"	<head></head>																	"	\
			"	<body>																			"	\
			"		<font><center><i>															"	\
			"			You should select some object on the landscape to see its information.	"	\
			"		</i></center></font>														"	\
			"	</body>																			"	\
			"</html>																			";

	const char* const ObjectInfoFormat
		=	"<html>																			"	\
			"	<head></head>																"	\
			"	<body>																		"	\
			"		<font><center><b>%1</b></center></font>									"	\
			"		<br>																	"	\
			"		<div>																	"	\
			"			<b>Unique Id:</b> %2												"	\
			"			<br>																"	\
			"			<b>State:</b> %3													"	\
			"			<br>																"	\
			"			<b>Player Id:</b> %4												"	\
			"			<br>																"	\
			"			<b>Health:</b> %5 / %6												"	\
			"			<br>																"	\
			"			<b>Moving speed:</b> %7												"	\
			"			<br>																"	\
			"			<b>Position:</b> ( %8, %9 )											"	\
			"			<br>																"	\
			"			<b>Size:</b> ( %10, %11 )											"	\
			"			<br>																"	\
			"			<b>Emplacement:</b> %12												"	\
			"			<br>																"	\
			"			<b>Damage:</b> %13													"	\
			"			<br>																"	\
			"			<b>Attack distance:</b> %14											"	\
			"			<br>																"	\
			"			<b>Resource inside:</b> %15											"	\
			"			<br>																"	\
			"			<b>Resources hold:</b> %16											"	\
			"			<br>																"	\
			"			<b>Can store resources:</b> %17										"	\
			"		</div>																	"	\
			"	</body>																		"	\
			"</html>																		";

	const char* const DamageInfoFormat = "( %1 - %2 )";

	const char* const ResourcesSourceFormat = "%1: %2";

	const char* const ResourcesHoldFormat = "%1: %2 / %3";

	const char* const NoneString = "none";

/*---------------------------------------------------------------------------*/

	const char* const PlayerInfoDefaultText
		=	"<html>															"	\
			"	<head></head>												"	\
			"	<body>														"	\
			"		<font><center><i>										"	\
			"			You should be in game to see player information.	"	\
			"		</i></center></font>									"	\
			"	</body>														"	\
			"</html>														";

	const char* const PlayersInfoTextFormat
		=	"<html>																			"	\
			"	<head></head>																"	\
			"	<body>%1<br>%2</body>														"	\
			"</html>																		";

	const char* const PlayerInfoTextFormat
		=	"%1. <b>%2</b>: ( %3, %4 ) - %5<br>";

	const char* const PlayerResourceInfoFormat = "%1: %2";

	const char* const TickInfoTextFormat = "<b>Tick:</b> %1";

/*---------------------------------------------------------------------------*/

	const char* const CreateButtonName = "Create";

	const char* const ConnectButtonName = "Connect";

	const char* const StartButtonName = "Start";

	const char* const CancelButtonName = "Cancel";

/*---------------------------------------------------------------------------*/

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Messages {

/*---------------------------------------------------------------------------*/

	const char* const SimulationIsRunningNow = "Simulation is running now. Stop it before creating new session.";

/*---------------------------------------------------------------------------*/

} // namespace Messages

/*---------------------------------------------------------------------------*/

namespace Animations {

/*---------------------------------------------------------------------------*/

	const char* const AnimationNameFormat = "Skin(%1)Object(Name(%2)State(%3)Direction(%4))";

/*---------------------------------------------------------------------------*/

} // namespace Animations

/*---------------------------------------------------------------------------*/

namespace Landscape {

/*---------------------------------------------------------------------------*/

	const int CellSize = 32;

/*---------------------------------------------------------------------------*/

} // namespace Landscape

/*---------------------------------------------------------------------------*/

namespace Commands {

/*---------------------------------------------------------------------------*/

	const char* const NewLandscapeCommandName = "lv.landscape.new";

	const char* const OpenLandscapeCommandName = "lv.landscape.open";

	const char* const CloseLandscapeCommandName = "lv.landscape.close";

	const char* const SaveLandscapeCommandName = "lv.landscape.save";

	const char* const SaveAsLandscapeCommandName = "lv.landscape.saveas";

	const char* const StartGameCommandName = "lv.game.start";

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

namespace Properties {

/*---------------------------------------------------------------------------*/

	const char* const TerrainMapVisibility = "TerrainMapVisibilityProperty";

	const char* const SkinId = "SkinIdProperty";

	const char* const UpdateMinimap = "UpdateMinimap";

/*---------------------------------------------------------------------------*/

} // namespace Properties

/*---------------------------------------------------------------------------*/

namespace Sounds {

/*---------------------------------------------------------------------------*/

	const char* const PlacementError = "ui/placement_error";

	const char* const PlacementSuccess = "ui/placement_success";

/*---------------------------------------------------------------------------*/

} // namespace Sounds

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
