
#include "hedgehog_srv/sources/ph/hhs_ph.hpp"

#include "hedgehog_srv/sources/main_application/main_application.hpp"

/*---------------------------------------------------------------------------*/

#ifdef _WINDOWS

/*---------------------------------------------------------------------------*/

#include <windows.h>

int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdline, int ncmdshow )
{
	Hedgehog::Server::MainApplication app( ncmdshow, (char **)lpcmdline );
	return app.exec();
}

/*---------------------------------------------------------------------------*/

#else

/*---------------------------------------------------------------------------*/

int main( int argc, char* argv[] )
{
	Hedgehog::Server::MainApplication app( argc, argv );
	return app.exec();
}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
