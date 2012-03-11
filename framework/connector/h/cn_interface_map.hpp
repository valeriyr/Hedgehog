
/** Interface map macroses */

#ifndef __CN_INTERFACE_MAP_HPP__
#define __CN_INTERFACE_MAP_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


#define INTERFACE_MAP_DECLARATION()											\
																			\
	/*virtual*/ IBase* getInterface( const unsigned int _interfaceId );		\


/*---------------------------------------------------------------------------*/


#define BEGIN_INTERFACE_MAP( PLUGIN_INSTANCE )								\
																			\
IBase*																		\
PLUGIN_INSTANCE::getInterface( const unsigned int _interfaceId )			\
{																			\
	switch( _interfaceId )													\
	{																		\


/*---------------------------------------------------------------------------*/


#define INTERFACE( INTERFACE_ID, INTERFACE_POINTER )						\
																			\
	case ( INTERFACE_ID ):													\
		return INTERFACE_POINTER;											\


/*---------------------------------------------------------------------------*/


#define END_INTERFACE_MAP()													\
																			\
		default:															\
			return NULL;													\
	}																		\
}																			\


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_INTERFACE_MAP_HPP__
