
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_generate_resources_action.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


GenerateResourcesAction::GenerateResourcesAction(
		const IEnvironment& _environment
	,	Object& _object
	,	IPlayer& _player
	)
	:	BaseAction( _environment, _object )
	,	m_player( _player )
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
	boost::intrusive_ptr< IGenerateResourcesComponent > generateResourcesComponent
		= m_object.getComponent< IGenerateResourcesComponent >( ComponentId::ResourcesGenerating );

	if ( generateResourcesComponent->isGeneratingEnabled() )
	{
		GenerateResourcesComponentStaticData::ResourcesByMinuteCollectionIterator
				begin = generateResourcesComponent->getStaticData().m_resourcesByMinute.begin()
			,	end = generateResourcesComponent->getStaticData().m_resourcesByMinute.end();

		for ( ; begin != end; ++begin )
		{
			int incTo = static_cast< float >( _deltaTime * begin->second ) / 60000;
			m_player.getResourcesData().incResource( begin->first, incTo );

			Framework::Core::EventManager::Event resourceValueChangedEvent( Events::ResourceValueChanged::ms_type );
			resourceValueChangedEvent.pushAttribute( Events::ResourceValueChanged::ms_resourceNameAttribute, begin->first );
			resourceValueChangedEvent.pushAttribute( Events::ResourceValueChanged::ms_resourceValueAttribute, m_player.getResourcesData().getResourceValue( begin->first ) );

			m_environment.riseEvent( resourceValueChangedEvent );
		}
	}

} // MoveAction::processAction


/*---------------------------------------------------------------------------*/


void
GenerateResourcesAction::unprocessAction( const unsigned int _deltaTime )
{
} // GenerateResourcesAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
GenerateResourcesAction::hasFinished() const
{
	return false;

} // GenerateResourcesAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
GenerateResourcesAction::getType() const
{
	return Actions::GenerateResources;

} // GenerateResourcesAction::getType


/*---------------------------------------------------------------------------*/


void
GenerateResourcesAction::updateWithData( const QVariant& _data )
{
} // GenerateResourcesAction::updateWithData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
