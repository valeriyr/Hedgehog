
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_objects_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor/le_ilandscape_editor_internal.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"

#include "le_objects_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


ObjectsView::ObjectsView( const IEnvironment& _environment, QObject* _parent )
	:	QObject( _parent )
	,	m_environment( _environment )
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

	for ( int i = 0; i < 384; ++i )
	{
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
			surfaceItem = _environment.getSurfaceItem( i );

		QTreeWidgetItem* summerItem = new QTreeWidgetItem();
		summerItem->setText( 0, QString( "%1" ).arg( surfaceItem->getIndex() ) );
		summerItem->setIcon( 0, QIcon( _environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) ) );

		summerSurface->addChild( summerItem );
	}

	for ( int i = 384; i < 768; ++i )
	{
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
			surfaceItem = _environment.getSurfaceItem( i );

		QTreeWidgetItem* winterItem = new QTreeWidgetItem();
		winterItem->setText( 0, QString( "%1" ).arg( surfaceItem->getIndex() ) );
		winterItem->setIcon( 0, QIcon( _environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) ) );

		winterSurface->addChild( winterItem );
	}

	for ( int i = 768; i < 1152; ++i )
	{
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
			surfaceItem = _environment.getSurfaceItem( i );

		QTreeWidgetItem* wastelandItem = new QTreeWidgetItem();
		wastelandItem->setText( 0, QString( "%1" ).arg( surfaceItem->getIndex() ) );
		wastelandItem->setIcon( 0, QIcon( _environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) ) );

		wastelandSurface->addChild( wastelandItem );
	}

	m_objectsView->addTopLevelItem( summerSurface );
	m_objectsView->addTopLevelItem( winterSurface );
	m_objectsView->addTopLevelItem( wastelandSurface );

	QList< QTreeWidgetItem* > items
		= m_objectsView->findItems(
		QString( "%1" ).arg( _environment.getGUILandscapeEditor()->getSelectedSurfaceItem()->getIndex() )
			,	Qt::MatchFixedString | Qt::MatchRecursive );

	m_objectsView->setCurrentItem( items.first() );

	QObject::connect(
			m_objectsView.get()
		,	SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) )
		,	this
		,	SLOT( onCurrentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ) );

} // ObjectsView::ObjectsView


/*---------------------------------------------------------------------------*/


ObjectsView::~ObjectsView()
{
	QObject::disconnect(
			m_objectsView.get()
		,	SIGNAL( currentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) )
		,	this
		,	SLOT( onCurrentItemChanged( QTreeWidgetItem*, QTreeWidgetItem* ) ) );

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
	 m_environment.getGUILandscapeEditor()->setSelectedSurfaceItem(
		 m_environment.getSurfaceItem( _current->text( 0 ).toUInt() ) );

} // ObjectsView::onCurrentItemChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
