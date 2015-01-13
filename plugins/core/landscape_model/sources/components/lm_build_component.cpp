
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_build_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuildComponent::BuildComponent(
		GameObject& _object
	,	const IBuildComponent::StaticData& _staticData
	)
	:	BaseComponent< IBuildComponent >( _object )
	,	m_staticData( _staticData )
	,	m_data()
{
} // BuildComponent::BuildComponent


/*---------------------------------------------------------------------------*/


BuildComponent::~BuildComponent()
{
} // BuildComponent::~BuildComponent


/*---------------------------------------------------------------------------*/


const IBuildComponent::StaticData&
BuildComponent::getStaticData() const
{
	return m_staticData;

} // BuildComponent::getStaticData


/*---------------------------------------------------------------------------*/


IBuildComponent::Data&
BuildComponent::getBuildData()
{
	return m_data;

} // BuildComponent::getBuildData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
