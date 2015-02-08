
#ifndef __CM_ICOMMANDS_REGISTRY_HPP__
#define __CM_ICOMMANDS_REGISTRY_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "iterators/it_simple_iterator.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

struct ICommand;

/*---------------------------------------------------------------------------*/

	const quint32 IID_COMMANDS_REGISTRY = 0;

/*---------------------------------------------------------------------------*/

struct ICommandsRegistry
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, boost::intrusive_ptr< ICommand > >
		CommandsCollectionType;

	typedef
		Tools::Core::SimpleIterator< CommandsCollectionType, Tools::Core::FirstExtractor >
		CommandsIteratorType;

	typedef
		boost::shared_ptr< CommandsIteratorType >
		CommandsIteratorTypePtr;

/*---------------------------------------------------------------------------*/

	virtual void registerCommand(
			const QString& _commandName
		,	boost::intrusive_ptr< ICommand > _command ) = 0;

	virtual boost::intrusive_ptr< ICommand >
		unregisterCommand( const QString& _commandName ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ICommand >
		getCommand( const QString& _commandName ) const = 0;

	virtual CommandsIteratorTypePtr getCommandsList() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_ICOMMANDS_REGISTRY_HPP__
