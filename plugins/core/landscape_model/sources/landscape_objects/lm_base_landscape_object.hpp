
#ifndef __LM_BASE_LANDSCAPE_OBJECT_HPP__
#define __LM_BASE_LANDSCAPE_OBJECT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class BaseLandscapeObject
	:	public Tools::Core::BaseWrapper< ILandscapeObject >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseLandscapeObject( unsigned int _width, unsigned int _height );

	virtual ~BaseLandscapeObject();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	unsigned int m_width;

	unsigned int m_height;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BASE_LANDSCAPE_OBJECT_HPP__
