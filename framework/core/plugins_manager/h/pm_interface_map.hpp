
#ifndef __PM_INTERFACE_MAP_HPP__
#define __PM_INTERFACE_MAP_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


#define INTERFACE_MAP_DECLARATION()														\
																						\
	/*virtual*/ boost::intrusive_ptr< Tools::Core::IBase >								\
		getInterface( const quint32 _interfaceId );										\


/*---------------------------------------------------------------------------*/


#define BEGIN_INTERFACE_MAP( PLUGIN_INSTANCE )											\
																						\
boost::intrusive_ptr< Tools::Core::IBase >												\
PLUGIN_INSTANCE::getInterface( const quint32 _interfaceId )								\
{																						\
	switch( _interfaceId )																\
	{																					\


/*---------------------------------------------------------------------------*/


#define INTERFACE_DECLARATION( INTERFACE_ID, INTERFACE_POINTER )						\
																						\
	case ( INTERFACE_ID ):																\
		return INTERFACE_POINTER;														\


/*---------------------------------------------------------------------------*/


#define END_INTERFACE_MAP()																\
																						\
		default:																		\
			return boost::intrusive_ptr< Tools::Core::IBase >();						\
	}																					\
}																						\


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_INTERFACE_MAP_HPP__
