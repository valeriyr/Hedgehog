
#ifndef __LM_NOTIFICATION_CENTER_HPP__
#define __LM_NOTIFICATION_CENTER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/notification_center/lm_inotification_center.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct INotifier;

/*---------------------------------------------------------------------------*/

class NotificationCenter
	:	public Tools::Core::BaseWrapper< INotificationCenter >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	NotificationCenter();

	virtual ~NotificationCenter();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addNotifier( INotifier* _notifier );

	/*virtual*/ void removeNotifier( INotifier* _notifier );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processNotifiers();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::set< INotifier* >
		NotifiersCollection;
	typedef
		NotifiersCollection::const_iterator
		NotifiersCollectionIterator;

/*---------------------------------------------------------------------------*/

	NotifiersCollection m_notifiers;

	// We don't need synchronization here becouse all model is synchronized
	// QMutex m_mutex;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_NOTIFICATION_CENTER_HPP__
