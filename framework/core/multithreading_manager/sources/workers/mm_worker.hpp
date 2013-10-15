
#ifndef __MM_WORKER_HPP__
#define __MM_WORKER_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/h/mm_runnable_function.hpp"
#include "multithreading_manager/sources/tasks_queue/mm_tasks_queue.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

class Worker
	:	public QObject
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Worker( QObject* _parent = NULL );

	virtual ~Worker();

/*---------------------------------------------------------------------------*/

	QString pushTask( RunnableFunction _function, const qint64 _period );

	void removeTask( const QString& _taskId );

	void refreshPeriodicalTasks();

/*---------------------------------------------------------------------------*/

	void clear();

	void stop();

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void doWork();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QSemaphore m_semaphore;

	TasksQueue m_tasksQueue;

	bool m_stopped;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_WORKER_HPP__
