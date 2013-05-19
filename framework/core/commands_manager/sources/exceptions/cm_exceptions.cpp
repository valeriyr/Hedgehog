
#include "commands_manager/sources/ph/cm_ph.hpp"

#include "commands_manager/sources/exceptions/cm_exceptions.hpp"

#include "commands_manager/sources/resources/cm_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/


template < typename _TBaseInterface >
BaseException< _TBaseInterface >::BaseException( const QString& _commandName )
	:	m_commandName( _commandName )
{
} // BaseException< _TBaseInterface >::BaseException


/*---------------------------------------------------------------------------*/


template < typename _TBaseInterface >
BaseException< _TBaseInterface >::~BaseException()
{
} // BaseException< _TBaseInterface >::~BaseException


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


UnknownCommandException::UnknownCommandException( const QString& _commandName )
	:	BaseException< IUnknownCommandException >( _commandName )
{
} // UnknownCommandException::UnknownCommandException


/*---------------------------------------------------------------------------*/


UnknownCommandException::~UnknownCommandException()
{
} // UnknownCommandException::~UnknownCommandException


/*---------------------------------------------------------------------------*/


QString
UnknownCommandException::what() const
{
	return QString( Resources::Exceptions::UnknownCommandMessageFormat ).arg( m_commandName );

} // UnknownCommandException::what


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


DisabledCommandException::DisabledCommandException( const QString& _commandName )
	:	BaseException< IDisabledCommandException >( _commandName )
{
} // DisabledCommandException::DisabledCommandException


/*---------------------------------------------------------------------------*/


DisabledCommandException::~DisabledCommandException()
{
} // DisabledCommandException::~DisabledCommandException


/*---------------------------------------------------------------------------*/


QString
DisabledCommandException::what() const
{
	return QString( Resources::Exceptions::DisabledCommandMessageFormat ).arg( m_commandName );

} // DisabledCommandException::what


/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
