
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/sources/actions_queue/lm_actions_queue.hpp"
#include "landscape_model/sources/actions/lm_select_items_action.hpp"

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
	,	m_landscapeLocker()
	,	m_actionsQueue( new ActionsQueue() )
{
	m_environment.startThread( Resources::ModelThreadName );
	m_environment.pushTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::runActionsProcessing, this )
		,	ms_actionsProcessPerisod );

} // LandscapeModel::LandscapeModel


/*---------------------------------------------------------------------------*/


LandscapeModel::~LandscapeModel()
{
	m_environment.stopThread( Resources::ModelThreadName );

} // LandscapeModel::~LandscapeModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initCurrentLandscape ( const QString& _filePath )
{
	boost::intrusive_ptr< IEditableLandscape >
		landscape( new Landscape( m_surfaceItemsCache, m_objectTypesCache ) );

	m_landscapeSerializer.load( *landscape, _filePath );

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
		boost::intrusive_ptr< IAction >( new SelectAction( m_environment, *this, _rect ) ) );

} // LandscapeModel::selectUnits


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
