
#ifndef __PM_EXPORT_HPP__
#define __PM_EXPORT_HPP__

/*----------------------------------------------------------------------------*/

#ifndef _WINDOWS
	#define PLUGINS_MANAGER_EXPORT

#elif defined( PLUGINS_MANAGER_EXPORTS )
	#define PLUGINS_MANAGER_EXPORT __declspec( dllexport )
#else
	#define PLUGINS_MANAGER_EXPORT __declspec( dllimport )
#endif


/*----------------------------------------------------------------------------*/

#endif // __PM_EXPORT_HPP__
