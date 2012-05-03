
#ifndef __IT_SIMPLE_ITERATOR_HPP__
#define __IT_SIMPLE_ITERATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "iterators/it_iiterator.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {

/*---------------------------------------------------------------------------*/

template< typename _TReturnType, typename _TCollectionType >
class SimpleIterator
	:	public IIterator< _TReturnType >
{

/*---------------------------------------------------------------------------*/

	typedef
		_TCollectionType
		CollectionType;

	typedef
		typename CollectionType::const_iterator
		CollectionIteratorType;

	typedef
		IIterator< _TReturnType >
		BaseClass;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SimpleIterator( const CollectionType& _collection )
		:	m_begin( _collection.begin() )
		,	m_end( _collection.end() )
	{}

	virtual ~SimpleIterator() {}

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isValid() const { return m_begin != m_end; }

	/*virtual*/ typename BaseClass::ReturnType current() const { return *m_begin; }

	/*virtual*/ void next() { ++m_begin; }

/*---------------------------------------------------------------------------*/

	CollectionIteratorType m_begin;

	CollectionIteratorType m_end;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __IT_SIMPLE_ITERATOR_HPP__
