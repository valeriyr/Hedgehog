
#ifndef __LV_VIEWS_MEDIATOR_HPP__
#define __LV_VIEWS_MEDIATOR_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ISurfaceItem;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class ViewsMediator
	:	public QObject
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ViewsMediator();

	virtual ~ViewsMediator();

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void landscapeWasChanged();

	void visibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

	void landscapeViewWasResized( const float _visibleWidth, const float _visibleHeight );

	void visibilityRectChangedPosition( const float _visibleWidth, const float _visibleHeight );

	void currentSurfaceItemWasChanged(
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > _surfaceItem );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_VIEWS_MEDIATOR_HPP__
