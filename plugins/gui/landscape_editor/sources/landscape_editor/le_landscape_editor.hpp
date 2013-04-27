
#ifndef __LE_LANDSCAPE_EDITOR_HPP__
#define __LE_LANDSCAPE_EDITOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/landscape_editor/le_ilandscape_editor_internal.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class LandscapeEditor
	:	public Tools::Core::BaseWrapper< ILandscapeEditorInternal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeEditor( const IEnvironment& _environment );

	virtual ~LandscapeEditor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void newLandscape();

	/*virtual*/ void openLandscape();

	/*virtual*/ void closeLandscape();

	/*virtual*/ void saveLandscape();

	/*virtual*/ void saveAsLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem >
		getSelectedSurfaceItem() const;

	/*virtual*/ void setSelectedSurfaceItem(
		boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem > _item );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getLandscapeFilePath() const;

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
		getEditableLandscape() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setVisibilityRectPosition(
			const float _relVisibleWidth
		,	const float _relVisibleHeight );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	QString m_landscapeFilePath;

	boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape > m_editableLandscape;

	boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem > m_selectedSurfaceItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_EDITOR_HPP__
