
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_base_action.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BaseAction::BaseAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	)
	:	m_environment( _environment )
	,	m_landscapeModel( _landscapeModel )
	,	m_object( _object )
	,	m_isInitialized( false )
{
} // BaseAction::BaseAction


/*---------------------------------------------------------------------------*/


BaseAction::~BaseAction()
{
} // BaseAction::~BaseAction


/*---------------------------------------------------------------------------*/


bool
BaseAction::prepareToProcessing()
{
	return m_isInitialized = prepareToProcessingInternal();

} // BaseAction::prepareToProcessing


/*---------------------------------------------------------------------------*/


bool
BaseAction::cancelProcessing()
{
	if ( isInitialized() )
		m_isInitialized = !cancelProcessingInternal();

	return !m_isInitialized;

} // BaseAction::cancelProcessing


/*---------------------------------------------------------------------------*/


bool
BaseAction::isInitialized() const
{
	return m_isInitialized;

} // BaseAction::isInitialized


/*---------------------------------------------------------------------------*/


bool
BaseAction::prepareToProcessingInternal()
{
	return true;

} // BaseAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
BaseAction::cancelProcessingInternal()
{
	return true;

} // BaseAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
