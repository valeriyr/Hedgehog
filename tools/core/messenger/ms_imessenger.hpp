
#ifndef __MS_IMESSENGER_HPP__
#define __MS_IMESSENGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

	const quint32 IID_MESSENGER = 1000;

/*---------------------------------------------------------------------------*/

struct IMessenger
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct MessegeLevel
	{
		enum Enum : qint32
		{
				Info	= 0
			,	Warning
			,	Error
			,	Success
		};

		static QString toString( const Enum _level )
		{
			switch( _level )
			{
			case Info:
				return "Info";
			case Warning:
				return "Warning";
			case Error:
				return "Error";
			case Success:
				return "Success";
			default:
				break;
			}

			return "Unknown Level";
		}
	};

/*---------------------------------------------------------------------------*/

	virtual void printMessage(
			const MessegeLevel::Enum _messageLevel
		,	const QString& _message ) = 0;

	virtual void printMessage(
			const QString& _moduleName
		,	const MessegeLevel::Enum _messageLevel
		,	const QString& _message ) = 0;

	virtual void printMessage( const QString& _message ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __MS_IMESSENGER_HPP__
