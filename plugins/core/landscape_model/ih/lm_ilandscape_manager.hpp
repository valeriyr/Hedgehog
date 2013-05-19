
#ifndef __LM_ILANDSCAPE_MANAGER_HPP__
#define __LM_ILANDSCAPE_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_LANDSCAPE_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IEditableLandscape;

/*---------------------------------------------------------------------------*/

struct ILandscapeManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void initCurrentLandscape ( const QString& _filePath ) = 0;

	virtual void closeCurrentLandscape() = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IEditableLandscape > getCurrentLandscape() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
