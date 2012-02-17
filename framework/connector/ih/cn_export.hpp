
/** Connector export macroses */

#ifndef __CN_EXPORT_HPP_
#define __CN_EXPORT_HPP_

/*----------------------------------------------------------------------------*/

#ifndef WINDOWS_PLATFORM
	#define PM_EXPORT

#elif defined( CN_EXPORT )
	#define PM_EXPORT __declspec( dllexport )
#else
	#define PM_EXPORT __declspec( dllimport )
#endif


/*----------------------------------------------------------------------------*/

#endif // __CN_EXPORT_HPP_
