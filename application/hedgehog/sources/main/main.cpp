
#include "hedgehog/sources/ph/hh_ph.hpp"

#include "hedgehog/sources/main_gui_application/main_gui_application.hpp"

/*---------------------------------------------------------------------------*/

#ifdef _WINDOWS

/*---------------------------------------------------------------------------*/

#include <windows.h>

int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdline, int ncmdshow )
{
	Hedgehog::MainGuiApplication app( ncmdshow, (char **)lpcmdline );
	return app.exec();
}

/*---------------------------------------------------------------------------*/

#else

/*---------------------------------------------------------------------------*/

int main( int argc, char* argv[] )
{
	Hedgehog::MainGuiApplication app( argc, argv );
	return app.exec();
}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
