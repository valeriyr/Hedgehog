
#ifndef __WM_IDIALOGS_MANAGER_HPP__
#define __WM_IDIALOGS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_DIALOGS_MANAGER = 1;

/*---------------------------------------------------------------------------*/

struct IDialogsManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual QString getExistingDirectory() = 0;

	virtual QString getOpenFileName( const QString& _filter ) = 0;

	virtual QString getSaveFileName( const QString& _filter ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_IDIALOGS_MANAGER_HPP__
