
#ifndef __LM_IOBJECT_CREATOR_HPP__
#define __LM_IOBJECT_CREATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_game_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IObjectCreator
{

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< GameObject > create(
				const QString& _objectName
			,	const QPoint& _location
			,	const Tools::Core::Generators::IGenerator::IdType& _playerId ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IOBJECT_CREATOR_HPP__
