
#ifndef __LM_ILANDSCAPE_MODEL_HPP__
#define __LM_ILANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_object.hpp"

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

	virtual void selectObjects( const QRect& _rect ) = 0;

	virtual void selectObject( const Object::UniqueId& _id ) = 0;

	virtual void sendSelectedObjects( const QPoint& _to, const bool _pushCommand ) = 0;

	virtual void createObject(
			const QPoint& _location
		,	const QString& _objectName ) = 0;

	virtual void setSurfaceItem(
			const QPoint& _location
		,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) = 0;

	virtual void trainObject( const Object::UniqueId& _parentObject, const QString& _objectName ) = 0;

	virtual void buildObject( const Object::UniqueId& _builder, const QString& _objectName, const QPoint& _atLocation ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void startBuild(
			const Object::UniqueId& _id
		,	const QString& _objectName
		,	const QPoint& _location ) = 0;

	virtual void stopBuild( const Object::UniqueId& _id ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
