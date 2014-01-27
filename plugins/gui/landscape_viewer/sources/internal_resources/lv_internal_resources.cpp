
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

	const char* const PlayerInfoViewTitle = "Player Information";

	const char* const EditorViewDefaultTitle = "Landscape Editor";

	const char* const TarrainMapVisibilityCheckboxName = "Show tarrain map";

	const char* const SkinIdLabel = "Skin Id:";

	const char* const UpdateMinimapCheckboxName = "Update minimap";

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
			"			<b>Health:</b> %2 / %3												"	\
			"			<br>																"	\
			"			<b>Moving speed:</b> %4												"	\
			"			<br>																"	\
			"			<b>Position:</b> ( %5, %6 )											"	\
			"			<br>																"	\
			"			<b>Size:</b> ( %7, %8 )												"	\
			"			<br>																"	\
			"			<b>Unique Id:</b> %9												"	\
			"		</div>																	"	\
			"	</body>																		"	\
			"</html>																		";

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

	const char* const PlayerInfoTextFormat
		=	"<html>																			"	\
			"	<head></head>																"	\
			"	<body>																		"	\
			"		<font><center><b>Player ( id: %1 )</b></center></font>					"	\
			"		<br>																	"	\
			"		<div>%2</div>															"	\
			"	</body>																		"	\
			"</html>																		";

	const char* const PlayerResourceInfoFormat = "<b>%1:</b> %2<br>";

/*---------------------------------------------------------------------------*/

} // namespace Views

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
