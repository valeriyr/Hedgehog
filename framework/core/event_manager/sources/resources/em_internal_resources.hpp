
#ifndef __EM_INTERNAL_RESOURCES_HPP__
#define __EM_INTERNAL_RESOURCES_HPP__

#include "time/t_time.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {
namespace Resources {

/*---------------------------------------------------------------------------*/

	extern const char* const ModuleName;

/*---------------------------------------------------------------------------*/

	extern const Tools::Core::Time::Milliseconds TimeLimit;

	extern const char* const TimeLimitWarning;

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_INTERNAL_RESOURCES_HPP__
