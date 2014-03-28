
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

struct IModelLocker;

/*---------------------------------------------------------------------------*/

struct ILandscapeModel
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void initModel( const QString& _filePath ) = 0;

	virtual void resetModel() = 0;

	virtual void saveModel( const QString& _filePath ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IModelLocker > lockModel() = 0;

/*---------------------------------------------------------------------------*/

	virtual void selectObjects( const QRect& _rect ) = 0;

	virtual void selectObject( const Object::Id& _id ) = 0;

	virtual void sendSelectedObjects( const QPoint& _to, const bool _flush ) = 0;

	virtual void createObject(
			const QPoint& _location
		,	const QString& _objectName ) = 0;

	virtual void setSurfaceItem(
			const QPoint& _location
		,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) = 0;

	virtual void trainObject( const Object::Id& _parentObject, const QString& _objectName ) = 0;

	virtual void buildObject(
			const Object::Id& _builder
		,	const QString& _objectName
		,	const QPoint& _atLocation
		,	const bool _flush ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void startBuild(
			const Object::Id& _id
		,	const QString& _objectName
		,	const QPoint& _location ) = 0;

	virtual void stopBuild( const Object::Id& _id ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
