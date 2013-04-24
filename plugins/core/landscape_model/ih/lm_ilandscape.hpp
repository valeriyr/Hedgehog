
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItem;

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem >
		getSurfaceItem( const unsigned int _width, const unsigned int _height ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
