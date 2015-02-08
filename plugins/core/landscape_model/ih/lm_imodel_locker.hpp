
#ifndef __LM_IMODEL_LOCKER_HPP__
#define __LM_IMODEL_LOCKER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_model.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const quint32 IID_LANDSCAPE_MODEL = 0;

/*---------------------------------------------------------------------------*/

struct IModelLocker
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ILandscapeModel > getLandscapeModel() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IMODEL_LOCKER_HPP__
