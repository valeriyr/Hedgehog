
#ifndef __LM_IWORKERS_HOLDER_HPP__
#define __LM_IWORKERS_HOLDER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IWorkersHolder
{

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getWorker( const Object::Id& _id ) const = 0;

	virtual void removeWorker( const Object::Id& _id ) = 0;

	virtual void addWorker( boost::shared_ptr< Object > _worker ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IWORKERS_HOLDER_HPP__
