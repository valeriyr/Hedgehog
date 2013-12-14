
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_objects_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/object_graphics_info/lv_iobject_graphics_info.hpp"
#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "lv_objects_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct TreeWidgetType
{
	enum Enum
	{
			Surface = 0
		,	Object
	};
};

class TreeWidgetItem
	:	public QTreeWidgetItem
{

public:

	TreeWidgetItem( const TreeWidgetType::Enum _type )
		:	QTreeWidgetItem()
		,	m_type( _type )
	{}

	const TreeWidgetType::Enum getTreeWidgetType() { return m_type; }

private:

	const TreeWidgetType::Enum m_type;
};


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
	summerSurface->setText( 0, "Summer surface" );

	QTreeWidgetItem* winterSurface = new QTreeWidgetItem();
	winterSurface->setText( 0, "Winter surface" );

	QTreeWidgetItem* wastelandSurface = new QTreeWidgetItem();
	wastelandSurface->setText( 0, "Wasteland surface" );

	QTreeWidgetItem* anySurface = new QTreeWidgetItem();
	anySurface->setText( 0, "Any surface" );

	fillWithSurfaceItems( "summer", summerSurface );
	fillWithSurfaceItems( "winter", winterSurface );
	fillWithSurfaceItems( "wasteland", wastelandSurface );
	fillWithSurfaceItems( GraphicsInfoCache::ms_anySkinIdentifier, anySurface );

	QTreeWidgetItem* summerObjects = new QTreeWidgetItem();
	summerObjects->setText( 0, "Summer objects" );

	QTreeWidgetItem* winterObjects = new QTreeWidgetItem();
	winterObjects->setText( 0, "Winter objects" );

	QTreeWidgetItem* wastelandObjects = new QTreeWidgetItem();
	wastelandObjects->setText( 0, "Wasteland objects" );

	QTreeWidgetItem* anyObjects = new QTreeWidgetItem();
	anyObjects->setText( 0, "Any objects" );

	fillWithObjectItems( "summer", summerObjects );
	fillWithObjectItems( "winter", winterObjects );
	fillWithObjectItems( "wasteland", wastelandObjects );
	fillWithObjectItems( GraphicsInfoCache::ms_anySkinIdentifier, anyObjects );

	m_objectsView->addTopLevelItem( summerSurface );
	m_objectsView->addTopLevelItem( winterSurface );
	m_objectsView->addTopLevelItem( wastelandSurface );
	m_objectsView->addTopLevelItem( anySurface );

	m_objectsView->addTopLevelItem( summerObjects );
	m_objectsView->addTopLevelItem( winterObjects );
	m_objectsView->addTopLevelItem( wastelandObjects );
	m_objectsView->addTopLevelItem( anyObjects );

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

	QObject::connect(
			this
		,	SIGNAL( currentObjectWasChanged( const QString& ) )
		,	&m_viewsMediator
		,	SIGNAL( currentObjectWasChanged( const QString& ) ) );

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

	QObject::disconnect(
			this
		,	SIGNAL( currentObjectWasChanged( const QString& ) )
		,	&m_viewsMediator
		,	SIGNAL( currentObjectWasChanged( const QString& ) ) );

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
	TreeWidgetItem* item = dynamic_cast< TreeWidgetItem* >( _current );
	if ( item )
	{
		switch( item->getTreeWidgetType() )
		{
		case TreeWidgetType::Surface:
			emit currentSurfaceItemWasChanged( _current->text( 0 ).toUInt() );
			break;
		case TreeWidgetType::Object:
			emit currentObjectWasChanged( _current->text( 0 ) );
			break;
		default:
			assert( !"Unsupported tree widget type!" );
			break;
		}
	}

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
		TreeWidgetItem* item = new TreeWidgetItem( TreeWidgetType::Surface );
		item->setText( 0, QString( "%1" ).arg( ( *begin )->getId() ) );
		item->setIcon( 0, QIcon( m_environment.getPixmap( ( *begin )->getAtlasName(), ( *begin )->getFrameRect() ) ) );

		_parentNode->addChild( item );
	}

} // ObjectsView::fillWithSurfaceItems


/*---------------------------------------------------------------------------*/


void
ObjectsView::fillWithObjectItems( const QString& _skinId, QTreeWidgetItem* _parentNode )
{
	IGraphicsInfoCache::ObjectGraphicsInfoCollection collection;
	m_environment.fetchObjectsGraphicsInfos( _skinId, collection );

	IGraphicsInfoCache::ObjectGraphicsInfoCollectionIterator
			begin = collection.begin()
		,	end = collection.end();

	for ( ; begin != end; ++begin )
	{
		TreeWidgetItem* item = new TreeWidgetItem( TreeWidgetType::Object );
		item->setText( 0, ( *begin )->getName() );
		item->setIcon( 0, QIcon( m_environment.getPixmap( ( *begin )->getAtlasName(), ( *begin )->getFrameRect() ) ) );

		_parentNode->addChild( item );
	}

} // ObjectsView::fillWithObjectItems


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
