
#ifndef __IB_BASE_WRAPPER_HPP__
#define __IB_BASE_WRAPPER_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

template< typename _TBase >
class BaseWrapper
	:	public _TBase
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseWrapper()
		:	m_counter( 0 )
	{}

	virtual ~BaseWrapper() {}

/*---------------------------------------------------------------------------*/

	virtual void addRef()
	{
		++m_counter;
	}

	virtual void releaseRef()
	{
		if ( --m_counter == 0 )
			delete this;
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	// TODO: should be atomic
	volatile unsigned int m_counter;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __IB_BASE_WRAPPER_HPP__
