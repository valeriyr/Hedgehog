
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_objects_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"

#include "lv_objects_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


ObjectsView::ObjectsView(
		const IEnvironment& _environment
	,	const ViewsMediator& _viewsMediator
	,	QObject* _parent
	)
	:	QObject( _parent )
	,	m_environment( _environment )
	,	m_viewsMediator( _viewsMediator )
	,	m_objectsView( new QTreeWidget() )
	,	m_viewTitle( Resources::Views::ObjectsViewTitle )
{
	m_objectsView->setHeaderLabel( Resources::Views::ObjectsViewColumnName );

	m_objectsView->setIconSize( QSize( Resources::Landscape::CellSize, Resources::Landscape::CellSize ) );

	QTreeWidgetItem* summerSurface = new QTreeWidgetItem();
	summerSurface->setText( 0, "Summer" );

	QTreeWidgetItem* winterSurface = new QTreeWidgetItem();
	winterSurface->setText( 0, "Winter" );

	QTreeWidgetItem* wastelandSurface = new QTreeWidgetItem();
	wastelandSurface->setText( 0, "Wasteland" );

	fillWithSurfaceItems( "summer", summerSurface );
	fillWithSurfaceItems( "winter", winterSurface );
	fillWithSurfaceItems( "wasteland", wastelandSurface );

	m_objectsView->addTopLevelItem( summerSurface );
	m_objectsView->addTopLevelItem( winterSurface );
	m_objectsView->addTopLevelItem( wastelandSurface );

	QList< QTreeWidgetItem* > items
		= m_objectsView->findItems(
				QString( "%1" ).arg( m_environment.getDefaultSurfaceItemId() )
			,	Qt::MatchFixedString | Qt::MatchRecursive );

	m_objectsView->setCurrentItem( items.first() );

	QObject::connect(
			m_objectsView.get()
		,	SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) )
		,	this
		,	SLOT( onCurrentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ) );

	QObject::connect(
			this
		,	SIGNAL( currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) )
		,	&m_viewsMediator
		,	SIGNAL( currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) ) );

} // ObjectsView::ObjectsView


/*---------------------------------------------------------------------------*/


ObjectsView::~ObjectsView()
{
	QObject::disconnect(
			m_objectsView.get()
		,	SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) )
		,	this
		,	SLOT( onCurrentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ) );

	QObject::disconnect(
			this
		,	SIGNAL( currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) )
		,	&m_viewsMediator
		,	SIGNAL( currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) ) );

} // ObjectsView::~ObjectsView


/*---------------------------------------------------------------------------*/


const QString&
ObjectsView::getViewTitle() const
{
	return m_viewTitle;

} // ObjectsView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
ObjectsView::getViewWidget()
{
	return m_objectsView.get();

} // ObjectsView::getViewWidget


/*---------------------------------------------------------------------------*/


void
ObjectsView::viewWasClosed()
{
	m_objectsView.reset();

} // ObjectsView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectsView::landscapeWasOpened()
{
} // ObjectsView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectsView::landscapeWasClosed()
{
} // ObjectsView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectsView::onCurrentItemChanged( QTreeWidgetItem* _current, QTreeWidgetItem* _previous )
{
	emit currentSurfaceItemWasChanged( _current->text( 0 ).toUInt() );

} // ObjectsView::onCurrentItemChanged


/*---------------------------------------------------------------------------*/


void
ObjectsView::fillWithSurfaceItems( const QString& _skinId, QTreeWidgetItem* _parentNode )
{
	IGraphicsInfoCache::SurfaceItemGraphicsInfoCollection collection;
	m_environment.fetchSurfaceItemGraphicsInfos( _skinId, collection );

	IGraphicsInfoCache::SurfaceItemGraphicsInfoCollectionIterator
			begin = collection.begin()
		,	end = collection.end();

	for ( ; begin != end; ++begin )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText( 0, QString( "%1" ).arg( ( *begin )->getId() ) );
		item->setIcon( 0, QIcon( m_environment.getPixmap( ( *begin )->getAtlasName(), ( *begin )->getFrameRect() ) ) );

		_parentNode->addChild( item );
	}

} // ObjectsView::fillWithSurfaceItems


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
