
#ifndef __LM_IACTION_HPP__
#define __LM_IACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_actions.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct IAction
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual bool prepareToProcessing() = 0;

	virtual bool cancelProcessing() = 0;

/*---------------------------------------------------------------------------*/

	virtual void processAction() = 0;

	virtual bool isInProcessing() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const Actions::Enum getType() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IACTION_HPP__
