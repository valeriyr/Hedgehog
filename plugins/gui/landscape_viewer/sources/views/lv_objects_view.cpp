
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_objects_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/graphics_info_cache/lv_igraphics_info_cache.hpp"

#include "landscape_model/ih/lm_iobject_type.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

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
		,	Control
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
	,	m_subscriber( _environment.createSubscriber() )
	,	m_objectsView( new QTreeWidget() )
	,	m_viewTitle( Resources::Views::ObjectsViewTitle )
{
	m_objectsView->setHeaderLabel( Resources::Views::ObjectsViewColumnName );
	m_objectsView->setIconSize( QSize( Resources::Landscape::CellSize, Resources::Landscape::CellSize ) );

	fill();

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

	QObject::connect(
			this
		,	SIGNAL( controlItemSelected() )
		,	&m_viewsMediator
		,	SIGNAL( controlItemSelected() ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Framework::Core::Settings::Events::SettingChanged::ms_type
							,	boost::bind( &ObjectsView::onSettingChanged, this, _1 ) );

} // ObjectsView::ObjectsView


/*---------------------------------------------------------------------------*/


ObjectsView::~ObjectsView()
{
	m_subscriber.unsubscribe();

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

	QObject::disconnect(
			this
		,	SIGNAL( controlItemSelected() )
		,	&m_viewsMediator
		,	SIGNAL( controlItemSelected() ) );

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
		case TreeWidgetType::Control:
			emit controlItemSelected();
			break;
		default:
			assert( !"Unsupported tree widget type!" );
			break;
		}
	}

} // ObjectsView::onCurrentItemChanged


/*---------------------------------------------------------------------------*/


void
ObjectsView::onSettingChanged( const Framework::Core::EventManager::Event& _event )
{
	if (	_event.getAttribute( Framework::Core::Settings::Events::SettingChanged::ms_key ).toString()
		==	Resources::Properties::SkinId)
	{
		m_objectsView->clear();
		fill();
	}

} // ObjectsView::onSettingChanged


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
		item->setIcon(
				0
			,	QIcon( m_environment.getPixmap(
						( *begin )->getAtlasName()
					,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( ( *begin )->getFrameRect() ) ) ) );

		_parentNode->addChild( item );
	}

} // ObjectsView::fillWithSurfaceItems


/*---------------------------------------------------------------------------*/


void
ObjectsView::fillWithObjectItems( const QString& _skinId, QTreeWidgetItem* _parentNode )
{
	Core::LandscapeModel::IObjectTypesCache::TypesCollection collection;
	m_environment.fetchTypes( collection );

	Core::LandscapeModel::IObjectTypesCache::TypesCollectionIterator
			begin = collection.begin()
		,	end = collection.end();

	for ( ; begin != end; ++begin )
	{
		TreeWidgetItem* item = new TreeWidgetItem( TreeWidgetType::Object );
		item->setText( 0, ( *begin )->getName() );
		item->setIcon(
				0
			,	QIcon( m_environment.getPixmap( ( *begin )->getName(), _skinId ) ) );

		_parentNode->addChild( item );
	}

} // ObjectsView::fillWithObjectItems


/*---------------------------------------------------------------------------*/


void
ObjectsView::fill()
{
	TreeWidgetItem* controlItem = new TreeWidgetItem( TreeWidgetType::Control );
	controlItem->setText( 0, "Control" );

	QTreeWidgetItem* surfaceItem = new QTreeWidgetItem();
	surfaceItem->setText( 0, "Surface" );

	fillWithSurfaceItems( m_environment.getString( Resources::Properties::SkinId ), surfaceItem );

	QTreeWidgetItem* objectsItem = new QTreeWidgetItem();
	objectsItem->setText( 0, "Objects" );

	fillWithObjectItems( IGraphicsInfoCache::ms_anySkinIdentifier, objectsItem );

	m_objectsView->addTopLevelItem( controlItem );
	m_objectsView->addTopLevelItem( surfaceItem );
	m_objectsView->addTopLevelItem( objectsItem );

	m_objectsView->setCurrentItem( controlItem );

	m_objectsView->expandAll();

} // ObjectsView::fill


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
