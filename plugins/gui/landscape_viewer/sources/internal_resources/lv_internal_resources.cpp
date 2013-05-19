
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {
namespace Resources {

/*---------------------------------------------------------------------------*/

namespace Views {

/*---------------------------------------------------------------------------*/

	const char* const LandscapeViewTitle = "Landscape";

	const char* const MinimapViewTitle = "Mini Map";

	const char* const ObjectsViewTitle = "Landscape Objects";

	const char* const ObjectsViewColumnName = "Landscape Items";

	const char* const DescriptionViewTitle = "Landscape Description";

	const char* const EditorViewDefaultTitle = "Landscape Editor";

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

/*---------------------------------------------------------------------------*/

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Landscape {

/*---------------------------------------------------------------------------*/

	const unsigned int CellSize = 32;

/*---------------------------------------------------------------------------*/

} // namespace Landscape

/*---------------------------------------------------------------------------*/

namespace Commands {

/*---------------------------------------------------------------------------*/

	const char* const RunGameCommandName = "lv.game.run";

	const char* const StopGameCommandName = "lv.game.stop";

	const char* const NewLandscapeCommandName = "lv.landscape.new";

	const char* const OpenLandscapeCommandName = "lv.landscape.open";

	const char* const CloseLandscapeCommandName = "lv.landscape.close";

	const char* const SaveLandscapeCommandName = "lv.landscape.save";

	const char* const SaveAsLandscapeCommandName = "lv.landscape.saveas";

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
