
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_objects_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


ObjectsView::ObjectsView(
		const ILandscapeEditorController& _landscapeEditorController
	,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
	)
	:	m_landscapeEditorController( _landscapeEditorController )
	,	m_imagesManager( _imagesManager )
	,	m_objectsView( new QTreeWidget() )
	,	m_viewTitle( Resources::Views::ObjectsViewTitle )
{
	m_objectsView->setHeaderLabel( Resources::Views::ObjectsViewColumnName );

	QPixmap waterPixmap( 20, 20 );
	waterPixmap.fill( Qt::blue );

	QIcon waterIcon( waterPixmap );

	QTreeWidgetItem* grassItem = new QTreeWidgetItem();
	grassItem->setText( 0, "Grass" );
	grassItem->setIcon( 0, QIcon( m_imagesManager.getPixmap( "grass2" ) ) );

	QTreeWidgetItem* waterItem = new QTreeWidgetItem();
	waterItem->setText( 0, "Water" );
	waterItem->setIcon( 0, waterIcon );

	QTreeWidgetItem* landscapeTopItem = new QTreeWidgetItem();
	landscapeTopItem->setText( 0, "Landscape" );

	landscapeTopItem->addChild( grassItem );
	landscapeTopItem->addChild( waterItem );

	QTreeWidgetItem* objectsTopItem = new QTreeWidgetItem();
	objectsTopItem->setText( 0, "Objects" );

	QPixmap treePixmap( 20, 20 );
	treePixmap.fill( Qt::green );

	QIcon treeIcon( treePixmap );

	QTreeWidgetItem* treeItem = new QTreeWidgetItem();
	treeItem->setText( 0, "Tree" );
	treeItem->setIcon( 0, treeIcon );

	objectsTopItem->addChild( treeItem );

	m_objectsView->addTopLevelItem( landscapeTopItem );
	m_objectsView->addTopLevelItem( objectsTopItem );

	landscapeTopItem->setExpanded( true );
	objectsTopItem->setExpanded( true );

} // ObjectsView::ObjectsView


/*---------------------------------------------------------------------------*/


ObjectsView::~ObjectsView()
{
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

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
