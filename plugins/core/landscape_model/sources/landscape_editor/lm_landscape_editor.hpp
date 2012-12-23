
#ifndef __LM_LANDSCAPE_EDITOR_HPP__
#define __LM_LANDSCAPE_EDITOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_editor.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeSerializer;

/*---------------------------------------------------------------------------*/

class LandscapeEditor
	:	public Tools::Core::BaseWrapper< ILandscapeEditor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeEditor( const ILandscapeSerializer& _landscapeSerializer );

	virtual ~LandscapeEditor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ IEditableLandscape::Ptr
		createLandscape(
				const unsigned int _width
			,	const unsigned int _height ) const;

	/*virtual*/ IEditableLandscape::Ptr
		loadLandscape( const QString& _filePath ) const;

	/*virtual*/ void saveLandscape(
			const QString& _filePath 
		,	ILandscape::Ptr _landscape ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeSerializer& m_landscapeSerializer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_EDITOR_HPP__
