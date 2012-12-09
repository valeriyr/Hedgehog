
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_ilandscape_object.hpp"
#include "landscape_model/h/lm_point.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::intrusive_ptr< ILandscape >
		Ptr;

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual ILandscapeObject::Ptr getLadscapeObject( const Point& _point ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
