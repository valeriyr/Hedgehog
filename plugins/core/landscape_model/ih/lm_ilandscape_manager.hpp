
#ifndef __LM_ILANDSCAPE_MANAGER_HPP__
#define __LM_ILANDSCAPE_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_LANDSCAPE_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct ILandscape;

/*---------------------------------------------------------------------------*/

struct ILandscapeEditor
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ILandscape > getCurrentLandscape() const = 0;

	virtual void initCurrentLandscape ( const std::string& _filePath ) const = 0

	virtual void closeCurrentLandscape() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
