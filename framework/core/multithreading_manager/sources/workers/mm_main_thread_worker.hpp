
#ifndef __MM_MAIN_THREAD_WORKER_HPP__
#define __MM_MAIN_THREAD_WORKER_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/h/mm_runnable_function.hpp"
#include "multithreading_manager/sources/tasks_queue/mm_tasks_queue.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

class MainThreadWorker
	:	public QObject
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	static const unsigned int ms_period = 100;

/*---------------------------------------------------------------------------*/

	MainThreadWorker( QObject* _parent = NULL );

	virtual ~MainThreadWorker();

/*---------------------------------------------------------------------------*/

	QString pushTask( RunnableFunction _function, const qint64 _period );

	void removeTask( const QString& _taskId );

	void clear();

	void refreshPeriodicalTasks();

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void start();

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void doWork();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static const unsigned int ms_oneTickTimeLimit = 50;

	QTimer* m_timer;

	TasksQueue m_tasksQueue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_WORKER_HPP__
