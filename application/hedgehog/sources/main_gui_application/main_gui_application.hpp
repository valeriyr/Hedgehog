
/** Main GUI Application */

#ifndef __HEDGEHOG_MAIN_GUI_APPLICATION_HPP_
#define __HEDGEHOG_MAIN_GUI_APPLICATION_HPP_

/*---------------------------------------------------------------------------*/

namespace Hedgehog {

/*---------------------------------------------------------------------------*/

class MainGuiApplication
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MainGuiApplication( int argc, char* argv[] );

	~MainGuiApplication();

/*---------------------------------------------------------------------------*/

	int exec();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QApplication m_qtApplicaiton;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Hedgehog

/*---------------------------------------------------------------------------*/

#endif // __HEDGEHOG_MAIN_GUI_APPLICATION_HPP_
