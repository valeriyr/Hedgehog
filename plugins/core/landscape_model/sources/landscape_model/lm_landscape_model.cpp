
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/sources/actions_queue/lm_actions_queue.hpp"
#include "landscape_model/sources/actions/lm_select_in_rect_action.hpp"
#include "landscape_model/sources/actions/lm_select_by_id_action.hpp"
#include "landscape_model/sources/actions/lm_create_object_action.hpp"
#include "landscape_model/sources/actions/lm_set_surface_item_action.hpp"
#include "landscape_model/sources/actions/lm_move_items_action.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/h/lm_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeModel::LandscapeModel(
		const IEnvironment& _environment
	,	const ILandscapeSerializer& _landscapeSerializer
	,	const ISurfaceItemsCache& _surfaceItemsCache
	,	const IObjectTypesCache& _objectTypesCache
	)
	:	m_environment( _environment )
	,	m_landscapeSerializer( _landscapeSerializer )
	,	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_objectTypesCache( _objectTypesCache )
	,	m_currentLandscape()
	,	m_landscapeLocker( QMutex::Recursive )
	,	m_actionsQueue( new ActionsQueue() )
{
	m_environment.startThread( Resources::ModelThreadName );
	m_actionsProcessingTaskHandle = m_environment.pushPeriodicalTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::runActionsProcessing, this )
		,	ms_actionsProcessPerisod );

} // LandscapeModel::LandscapeModel


/*---------------------------------------------------------------------------*/


LandscapeModel::~LandscapeModel()
{
	m_environment.removeTask( m_actionsProcessingTaskHandle );
	m_environment.stopThread( Resources::ModelThreadName );

} // LandscapeModel::~LandscapeModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initCurrentLandscape ( const QString& _filePath )
{
	boost::intrusive_ptr< IEditableLandscape >
		landscape( new Landscape( m_surfaceItemsCache, m_objectTypesCache ) );

	try
	{
		m_landscapeSerializer.load( *landscape, _filePath );
	}
	catch( ... )
	{
		landscape.reset( new Landscape( m_surfaceItemsCache, m_objectTypesCache ) );
		landscape->setSize( 20, 20 );
	}

	m_currentLandscape = landscape;

} // LandscapeModel::initCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::closeCurrentLandscape()
{
	m_actionsQueue->clear();
	m_currentLandscape.reset();

} // LandscapeModel::closeCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveLandscape( const QString& _filePath ) const
{
	if ( m_currentLandscape )
		m_landscapeSerializer.save( *m_currentLandscape, _filePath );

} // LandscapeModel::saveLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditableLandscape >
LandscapeModel::getCurrentLandscapeInternal() const
{
	return m_currentLandscape;

} // LandscapeModel::getCurrentLandscapeInternal


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeHandle >
LandscapeModel::getCurrentLandscape()
{
	return boost::intrusive_ptr< ILandscapeHandle >( new LandscapeHandle( *this ) );

} // LandscapeModel::getCurrentLandscape


/*---------------------------------------------------------------------------*/


QMutex&
LandscapeModel::getLandscapeLocker()
{
	return m_landscapeLocker;

} // LandscapeModel::getLandscapeLocker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectUnits( const QRect& _rect )
{
	m_actionsQueue->pushAction(
		boost::intrusive_ptr< IAction >( new SelectInRectAction( m_environment, *this, _rect ) ) );

} // LandscapeModel::selectUnits


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectUnit( const IUnit::IdType& _id )
{
	m_actionsQueue->pushAction(
		boost::intrusive_ptr< IAction >( new SelectByIdAction( m_environment, *this, _id ) ) );

} // LandscapeModel::selectUnit


/*---------------------------------------------------------------------------*/


void
LandscapeModel::moveSelectedUnits( const QPoint& _to )
{
	m_actionsQueue->pushAction(
		boost::intrusive_ptr< IAction >( new MoveAction(	m_environment
														,	*this
														,	boost::intrusive_ptr< IPathFinder >( new JumpPointSearch() )
														,	_to ) ) );

} // LandscapeModel::moveSelectedUnits


/*---------------------------------------------------------------------------*/


void
LandscapeModel::createObject(
		const QPoint& _position
	,	const QString& _objectName )
{
	m_actionsQueue->pushAction(
		boost::intrusive_ptr< IAction >( new CreateObjectAction( m_environment, *this, _position, _objectName ) ) );

} // LandscapeModel::createObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setSurfaceItem(
		const QPoint& _position
	,	const Core::LandscapeModel::ISurfaceItem::IdType& _id )
{
	m_actionsQueue->pushAction(
		boost::intrusive_ptr< IAction >( new SetSurfaceItemAction( m_environment, *this, _position, _id ) ) );

} // LandscapeModel::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeModel::runActionsProcessing()
{
	m_actionsQueue->processAction( ms_actionsProcessPerisod );

} // LandscapeModel::runActionsProcessing


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
