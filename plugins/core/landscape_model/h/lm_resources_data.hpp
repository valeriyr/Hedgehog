
#ifndef __LM_RESOURCES_DATA_HPP__
#define __LM_RESOURCES_DATA_HPP__

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

	ResourcesDataCollection m_data;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_RESOURCES_DATA_HPP__