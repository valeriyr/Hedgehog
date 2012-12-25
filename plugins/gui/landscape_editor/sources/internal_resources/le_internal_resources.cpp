
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

	const char* const DescriptionViewTitle = "Landscape Description";

	const char* const EditorViewDefaultTitle = "Landscape Editor";

/*---------------------------------------------------------------------------*/

	const char* const LandscapeDescriptionDefaultText
		=	"<html>																						"	\
			"	<head></head>																			"	\
			"	<body>																					"	\
			"		<font><center><i>																	"	\
			"			You should open some landscape to see its description.							"	\
			"		</i></center></font>																"	\
			"	</body>																					"	\
			"</html>																					";

/*---------------------------------------------------------------------------*/

} // namespace Views

/*---------------------------------------------------------------------------*/

namespace Commands {

/*---------------------------------------------------------------------------*/

	const char* const NewLandscapeCommandName = "le.landscape.new";

	const char* const OpenLandscapeCommandName = "le.landscape.open";

	const char* const CloseLandscapeCommandName = "le.landscape.close";

	const char* const SaveLandscapeCommandName = "le.landscape.save";

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
