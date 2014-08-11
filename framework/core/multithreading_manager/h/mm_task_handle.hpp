
#ifndef __MM_TASK_HANDLE_HPP__
#define __MM_TASK_HANDLE_HPP__


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

	struct TaskHandle
	{
		TaskHandle()
			:	m_threadName()
			,	m_taskId()
		{}

		TaskHandle( const QString& _threadName, const QString& _taskId )
			:	m_threadName( _threadName )
			,	m_taskId( _taskId )
		{}

		bool isValid() const
		{
			return !m_taskId.isEmpty();
		}

		void reset()
		{
			m_threadName.clear();
			m_taskId.clear();
		}

		QString m_threadName;
		QString m_taskId;
	};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_TASK_HANDLE_HPP__
