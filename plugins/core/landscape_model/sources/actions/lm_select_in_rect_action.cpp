
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_select_in_rect_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SelectInRectAction::SelectInRectAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	const QRect& _rect
	)
	:	BaseAction( _environment, _landscapeModel )
	,	m_rect( _rect )
{
} // SelectInRectAction::SelectInRectAction


/*---------------------------------------------------------------------------*/


SelectInRectAction::~SelectInRectAction()
{
} // SelectInRectAction::~SelectInRectAction


/*---------------------------------------------------------------------------*/


void
SelectInRectAction::processAction( const unsigned int /*_deltaTime*/ )
{
	{
		boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			handle->getLandscape()->selectUnits( m_rect );
		}
	}

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::UnitsSelectionChanged::ms_type ) );

} // SelectInRectAction::processAction


/*---------------------------------------------------------------------------*/


void
SelectInRectAction::unprocessAction( const unsigned int /*_deltaTime*/ )
{
	{
		boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			handle->getLandscape()->unselectUnits();
		}
	}

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::UnitsSelectionChanged::ms_type ) );

} // SelectInRectAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
SelectInRectAction::hasFinished() const
{
	return true;

} // SelectInRectAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
