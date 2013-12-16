
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
	boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->createObject( m_position, m_objectName );

		Framework::Core::EventManager::Event objectCreatedEvent( Events::ObjectCreated::ms_type );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectNameAttribute, m_objectName );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectPositionAttribute, m_position );

		m_environment.riseEvent( objectCreatedEvent );
	}

} // CreateObjectAction::processAction


/*---------------------------------------------------------------------------*/


void
CreateObjectAction::unprocessAction( const unsigned int /*_deltaTime*/ )
{
	/*boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->unselectUnits();
		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::UnitsSelectionChanged::ms_type ) );
	}*/

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
