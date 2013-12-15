
#ifndef __LM_ILANDSCAPE_MODEL_HPP__
#define __LM_ILANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_LANDSCAPE_MODEL = 0;

/*---------------------------------------------------------------------------*/

struct ILandscapeHandle;

/*---------------------------------------------------------------------------*/

struct ILandscapeModel
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void initCurrentLandscape ( const QString& _filePath ) = 0;

	virtual void closeCurrentLandscape() = 0;

	virtual void saveLandscape( const QString& _filePath ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ILandscapeHandle > getCurrentLandscape() = 0;

/*---------------------------------------------------------------------------*/

	virtual void selectUnits( const QRect& _rect ) = 0;

	virtual void createObject(
			const QRect& _rect
		,	const QString& _objectName ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
