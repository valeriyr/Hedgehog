
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_repair_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


RepairComponent::RepairComponent( Object& _object, const IRepairComponent::StaticData& _staticData )
	:	BaseComponent< IRepairComponent >( _object )
	,	m_staticData( _staticData )
	,	m_targetObject()
{
} // RepairComponent::RepairComponent


/*---------------------------------------------------------------------------*/


RepairComponent::~RepairComponent()
{
} // RepairComponent::~RepairComponent


/*---------------------------------------------------------------------------*/


const IRepairComponent::StaticData&
RepairComponent::getStaticData() const
{
	return m_staticData;

} // RepairComponent::getStaticData


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
RepairComponent::getTargetObject() const
{
	return m_targetObject;

} // RepairComponent::getTargetObject


/*---------------------------------------------------------------------------*/


void
RepairComponent::setTargetObject( boost::shared_ptr< Object > _object )
{
	m_targetObject = _object;

} // RepairComponent::setTargetObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
