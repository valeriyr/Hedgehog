
#ifndef __LM_IRESOURCE_HOLDER_COMPONENT_HPP__
#define __LM_IRESOURCE_HOLDER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

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
		StaticData( const QString& _resource )
			:	m_resource( _resource )
		{}

		const QString m_resource;
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

#endif // __LM_IRESOURCE_HOLDER_COMPONENT_HPP__
