
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_set_surface_item_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SetSurfaceItemAction::SetSurfaceItemAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	const QPoint& _position
	,	const Core::LandscapeModel::ISurfaceItem::IdType& _id
	)
	:	BaseAction( _environment, _landscapeModel )
	,	m_position( _position )
	,	m_id( _id )
{
} // SetSurfaceItemAction::SetSurfaceItemAction


/*---------------------------------------------------------------------------*/


SetSurfaceItemAction::~SetSurfaceItemAction()
{
} // SetSurfaceItemAction::~SetSurfaceItemAction


/*---------------------------------------------------------------------------*/


void
SetSurfaceItemAction::processAction( const unsigned int /*_deltaTime*/ )
{
	{
		boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			handle->getLandscape()->setSurfaceItem( m_position, m_id );
		}
	}

	Framework::Core::EventManager::Event surfaceItemChangedEvent( Events::SurfaceItemChanged::ms_type );
	surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemIdAttribute, m_id );
	surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemPositionAttribute, m_position );

	m_environment.riseEvent( surfaceItemChangedEvent );

} // SetSurfaceItemAction::processAction


/*---------------------------------------------------------------------------*/


void
SetSurfaceItemAction::unprocessAction( const unsigned int /*_deltaTime*/ )
{
} // SetSurfaceItemAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
SetSurfaceItemAction::hasFinished() const
{
	return true;

} // SetSurfaceItemAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
