
#ifndef __LM_IRESOURCE_SOURCE_COMPONENT_HPP__
#define __LM_IRESOURCE_SOURCE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IResourceSourceComponent
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

	virtual const int getResourceValue() const = 0;

	virtual void setResourceValue( const int _value ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const Tools::Core::Generators::IGenerator::IdType& getObjectInside() const = 0;

	virtual void setObjectInside( const Tools::Core::Generators::IGenerator::IdType& _id ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IRESOURCE_SOURCE_COMPONENT_HPP__
