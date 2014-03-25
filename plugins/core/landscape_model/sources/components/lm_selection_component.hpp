
#ifndef __LM_SELECTION_COMPONENT_HPP__
#define __LM_SELECTION_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_iselection_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class SelectionComponent
	:	public BaseComponent< ISelectionComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SelectionComponent( Object& _object, const ISelectionComponent::StaticData& _staticData );

	virtual ~SelectionComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const ISelectionComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isSelected() const;

	/*virtual*/ void setSelection( const bool _selection );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ISelectionComponent::StaticData& m_staticData;

	bool m_isSelected;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SELECTION_COMPONENT_HPP__
