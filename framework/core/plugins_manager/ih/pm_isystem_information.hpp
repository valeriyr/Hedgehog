
#ifndef __PM_ISYSTEM_INFORMATION_HPP__
#define __PM_ISYSTEM_INFORMATION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "iterators/it_iiterator.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

	const quint32 IID_SYSTEM_INFORMATION = 0;

/*---------------------------------------------------------------------------*/

struct ISystemInformation
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::shared_ptr< Tools::Core::IIterator< QString > >
		AdditionalPluginsDirectoriesIterator;

/*---------------------------------------------------------------------------*/

	virtual const QString& getApplicationDirectory() const = 0;

	virtual const QString& getPluginsDirectory() const = 0;

	virtual const QString& getConfigDirectory() const = 0;

	virtual const QString& getResourcesDirectory() const = 0;

	virtual const QString& getApplicationName() const = 0;

	virtual const QString& getSystemMessengerPluginName() const = 0;

	virtual AdditionalPluginsDirectoriesIterator getAdditionalPluginsDirectories() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_ISYSTEM_INFORMATION_HPP__
