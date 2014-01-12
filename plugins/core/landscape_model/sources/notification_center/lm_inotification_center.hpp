
#ifndef __LM_INOTIFICATION_CENTER_HPP__
#define __LM_INOTIFICATION_CENTER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct INotifier;

/*---------------------------------------------------------------------------*/

struct INotificationCenter
	: public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void addNotifier( INotifier* _notifier ) = 0;

	virtual void removeNotifier( INotifier* _notifier ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void processNotifiers() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_INOTIFICATION_CENTER_HPP__
