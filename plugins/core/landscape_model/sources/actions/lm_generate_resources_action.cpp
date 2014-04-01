
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_generate_resources_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/ih/components/lm_igenerate_resources_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


GenerateResourcesAction::GenerateResourcesAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
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
GenerateResourcesAction::processAction( const unsigned int _deltaTime )
{
	if ( m_object.getState() == ObjectState::Dying )
		return;

	boost::intrusive_ptr< IGenerateResourcesComponent > generateResourcesComponent
		= m_object.getComponent< IGenerateResourcesComponent >( ComponentId::ResourcesGenerating );

	IGenerateResourcesComponent::StaticData::ResourcesByMinuteCollectionIterator
			begin = generateResourcesComponent->getStaticData().m_resourcesByMinute.begin()
		,	end = generateResourcesComponent->getStaticData().m_resourcesByMinute.end();

	ResourcesData resources;

	for ( ; begin != end; ++begin )
	{
		int incTo = static_cast< float >( _deltaTime * begin->second ) / 60000;
		resources.pushResource( begin->first, incTo );
	}

	m_landscapeModel.getPlayer( m_object.getPlayerId() )->addResources( resources );

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
