
#ifndef __LM_IOBJECT_CREATOR_HPP__
#define __LM_IOBJECT_CREATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IObjectCreator
{

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > create(
			const QPoint& _location
		,	const QString& _objectName ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IOBJECT_CREATOR_HPP__
