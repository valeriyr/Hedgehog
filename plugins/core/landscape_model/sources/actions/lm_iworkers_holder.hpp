
#ifndef __LM_IWORKERS_HOLDER_HPP__
#define __LM_IWORKERS_HOLDER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_game_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IWorkersHolder
{

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< GameObject > getWorker( const Tools::Core::Generators::IGenerator::IdType& _id ) const = 0;

	virtual void removeWorker( const Tools::Core::Generators::IGenerator::IdType& _id ) = 0;

	virtual void addWorker( boost::shared_ptr< GameObject > _worker ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IWORKERS_HOLDER_HPP__
