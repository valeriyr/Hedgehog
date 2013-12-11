
#include "settings/sources/ph/st_ph.hpp"

#include "settings/sources/settings/st_settings.hpp"

#include "settings/sources/environment/st_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

/*---------------------------------------------------------------------------*/


Settings::Settings( IEnvironment& _environment )
	:	m_environment( _environment )
{
} // Settings::Settings


/*---------------------------------------------------------------------------*/


Settings::~Settings()
{
} // Settings::~Settings


/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
