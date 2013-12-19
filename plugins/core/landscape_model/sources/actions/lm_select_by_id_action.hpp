
#ifndef __GM_SELECT_BY_ID_ACTION_HPP__
#define __GM_SELECT_BY_ID_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"
#include "landscape_model/ih/lm_iunit.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class SelectByIdAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SelectByIdAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	const IUnit::IdType& _id );

	virtual ~SelectByIdAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ void unprocessAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IUnit::IdType m_id;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_SELECT_BY_ID_ACTION_HPP__
