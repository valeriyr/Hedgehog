
#ifndef __PM_INTERFACE_MAP_HPP__
#define __PM_INTERFACE_MAP_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


#define INTERFACE_MAP_DECLARATION()														\
																						\
	/*virtual*/ Tools::Core::IBase* getInterface( const unsigned int _interfaceId );	\


/*---------------------------------------------------------------------------*/


#define BEGIN_INTERFACE_MAP( PLUGIN_INSTANCE )											\
																						\
Tools::Core::IBase*																		\
PLUGIN_INSTANCE::getInterface( const unsigned int _interfaceId )						\
{																						\
	switch( _interfaceId )																\
	{																					\


/*---------------------------------------------------------------------------*/


#define INTERFACE( INTERFACE_ID, INTERFACE_POINTER )									\
																						\
	case ( INTERFACE_ID ):																\
		return INTERFACE_POINTER;														\


/*---------------------------------------------------------------------------*/


#define END_INTERFACE_MAP()																\
																						\
		default:																		\
			return NULL;																\
	}																					\
}																						\


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_INTERFACE_MAP_HPP__