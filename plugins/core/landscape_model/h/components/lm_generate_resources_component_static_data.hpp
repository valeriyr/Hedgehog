
#ifndef __LM_GENERATE_RESOURCES_COMPONENT_STATIC_DATA_HPP__
#define __LM_GENERATE_RESOURCES_COMPONENT_STATIC_DATA_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct GenerateResourcesComponentStaticData
{
	typedef
		std::map< QString, int >
		ResourcesByMinuteCollection;
	typedef
		ResourcesByMinuteCollection::const_iterator
		ResourcesByMinuteCollectionIterator;

	GenerateResourcesComponentStaticData()
		:	m_resourcesByMinute()
	{}

	void canGenerate( const QString& _resourceName, const int _value )
	{
		assert( m_resourcesByMinute.find( _resourceName ) == m_resourcesByMinute.end() );

		m_resourcesByMinute.insert( std::make_pair( _resourceName, _value ) );
	}

	ResourcesByMinuteCollection m_resourcesByMinute;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_GENERATE_RESOURCES_COMPONENT_STATIC_DATA_HPP__
