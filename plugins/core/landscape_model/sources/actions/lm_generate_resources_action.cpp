
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_generate_resources_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


GenerateResourcesAction::GenerateResourcesAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	GameObject& _object
	)
	:	BaseAction( _environment, _landscapeModel, _object )
{
} // GenerateResourcesAction::GenerateResourcesAction


/*---------------------------------------------------------------------------*/


GenerateResourcesAction::~GenerateResourcesAction()
{
} // GenerateResourcesAction::~GenerateResourcesAction


/*---------------------------------------------------------------------------*/


void
GenerateResourcesAction::processAction()
{
	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
		return;

	Tools::Core::Object::Ptr generateResourcesComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( GenerateResourcesComponent::Name );
	Tools::Core::Object::Ptr playerComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	m_landscapeModel.getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) )
		->addResources( generateResourcesComponent->getMember< ResourcesData >( GenerateResourcesComponent::StaticData::ResourcesByTick ) );

} // GenerateResourcesAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
GenerateResourcesAction::getType() const
{
	return Actions::GenerateResources;

} // GenerateResourcesAction::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
