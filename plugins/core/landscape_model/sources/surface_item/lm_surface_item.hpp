
#ifndef __LM_SURFACE_ITEM_HPP__
#define __LM_SURFACE_ITEM_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class SurfaceItem
	:	public Tools::Core::BaseWrapper< ISurfaceItem >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SurfaceItem(
			const unsigned int _index
		,	const QString& _bundlePath
		,	const QRect& _rectInBundle );

	virtual ~SurfaceItem();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getIndex() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getBundlePath() const;

	/*virtual*/ const QRect& getRectInBundle() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	unsigned int m_index;

	QString m_bundlePath;

	QRect m_rectInBundle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SURFACE_ITEM_HPP__
