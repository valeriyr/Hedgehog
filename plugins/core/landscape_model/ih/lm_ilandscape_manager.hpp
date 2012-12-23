
#ifndef __LM_ILANDSCAPE_MANAGER_HPP__
#define __LM_ILANDSCAPE_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_LANDSCAPE_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct ILandscape;

/*---------------------------------------------------------------------------*/

struct ILandscapeManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void initCurrentLandscape ( const QString& _filePath ) = 0;

	virtual void closeCurrentLandscape() = 0;

/*---------------------------------------------------------------------------*/

	virtual ILandscape::Ptr getCurrentLandscape() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
