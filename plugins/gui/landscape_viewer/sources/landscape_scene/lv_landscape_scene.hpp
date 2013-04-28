
#ifndef __LV_LANDSCAPE_SCENE_HPP__
#define __LV_LANDSCAPE_SCENE_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class LandscapeScene
	:	public QGraphicsScene
{

/*---------------------------------------------------------------------------*/

	// Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeScene( const IEnvironment& _environment, QObject* _parent = NULL );

	virtual ~LandscapeScene();

/*---------------------------------------------------------------------------*/

	void showLandscape( const Core::LandscapeModel::ILandscape& _landscape );

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

#endif // __LV_LANDSCAPE_SCENE_HPP__
