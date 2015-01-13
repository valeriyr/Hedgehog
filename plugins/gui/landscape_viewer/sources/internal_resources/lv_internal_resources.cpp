
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const QString ModuleName = "LANDSCAPE_VIEWER";

/*---------------------------------------------------------------------------*/

	const QString ConfigurationScriptsDirectory = "landscape_viewer";

/*---------------------------------------------------------------------------*/

namespace Views {

/*---------------------------------------------------------------------------*/

	const QString LandscapeViewTitle = "Landscape";

	const QString MinimapViewTitle = "Mini Map";

	const QString ObjectsViewTitle = "Landscape Objects";

	const QString ObjectsViewColumnName = "Landscape Items";

	const QString DescriptionViewTitle = "Landscape Description";

	const QString SettingsViewTitle = "Settings";

	const QString SelectionViewTitle = "Selection";

	const QString ActionPanelViewTitle = "Actions";

	const QString CreateObjectLabelFormat = "Create '%1'";

	const QString ObjectStatusViewTitle = "Status";

	const QString ObjectInfoViewTitle = "GameObject Information";

	const QString PlayerInfoViewTitle = "Players Information";

	const QString EditorViewDefaultTitle = "Landscape Editor";

	const QString TarrainMapVisibilityCheckboxName = "Show tarrain map";

	const QString SkinIdLabel = "Skin Id:";

	const QString UpdateMinimapCheckboxName = "Update minimap";

	const QString PlaySoundCheckboxName = "Play sound";

	const QString IpLabel = "Ip:";

	const QString PortLabel = "Port:";

	const QString RaceLabel = "Race:";

	const QString ColorLabel = "Color:";

	const QString VictoryCondition = "Victory condition:";

	const QString ConnectionTimeOutLabel = "Connection timeout (ms):";

	const QString PlayerNameLabel = "Player name:";

	const QString PlayerByStartPointLabelFormat = "SP %1 ( %2 )";

/*---------------------------------------------------------------------------*/

	const QString LandscapeDescriptionDefaultText
		=	"<html>																		"	\
			"	<head></head>															"	\
			"	<body>																	"	\
			"		<font><center><i>													"	\
			"			You should open some landscape to see its description.			"	\
			"		</i></center></font>												"	\
			"	</body>																	"	\
			"</html>																	";

	const QString LandscapeDescriptionFormat
		=	"<html>																		"	\
			"	<head></head>															"	\
			"	<body>																	"	\
			"		<font><center><b>Description</b></center></font>					"	\
			"		<ul>																"	\
			"			<li><b>File path:</b> '%1'</li>									"	\
			"			<br>															"	\
			"			<li><b>Landscape size:</b> %2 on %3</li>						"	\
			"			<br>															"	\
			"			<li><b>Victory condition:</b> %4</li>							"	\
			"		</ul>																"	\
			"	</body>																	"	\
			"</html>																	";

/*---------------------------------------------------------------------------*/

	const QString ObjectInfoDefaultText
		=	"<html>																				"	\
			"	<head></head>																	"	\
			"	<body>																			"	\
			"		<font><center><i>															"	\
			"			You should select some object on the landscape to see its information.	"	\
			"		</i></center></font>														"	\
			"	</body>																			"	\
			"</html>																			";

	const QString ObjectInfoFormat
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

	const QString DamageInfoFormat = "( %1 - %2 )";

	const QString ResourcesSourceFormat = "%1: %2";

	const QString ResourcesHoldFormat = "%1: %2 / %3";

	const QString NoneString = "none";

/*---------------------------------------------------------------------------*/

	const QString PlayerInfoDefaultText
		=	"<html>															"	\
			"	<head></head>												"	\
			"	<body>														"	\
			"		<font><center><i>										"	\
			"			You should be in game to see player information.	"	\
			"		</i></center></font>									"	\
			"	</body>														"	\
			"</html>														";

	const QString PlayersInfoTextFormat
		=	"<html>																			"	\
			"	<head></head>																"	\
			"	<body>%1<br>%2</body>														"	\
			"</html>																		";

	const QString PlayerInfoTextFormat
		=	"%1. <b>%2</b>: ( %3, %4 ) - %5<br>";

	const QString PlayerResourceInfoFormat = "%1: %2";

	const QString TickInfoTextFormat = "<b>Tick:</b> %1";

/*---------------------------------------------------------------------------*/

	const QString CreateButtonName = "Create";

	const QString ConnectButtonName = "Connect";

	const QString StartButtonName = "Start";

	const QString CancelButtonName = "Cancel";

/*---------------------------------------------------------------------------*/

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Messages {

/*---------------------------------------------------------------------------*/

	const QString SimulationIsRunningNow = "Simulation is running now. Stop it before creating new session.";

/*---------------------------------------------------------------------------*/

} // namespace Messages

/*---------------------------------------------------------------------------*/

namespace Animations {

/*---------------------------------------------------------------------------*/

	const QString AnimationNameFormat = "Skin(%1)GameObject(Name(%2)State(%3)Direction(%4))";

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

	const QString NewLandscapeCommandName = "lv.landscape.new";

	const QString OpenLandscapeCommandName = "lv.landscape.open";

	const QString CloseLandscapeCommandName = "lv.landscape.close";

	const QString SaveLandscapeCommandName = "lv.landscape.save";

	const QString SaveAsLandscapeCommandName = "lv.landscape.saveas";

	const QString StartGameCommandName = "lv.game.start";

	const QString StartReplayCommandName = "lv.replay.start";

	const QString SaveReplayCommandName = "lv.replay.save";

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

namespace Properties {

/*---------------------------------------------------------------------------*/

	const QString TerrainMapVisibility = "TerrainMapVisibilityProperty";

	const QString SkinId = "SkinIdProperty";

	const QString UpdateMinimap = "UpdateMinimap";

/*---------------------------------------------------------------------------*/

} // namespace Properties

/*---------------------------------------------------------------------------*/

namespace Sounds {

/*---------------------------------------------------------------------------*/

	const QString PlacementError = "ui/placement_error";

	const QString PlacementSuccess = "ui/placement_success";

/*---------------------------------------------------------------------------*/

} // namespace Sounds

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
