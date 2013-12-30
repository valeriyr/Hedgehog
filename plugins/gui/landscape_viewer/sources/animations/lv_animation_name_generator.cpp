
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

QString
generateAnimationName(
		const QString& _skinId
	,	const QString& _unitName
	,	const Core::LandscapeModel::ObjectState::Enum _state
	,	const Core::LandscapeModel::Direction::Enum _direction )
{
	return
		QString( Resources::Animations::AnimationNameFormat )
			.arg( _skinId )
			.arg( _unitName )
			.arg( _state )
			.arg( _direction );

} // generateAnimationName

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
