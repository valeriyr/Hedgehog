
#ifndef __CM_EXCEPTIONS_HPP__
#define __CM_EXCEPTIONS_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_iexceptions.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

template < typename _TBaseInterface >
class BaseException
	:	public Tools::Core::BaseWrapper< _TBaseInterface >
{

public:

	BaseException( const QString& _commandName );

	virtual ~BaseException();

protected:

	const QString m_commandName;

};

/*---------------------------------------------------------------------------*/

class UnknownCommandException
	:	public BaseException< IUnknownCommandException >
{

public:

	UnknownCommandException( const QString& _commandName );

	virtual ~UnknownCommandException();

public:

	/*virtual*/ QString what() const;
};

/*---------------------------------------------------------------------------*/

class DisabledCommandException
	:	public BaseException< IDisabledCommandException >
{

public:

	DisabledCommandException( const QString& _commandName );

	virtual ~DisabledCommandException();

public:

	/*virtual*/ QString what() const;
};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_EXCEPTIONS_HPP__
