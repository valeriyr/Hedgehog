
#ifndef __LM_LANDSCAPE_EDITOR_HPP__
#define __LM_LANDSCAPE_EDITOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_editor.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache;
struct IObjectTypesCache;
struct ILandscapeSerializer;

/*---------------------------------------------------------------------------*/

class LandscapeEditor
	:	public Tools::Core::BaseWrapper< ILandscapeEditor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeEditor(
			const ILandscapeSerializer& _landscapeSerializer
		,	const ISurfaceItemsCache& _surfaceItemsCache
		,	const IObjectTypesCache& _objectTypesCache );

	virtual ~LandscapeEditor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IEditableLandscape >
		createLandscape(
				const unsigned int _width
			,	const unsigned int _height ) const;

	/*virtual*/ boost::intrusive_ptr< IEditableLandscape >
		loadLandscape( const QString& _filePath ) const;

	/*virtual*/ void saveLandscape(
			const ILandscape& _landscape
		,	const QString& _filePath ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeSerializer& m_landscapeSerializer;

	const ISurfaceItemsCache& m_surfaceItemsCache;

	const IObjectTypesCache& m_objectTypesCache;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_EDITOR_HPP__
