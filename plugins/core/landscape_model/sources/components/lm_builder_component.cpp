
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_builder_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuilderComponent::BuilderComponent(
		Object& _object
	,	const BuilderComponentStaticData& _staticData
	)
	:	BaseComponent< IBuilderComponent >( _object )
	,	m_staticData( _staticData )
	,	m_buildData()
{
} // BuilderComponent::BuilderComponent


/*---------------------------------------------------------------------------*/


BuilderComponent::~BuilderComponent()
{
} // BuilderComponent::~BuilderComponent


/*---------------------------------------------------------------------------*/


const BuilderComponentStaticData&
BuilderComponent::getStaticData() const
{
	return m_staticData;

} // BuilderComponent::getStaticData


/*---------------------------------------------------------------------------*/


IBuilderComponent::BuildData&
BuilderComponent::getBuildData()
{
	return m_buildData;

} // BuilderComponent::getBuildData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
