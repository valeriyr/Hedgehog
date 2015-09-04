
#include "hedgehog/sources/ph/hh_ph.hpp"

#include "hedgehog/sources/main_gui_application/main_gui_application.hpp"

/*---------------------------------------------------------------------------*/

#ifdef _WINDOWS

/*---------------------------------------------------------------------------*/

#include <windows.h>

int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdline, int ncmdshow )
{
	Hedgehog::Client::MainGuiApplication app( ncmdshow, (char **)lpcmdline );
	return app.exec();
}

/*---------------------------------------------------------------------------*/

#else

/*---------------------------------------------------------------------------*/

/*	
 - ����, � ��� ���� 2 ����, ����� ��� 2 ����, � ��� 2 ����. ������� �� ����� � ���� � �����?
 - ����.
 - ���, ������ �����������. � ��� ���� 2 ����, ����� ��� 2 ����, � ��� 2 ����. ������� �� ����� � ���� � �����?
 - ����.
 - �����, �������������. � ��� ���� 2 ������, ����� ��� 2 ������, � ��� 2 ������. ������� �� ����� � ���� � �����?
 - �����.
 - �������! ����, � ��� ���� 2 ����, ����� ��� 2 ����, � ��� 2 ����. ������� � �����?
 - ����.
 - �� ������, ���� ������, ����!?
 - �����, � ���� ��� ���� ������ ���.

 (�) https://vk.com/tproger?z=photo-72495085_378607835%2Fwall-30666517_1215348

 - So, I give you 2 cats, than 2 cats more, and 2 cats more. How many cats will you have?
 - Seven.
 - No. Listen carefully. I give you 2 cats, than 2 cats more, and 2 cats more. How many cats will you have?
 - Seven.
 - Ok. Let me rephrase it. I give you 2 apples, than 2 apples more, and 2 apples more. How many apples will you have?
 - Six.
 - Excellent! So, I give you 2 cats, than 2 cats more, and 2 more. How many cats will you have?
 - Seven.
 - OMG! Why fucking seven!?
 - Man, cause I've got a fucking cat already.
*/

int main( int argc, char* argv[] )
{
	Hedgehog::Client::MainGuiApplication app( argc, argv );
	return app.exec();
}

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
