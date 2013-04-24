
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {
namespace Resources {

/*---------------------------------------------------------------------------*/

namespace Views {

/*---------------------------------------------------------------------------*/

	const char* const ObjectsViewTitle = "Landscape Objects";

	const char* const ObjectsViewColumnName = "Landscape Items";

	const char* const DescriptionViewTitle = "Landscape Description";

	const char* const EditorViewDefaultTitle = "Landscape Editor";

	const char* const MinimapViewTitle = "Mini Map";

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

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Commands {

/*---------------------------------------------------------------------------*/

	const char* const NewLandscapeCommandName = "le.landscape.new";

	const char* const OpenLandscapeCommandName = "le.landscape.open";

	const char* const CloseLandscapeCommandName = "le.landscape.close";

	const char* const SaveLandscapeCommandName = "le.landscape.save";

	const char* const SaveAsLandscapeCommandName = "le.landscape.saveas";

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

namespace Landscape {

/*---------------------------------------------------------------------------*/

	const unsigned int CellSize = 32;

/*---------------------------------------------------------------------------*/

} // namespace Landscape

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
