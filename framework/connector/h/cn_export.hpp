
/** Connector export macroses */

#ifndef __CN_EXPORT_HPP_
#define __CN_EXPORT_HPP_

/*----------------------------------------------------------------------------*/

#ifndef _WINDOWS
	#define PM_EXPORT

#elif defined( CONNECTOR_EXPORTS )
	#define PM_EXPORT __declspec( dllexport )
#else
	#define PM_EXPORT __declspec( dllimport )
#endif


/*----------------------------------------------------------------------------*/

#endif // __CN_EXPORT_HPP_
