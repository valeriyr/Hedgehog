
#ifndef __LM_IGENERATE_RESOURCES_COMPONENT_HPP__
#define __LM_IGENERATE_RESOURCES_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IGenerateResourcesComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		typedef
			std::map< QString, int >
			ResourcesByMinuteCollection;
		typedef
			ResourcesByMinuteCollection::const_iterator
			ResourcesByMinuteCollectionIterator;

		StaticData()
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

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual bool isGeneratingEnabled() const = 0;

	virtual void enableGenerating( const bool _enable ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IGENERATE_RESOURCES_COMPONENT_HPP__
