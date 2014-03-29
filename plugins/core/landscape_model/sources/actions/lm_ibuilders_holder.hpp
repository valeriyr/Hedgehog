
#ifndef __LM_IBUILDERS_HOLDER_HPP__
#define __LM_IBUILDERS_HOLDER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IBuildersHolder
{

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getBuilder( const Object::Id& _id ) const = 0;

	virtual void removeBuilder( const Object::Id& _id ) = 0;

	virtual void addBuilder( boost::shared_ptr< Object > _builder ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IBUILDERS_HOLDER_HPP__
