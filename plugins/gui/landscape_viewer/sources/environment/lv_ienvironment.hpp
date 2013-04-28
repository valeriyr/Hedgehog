
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

	virtual void initializeLandscapeModel( const QString& _fileName ) = 0;

	virtual boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
		getLandscape() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void showCurrentLandscapeModel() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IENVIRONMENT_HPP__
