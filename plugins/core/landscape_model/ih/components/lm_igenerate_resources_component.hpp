
#ifndef __LM_IGENERATE_RESOURCES_COMPONENT_HPP__
#define __LM_IGENERATE_RESOURCES_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_resources_data.hpp"

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
		StaticData()
			:	m_resourcesByTick()
		{}

		void canGenerate( const QString& _resourceName, const int _value )
		{
			m_resourcesByTick.pushResource( _resourceName, _value );
		}

		ResourcesData m_resourcesByTick;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IGENERATE_RESOURCES_COMPONENT_HPP__
