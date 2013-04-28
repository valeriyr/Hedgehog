
#ifndef __LV_GAME_INITIALIZER_HPP__
#define __LV_GAME_INITIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/game_initializer/lv_igame_initializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class GameInitializer
	:	public Tools::Core::BaseWrapper< IGameInitializer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GameInitializer( const IEnvironment& _environment );

	virtual ~GameInitializer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void run() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_GAME_INITIALIZER_HPP__
