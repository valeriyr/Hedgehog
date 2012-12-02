
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< IEditableLandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape( const unsigned int _width, const unsigned int _height );

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ LandscapeItems::Enum getLadscapeItem(
			const unsigned int _widht
		,	const unsigned int _height ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setLadscapeItem(
			const unsigned int _widht
		,	const unsigned int _height
		,	const LandscapeItems::Enum _Item );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const unsigned int m_width;

	const unsigned int m_height;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
