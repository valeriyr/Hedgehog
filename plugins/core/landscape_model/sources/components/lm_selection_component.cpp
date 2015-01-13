
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_selection_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SelectionComponent::SelectionComponent( GameObject& _object, const ISelectionComponent::StaticData& _staticData )
	:	BaseComponent< ISelectionComponent >( _object )
	,	m_staticData( _staticData )
	,	m_isSelected( false )
{
} // SelectionComponent::SelectionComponent


/*---------------------------------------------------------------------------*/


SelectionComponent::~SelectionComponent()
{
} // SelectionComponent::~SelectionComponent


/*---------------------------------------------------------------------------*/


const ISelectionComponent::StaticData&
SelectionComponent::getStaticData() const
{
	return m_staticData;

} // SelectionComponent::getStaticData


/*---------------------------------------------------------------------------*/


bool
SelectionComponent::isSelected() const
{
	return m_isSelected;

} // SelectionComponent::isSelected


/*---------------------------------------------------------------------------*/


void
SelectionComponent::setSelection( const bool _selection )
{
	m_isSelected = _selection;

} // SelectionComponent::setSelection


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
