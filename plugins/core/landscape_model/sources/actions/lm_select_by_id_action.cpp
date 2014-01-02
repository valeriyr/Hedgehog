
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_select_by_id_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SelectByIdAction::SelectByIdAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	const IObject::IdType& _id
	)
	:	BaseAction( _environment, _landscapeModel )
	,	m_id( _id )
{
} // SelectByIdAction::SelectByIdAction


/*---------------------------------------------------------------------------*/


SelectByIdAction::~SelectByIdAction()
{
} // SelectByIdAction::~SelectByIdAction


/*---------------------------------------------------------------------------*/


void
SelectByIdAction::processAction( const unsigned int /*_deltaTime*/ )
{
	{
		boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			handle->getLandscape()->selectObject( m_id );
		}
	}

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );

} // SelectByIdAction::processAction


/*---------------------------------------------------------------------------*/


void
SelectByIdAction::unprocessAction( const unsigned int /*_deltaTime*/ )
{
} // SelectByIdAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
SelectByIdAction::hasFinished() const
{
	return true;

} // SelectByIdAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
