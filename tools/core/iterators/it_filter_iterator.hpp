
#ifndef __IT_FILTER_ITERATOR_HPP__
#define __IT_FILTER_ITERATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "iterators/it_iiterator.hpp"
#include "iterators/it_value_extractors.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

template<
		typename _TCollectionType
	,	template < typename _TIteratorType >
		class _TFilterType
	,	template < typename _TIteratorType, typename _TReturnType >
		class _TExtractorType = SimpleExtractor
	>
class FilterIterator
	:	public IIterator<
			typename _TExtractorType<
					typename _TCollectionType::const_iterator
				,	typename _TCollectionType::value_type
				>::ReturnType
			>
{

/*---------------------------------------------------------------------------*/

	typedef
		typename _TCollectionType::const_iterator
		CollectionIteratorType;

	typedef
		_TExtractorType< CollectionIteratorType, typename _TCollectionType::value_type >
		ExtractorType;

	typedef
		_TFilterType< CollectionIteratorType >
		FilterType;

	typedef
		IIterator< typename ExtractorType::ReturnType >
		BaseClass;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	FilterIterator( const _TCollectionType& _collection )
		:	m_begin( _collection.begin() )
		,	m_end( _collection.end() )
		,	m_filter()
	{
		findNextElement();
	}

	FilterIterator( const _TCollectionType& _collection, const FilterType& _filter )
		:	m_begin( _collection.begin() )
		,	m_end( _collection.end() )
		,	m_filter( _filter )
	{
		findNextElement();
	}

	virtual ~FilterIterator() {}

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isValid() const { return m_begin != m_end; }

	/*virtual*/ typename BaseClass::ReturnType current() const { return ExtractorType().extract( m_begin ); }

	/*virtual*/ void next() { ++m_begin; findNextElement(); }

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void findNextElement()
	{
		while ( m_begin != m_end )
		{
			if ( m_filter.check( m_begin ) )
				break;

			++m_begin;
		}
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	CollectionIteratorType m_begin;

	CollectionIteratorType m_end;

	FilterType m_filter;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __IT_FILTER_ITERATOR_HPP__
