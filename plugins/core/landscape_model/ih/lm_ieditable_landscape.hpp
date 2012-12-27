
#ifndef __LM_IEDITABLE_LANDSCAPE_HPP__
#define __LM_IEDITABLE_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEditableLandscape
	:	public ILandscape
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::intrusive_ptr< IEditableLandscape >
		Ptr;

/*---------------------------------------------------------------------------*/

	virtual void setSize(
			const unsigned int _width
		,	const unsigned int _height ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void setSurfaceItem(
			const unsigned int _width
		,	const unsigned int _height
		,	const SurfaceItems::Enum _surfaceItem ) = 0;

	virtual void createTreeObject( const unsigned int _width, const unsigned int _height ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IEDITABLE_LANDSCAPE_HPP__
