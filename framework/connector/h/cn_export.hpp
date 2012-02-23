
/** Connector export macroses */

#ifndef __CN_EXPORT_HPP_
#define __CN_EXPORT_HPP_

/*----------------------------------------------------------------------------*/

#ifndef _WINDOWS
	#define CONNECTOR_EXPORT

#elif defined( CONNECTOR_EXPORTS )
	#define CONNECTOR_EXPORT __declspec( dllexport )
#else
	#define CONNECTOR_EXPORT __declspec( dllimport )
#endif


/*----------------------------------------------------------------------------*/

#endif // __CN_EXPORT_HPP_
