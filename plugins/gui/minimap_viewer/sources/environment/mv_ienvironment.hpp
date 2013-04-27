
#ifndef __MV_IENVIRONMENT_HPP__
#define __MV_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscapeEditor;
			struct ISurfaceItem;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getSurfaceItem( const unsigned int _index ) const = 0;

	virtual boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getDefaultSurfaceItem() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap( const QString& _resourcePath, const QRect& _rect ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void changeVisibleAreaOnMainWindow(
			const float _relPosotionByX
		,	const float _relPosotionByY ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __MV_IENVIRONMENT_HPP__
