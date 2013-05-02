
#ifndef __MM_MULTITHREADING_MANAGER_HPP__
#define __MM_MULTITHREADING_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

class MultithreadingManager
	:	public Tools::Core::BaseWrapper< IMultithreadingManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MultithreadingManager();

	virtual ~MultithreadingManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void run( RunnableFunction _function );

	/*virtual*/ void run(
			const QString& _threadName
		,	RunnableFunction _function
		,	const unsigned int _period );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void stop( const QString& _threadName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, boost::shared_ptr< QThread > >
		ThreadsCollection;
	typedef
		ThreadsCollection::iterator
		ThreadsCollectionIterator;

/*---------------------------------------------------------------------------*/

	QThreadPool m_threadPool;

	ThreadsCollection m_threadsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_MULTITHREADING_MANAGER_HPP__
