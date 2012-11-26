
#include "hedgehog/sources/ph/hh_ph.hpp"

#include "hedgehog/sources/main_gui_application/main_gui_application.hpp"

/*---------------------------------------------------------------------------*/


int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdline, int ncmdshow )
{
	Hedgehog::MainGuiApplication app( ncmdshow, (char **)lpcmdline );
	return app.exec();
}


/*---------------------------------------------------------------------------*/
