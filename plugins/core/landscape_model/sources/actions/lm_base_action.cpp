
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
	,	m_isInProcessing( false )
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
	return m_isInProcessing = prepareToProcessingInternal();

} // BaseAction::prepareToProcessing


/*---------------------------------------------------------------------------*/


bool
BaseAction::cancelProcessing()
{
	if ( isInProcessing() )
		m_isInProcessing = !cancelProcessingInternal();

	return m_isInProcessing;

} // BaseAction::cancelProcessing


/*---------------------------------------------------------------------------*/


bool
BaseAction::isInProcessing() const
{
	return m_isInProcessing;

} // BaseAction::isInProcessing


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
