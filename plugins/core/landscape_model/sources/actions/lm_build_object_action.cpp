
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_build_object_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuildObjectAction::BuildObjectAction(
		const IEnvironment& _environment
	,	Object& _object
	,	IPlayer& _player
	)
	:	BaseAction( _environment, _object )
	,	m_player( _player )
{
} // BuildObjectAction::BuildObjectAction


/*---------------------------------------------------------------------------*/


BuildObjectAction::~BuildObjectAction()
{
} // BuildObjectAction::~BuildObjectAction


/*---------------------------------------------------------------------------*/


void
BuildObjectAction::processAction( const unsigned int _deltaTime )
{
	/*boost::intrusive_ptr< IGenerateResourcesComponent > generateResourcesComponent
		= m_object.getComponent< IGenerateResourcesComponent >( ComponentId::ResourcesGenerating );

	if ( generateResourcesComponent->isGeneratingEnabled() )
	{
		GenerateResourcesComponentStaticData::ResourcesByMinuteCollectionIterator
				begin = generateResourcesComponent->getStaticData().m_resourcesByMinute.begin()
			,	end = generateResourcesComponent->getStaticData().m_resourcesByMinute.end();

		for ( ; begin != end; ++begin )
		{
			int incTo = static_cast< float >( _deltaTime * begin->second ) / 60000;
			m_player.incResource( begin->first, incTo );
		}
	}*/

} // BuildObjectAction::processAction


/*---------------------------------------------------------------------------*/


void
BuildObjectAction::unprocessAction( const unsigned int _deltaTime )
{
} // BuildObjectAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
BuildObjectAction::hasFinished() const
{
	return false;

} // BuildObjectAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
BuildObjectAction::getType() const
{
	return Actions::GenerateResources;

} // BuildObjectAction::getType


/*---------------------------------------------------------------------------*/


void
BuildObjectAction::updateWithData( const QVariant& _data )
{
} // BuildObjectAction::updateWithData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
