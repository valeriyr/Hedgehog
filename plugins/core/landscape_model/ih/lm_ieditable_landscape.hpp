
#ifndef __LM_IEDITABLE_LANDSCAPE_HPP__
#define __LM_IEDITABLE_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEditableLandscape
	:	public ILandscape
{

/*---------------------------------------------------------------------------*/

	virtual void setLadscapeItem(
			const unsigned int _widht
		,	const unsigned int _height
		,	const LandscapeItems::Enum _Item ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LM_IEDITABLE_LANDSCAPE_HPP__