
#ifndef __MS_IMESSANGER_HPP__
#define __MS_IMESSANGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_MESSENGER = 1000;

/*---------------------------------------------------------------------------*/

struct IMessenger
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct MessegeLevel
	{
		enum Enum
		{
				Info	= 0
			,	Warning
			,	Error
		};
	};

/*---------------------------------------------------------------------------*/

	virtual void printMessage(
			const MessegeLevel::Enum _messageLevel
		,	const std::string& _message ) = 0;

	virtual void printMessage( const std::string& _message ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __MS_IMESSANGER_HPP__
