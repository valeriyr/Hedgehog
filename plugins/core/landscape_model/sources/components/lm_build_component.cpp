
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_build_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuildComponent::BuildComponent(
		Object& _object
	,	const BuildComponentStaticData& _staticData
	)
	:	BaseComponent< IBuildComponent >( _object )
	,	m_staticData( _staticData )
	,	m_buildData()
{
} // BuildComponent::BuildComponent


/*---------------------------------------------------------------------------*/


BuildComponent::~BuildComponent()
{
} // BuildComponent::~BuildComponent


/*---------------------------------------------------------------------------*/


const BuildComponentStaticData&
BuildComponent::getStaticData() const
{
	return m_staticData;

} // BuildComponent::getStaticData


/*---------------------------------------------------------------------------*/


IBuildComponent::BuildData&
BuildComponent::getBuildData()
{
	return m_buildData;

} // BuildComponent::getBuildData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
