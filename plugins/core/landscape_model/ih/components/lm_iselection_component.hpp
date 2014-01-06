
#ifndef __LM_ISELECTION_COMPONENT_HPP__
#define __LM_ISELECTION_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_selection_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISelectionComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	virtual const SelectionComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual bool isSelected() const = 0;

	virtual void setSelection( const bool _selection ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISELECTION_COMPONENT_HPP__
