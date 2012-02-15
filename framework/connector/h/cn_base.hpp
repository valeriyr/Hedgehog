/** Base implementation for all classes witch use intrusive pointer */

#ifndef __CN_IBASE_HPP_
#define __CN_IBASE_HPP_

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

template< typename _Base >
class BaseWrapper
	:	public _Base
{

/*---------------------------------------------------------------------------*/

	BaseWrapper()
		:	m_counter( 0 )

	~BaseWrapper();

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

	unsigned int m_counter;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IBASE_HPP_
