
#ifndef __LM_ILANDSCAPE_EDITOR_HPP__
#define __LM_ILANDSCAPE_EDITOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_LANDSCAPE_EDITOR = 1;

/*---------------------------------------------------------------------------*/

struct ILandscape;
struct IEditableLandscape;

/*---------------------------------------------------------------------------*/

struct ILandscapeEditor
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IEditableLandscape >
		createLandscape(
			const unsigned int _width
		,	const unsigned int _height ) const = 0;

	virtual boost::intrusive_ptr< IEditableLandscape > loadLandscape( const QString& _filePath ) const = 0;

	virtual void saveLandscape(
			const ILandscape& _landscape
		,	const QString& _filePath ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_EDITOR_HPP__
