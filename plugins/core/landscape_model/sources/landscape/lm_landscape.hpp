
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< IEditableLandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape();

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ ILandscapeObject::Ptr getLadscapeObject( const Point& _point ) const;

	/*virtual*/ SurfaceItems::Enum getSurfaceItem( const Point& _point ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSize(
			const unsigned int _width
		,	const unsigned int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSurfaceItem(
			const Point& _point
		,	const SurfaceItems::Enum _surfaceItem );

	/*virtual*/ void createTreeObject( const Point& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	unsigned int m_width;

	unsigned int m_height;

/*---------------------------------------------------------------------------*/

	SurfaceItems::Enum ** m_surfaceData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
