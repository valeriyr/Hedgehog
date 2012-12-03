
#ifndef __WM_IVIEW_HPP__
#define __WM_IVIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

struct IView
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::intrusive_ptr< IView >
		Ptr;

/*---------------------------------------------------------------------------*/

	virtual const std::string& getViewTitle() const = 0;

	virtual QWidget* getViewWidget() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void viewWasClosed() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_IVIEW_HPP__
