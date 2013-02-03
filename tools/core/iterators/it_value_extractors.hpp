
#ifndef __IT_VALUE_EXTRUCTORS_HPP__
#define __IT_VALUE_EXTRUCTORS_HPP__


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

template< typename _TIteratorType, typename _TReturnType >
struct SimpleExtractor
{
	typedef _TReturnType ReturnType;

	ReturnType extract( const _TIteratorType& _iterator ) const
	{
		return *_iterator;
	}
};

/*---------------------------------------------------------------------------*/

template< typename _TIteratorType, typename _TReturnType >
struct FirstExtractor
{
	typedef typename _TReturnType::first_type ReturnType;

	ReturnType extract( const _TIteratorType& _iterator ) const
	{
		return _iterator->first;
	}
};

/*---------------------------------------------------------------------------*/

template< typename _TIteratorType, typename _TReturnType >
struct SecondExtractor
{
	typedef typename _TReturnType::second_type ReturnType;

	ReturnType extract( const _TIteratorType& _iterator ) const
	{
		return _iterator->second;
	}
};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __IT_VALUE_EXTRUCTORS_HPP__
