
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/notification_center/lm_notification_center.hpp"

#include "landscape_model/sources/notification_center/lm_inotifier.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


NotificationCenter::NotificationCenter()
	:	m_notifiers()
	,	m_mutex()
{
} // NotificationCenter::NotificationCenter


/*---------------------------------------------------------------------------*/


NotificationCenter::~NotificationCenter()
{
} // NotificationCenter::~NotificationCenter


/*---------------------------------------------------------------------------*/


void
NotificationCenter::addNotifier( INotifier* _notifier )
{
	QMutexLocker locker( &m_mutex );

	assert( m_notifiers.find( _notifier ) == m_notifiers.end() );

	m_notifiers.insert( _notifier );

} // NotificationCenter::addNotifier


/*---------------------------------------------------------------------------*/


void
NotificationCenter::removeNotifier( INotifier* _notifier )
{
	QMutexLocker locker( &m_mutex );

	m_notifiers.erase( _notifier );

} // NotificationCenter::removeNotifier


/*---------------------------------------------------------------------------*/


void
NotificationCenter::processNotifiers()
{
	QMutexLocker locker( &m_mutex );

	NotifiersCollectionIterator
			begin = m_notifiers.begin()
		,	end = m_notifiers.end();

	for ( ; begin != end; ++begin )
		( *begin )->notify();

} // NotificationCenter::processNotifiers


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
