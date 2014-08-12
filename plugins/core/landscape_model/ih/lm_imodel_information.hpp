
#ifndef __LM_IMODEL_INFORMATION_HPP__
#define __LM_IMODEL_INFORMATION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_MODEL_INFORMATION = 3;

/*---------------------------------------------------------------------------*/

struct IModelInformation
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual QString getLandscapesDirectory() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IMODEL_INFORMATION_HPP__
