
#ifndef __LV_VIEWS_MEDIATOR_HPP__
#define __LV_VIEWS_MEDIATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_game_object.hpp"

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

	void visibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

	void landscapeViewWasResized( const float _visibleWidth, const float _visibleHeight );

	void visibilityRectChangedPosition( const float _visibleWidth, const float _visibleHeight );

	void currentSurfaceItemWasChanged( const Tools::Core::Generators::IGenerator::IdType& _id );

	void currentObjectWasChanged( const QString& _name );

	void controlItemSelected();

	void buildObjectButtonPressed( const Tools::Core::Generators::IGenerator::IdType _builderId, const QString& _objectName );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_VIEWS_MEDIATOR_HPP__
