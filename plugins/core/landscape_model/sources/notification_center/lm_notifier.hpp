
#ifndef __LM_NOTIFIER_HPP__
#define __LM_NOTIFIER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/notification_center/lm_inotifier.hpp"
#include "landscape_model/sources/notification_center/lm_inotification_center.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

template< typename _TNotifierClass >
class Notifier
	:	public INotifier
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	typedef void (_TNotifierClass::*NotifyFunction)();

/*---------------------------------------------------------------------------*/

	Notifier( INotificationCenter& _notificationCenter, _TNotifierClass* _notifier )
		:	m_notificationCenter( _notificationCenter )
		,	m_notifier( _notifier )
		,	m_notifyFunctions()
	{
		m_notificationCenter.addNotifier( this );
	}

	virtual ~Notifier()
	{
		m_notifyFunctions.clear();
		m_notificationCenter.removeNotifier( this );
	}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void notify()
	{
		NotifyFunctionsCollectionIterator
				begin = m_notifyFunctions.begin()
			,	end = m_notifyFunctions.end();

		for ( ; begin != end; ++begin )
			(m_notifier->**begin)();

		m_notifyFunctions.clear();
	}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushNotifyFunction( NotifyFunction _notifyFunction )
	{
		NotifyFunctionsCollectionIterator
				begin = m_notifyFunctions.begin()
			,	end = m_notifyFunctions.end();

		for ( ; begin != end; ++begin )
		{
			if ( _notifyFunction == *begin )
				return;
		}

		m_notifyFunctions.push_back( _notifyFunction );
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< NotifyFunction >
		NotifyFunctionsCollection;
	typedef
		typename NotifyFunctionsCollection::const_iterator
		NotifyFunctionsCollectionIterator;

/*---------------------------------------------------------------------------*/

	INotificationCenter& m_notificationCenter;

	_TNotifierClass* m_notifier;

	NotifyFunctionsCollection m_notifyFunctions;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_NOTIFIER_HPP__
