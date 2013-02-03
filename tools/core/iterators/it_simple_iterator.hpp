
#ifndef __IT_SIMPLE_ITERATOR_HPP__
#define __IT_SIMPLE_ITERATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "iterators/it_iiterator.hpp"
#include "iterators/it_value_extractors.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

template<
		typename _TCollectionType
	,	template < typename _TIteratorType, typename _TReturnType >
		class _TExtractorType = SimpleExtractor
	>
class SimpleIterator
	:	public IIterator< typename _TExtractorType< typename _TCollectionType::const_iterator, typename _TCollectionType::value_type >::ReturnType >
{

/*---------------------------------------------------------------------------*/

	typedef
		_TCollectionType
		CollectionType;

	typedef
		typename CollectionType::const_iterator
		CollectionIteratorType;

	typedef
		typename _TCollectionType::value_type
		CollectionValueType;

	typedef
		IIterator< typename _TExtractorType< CollectionIteratorType, CollectionValueType >::ReturnType >
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

	/*virtual*/ typename BaseClass::ReturnType current() const
	{ return _TExtractorType< CollectionIteratorType, CollectionValueType >().extract( m_begin ); }

	/*virtual*/ void next() { ++m_begin; }

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	CollectionIteratorType m_begin;

	CollectionIteratorType m_end;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __IT_SIMPLE_ITERATOR_HPP__
