
#ifndef __LV_IENVIRONMENT_HPP__
#define __LV_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

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

struct IGameInitializer;

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IGameInitializer > getGameInitializer() const = 0;

/*---------------------------------------------------------------------------*/

	virtual QString showOpenFileDialog() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap( const QString& _resourcePath, const QRect& _rect ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void initializeLandscape( const QString& _fileName ) = 0;

	virtual void closeLandscape() = 0;

	virtual boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
		getLandscape() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void showCurrentLandscape() = 0;

	virtual void clearLandscapeView() = 0;

/*---------------------------------------------------------------------------*/

	virtual void runGameManager() const = 0;

	virtual void stopGameManager() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IENVIRONMENT_HPP__
