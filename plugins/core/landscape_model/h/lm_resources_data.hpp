
#ifndef __LM_RESOURCES_DATA_HPP__
#define __LM_RESOURCES_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/utils/lm_math.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ResourcesData
{
	typedef
		std::map< QString, int >
		ResourcesDataCollection;
	typedef
		ResourcesDataCollection::iterator
		ResourcesDataCollectionIterator;
	typedef
		ResourcesDataCollection::const_iterator
		ResourcesDataCollectionConstIterator;

	int getResourceValue( const QString& _resourceName ) const
	{
		ResourcesDataCollectionConstIterator iterator = m_data.find( _resourceName );
		assert( iterator != m_data.end() );

		return iterator->second;
	}

	void pushResource( const QString& _resourceName, const int _value )
	{
		assert( m_data.find( _resourceName ) == m_data.end() );

		m_data.insert( std::make_pair( _resourceName, _value ) );
	}

	bool isEnaught( const ResourcesData& _data ) const
	{
		ResourcesDataCollectionConstIterator
				begin = _data.m_data.begin()
			,	end = _data.m_data.end();

		for ( ; begin != end; ++begin )
		{
			ResourcesDataCollectionConstIterator iterator = m_data.find( begin->first );

			if ( iterator == m_data.end() || iterator->second < begin->second )
			{
				return false;
			}
		}

		return true;
	}

	void substruct( const ResourcesData& _data )
	{
		ResourcesDataCollectionConstIterator
				begin = _data.m_data.begin()
			,	end = _data.m_data.end();

		for ( ; begin != end; ++begin )
		{
			ResourcesDataCollectionIterator iterator = m_data.find( begin->first );

			if ( iterator == m_data.end() )
				continue;

			iterator->second -= begin->second;
		}
	}

	void add( const ResourcesData& _data )
	{
		ResourcesDataCollectionConstIterator
				begin = _data.m_data.begin()
			,	end = _data.m_data.end();

		for ( ; begin != end; ++begin )
		{
			ResourcesDataCollectionIterator iterator = m_data.find( begin->first );

			if ( iterator == m_data.end() )
				continue;

			iterator->second += begin->second;
		}
	}

	ResourcesData getResourceDataPart( const int _percent ) const
	{
		ResourcesData returnValue;

		ResourcesDataCollectionConstIterator
				begin = m_data.begin()
			,	end = m_data.end();

		for ( ; begin != end; ++begin )
			returnValue.pushResource( begin->first, Math::calculatePart( begin->second, _percent, 100 ) );

		return returnValue;
	}

	ResourcesDataCollection m_data;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_RESOURCES_DATA_HPP__