
#include "hedgehog_srv/sources/ph/hhs_ph.hpp"

#include "hedgehog_srv/sources/main_application/main_application.hpp"

/*---------------------------------------------------------------------------*/

int main( int argc, char* argv[] )
{
	Hedgehog::Server::MainApplication app( argc, argv );
	return app.exec();
}

/*---------------------------------------------------------------------------*/
