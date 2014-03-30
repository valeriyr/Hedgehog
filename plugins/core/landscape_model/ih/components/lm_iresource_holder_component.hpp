
#ifndef __LM_IRESOURCE_HOLDER_COMPONENT_HPP__
#define __LM_IRESOURCE_HOLDER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/lm_resources_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IResourceHolderComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		StaticData()
			:	m_maxResourcesValue()
		{}

		void hold( const QString& _resourceName, const int _maxValue )
		{
			m_maxResourcesValue.pushResource( _resourceName, _maxValue );
		}

		ResourcesData m_maxResourcesValue;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual ResourcesData& holdResources() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IRESOURCE_HOLDER_COMPONENT_HPP__
