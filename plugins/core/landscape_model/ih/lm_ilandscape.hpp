
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/h/lm_landscape_items.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct Point
	{
		const unsigned int m_widht;
		const unsigned int m_height;
	};

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual LandscapeItems::Enum getLadscapeItem(
			const unsigned int _widht
		,	const unsigned int _height ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
