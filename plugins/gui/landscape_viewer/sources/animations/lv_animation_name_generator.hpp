
#ifndef __LV_ANIMATION_NAME_GENERATOR_HPP__
#define __LV_ANIMATION_NAME_GENERATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_directions.hpp"
#include "landscape_model/h/lm_object_states.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

	QString generateAnimationName(
			const QString& _skinId
		,	const QString& _unitName
		,	const Core::LandscapeModel::ObjectState::Enum _state
		,	const Core::LandscapeModel::Direction::Enum _direction );

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ANIMATION_NAME_GENERATOR_HPP__

