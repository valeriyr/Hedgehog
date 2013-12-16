
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_create_object_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


CreateObjectAction::CreateObjectAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	const QPoint& _position
	,	const QString& _objectName
	)
	:	BaseAction( _environment, _landscapeModel )
	,	m_position( _position )
	,	m_objectName( _objectName )
{
} // CreateObjectAction::CreateObjectAction


/*---------------------------------------------------------------------------*/


CreateObjectAction::~CreateObjectAction()
{
} // CreateObjectAction::~CreateObjectAction


/*---------------------------------------------------------------------------*/


void
CreateObjectAction::processAction( const unsigned int /*_deltaTime*/ )
{
	int unitId = IUnit::ms_wrongId;

	{
		boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			unitId = handle->getLandscape()->createObject( m_position, m_objectName );
		}
	}

	if ( unitId != IUnit::ms_wrongId )
	{
		Framework::Core::EventManager::Event objectCreatedEvent( Events::ObjectCreated::ms_type );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectNameAttribute, m_objectName );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectPositionAttribute, m_position );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectUniqueIdAttribute, unitId );

		m_environment.riseEvent( objectCreatedEvent );
	}

} // CreateObjectAction::processAction


/*---------------------------------------------------------------------------*/


void
CreateObjectAction::unprocessAction( const unsigned int /*_deltaTime*/ )
{
} // CreateObjectAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
CreateObjectAction::hasFinished() const
{
	return true;

} // CreateObjectAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
