
#ifndef __LM_SURFACE_ITEMS_CACHE_HPP__
#define __LM_SURFACE_ITEMS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_isurface_items_cache.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct SurfaceItemsCache
	:	public Tools::Core::BaseWrapper< ISurfaceItemsCache >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SurfaceItemsCache();

	virtual ~SurfaceItemsCache();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem >
		getSurfaceItem( const unsigned int _index ) const;

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem > getDefaultSurfaceItem() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addSurfaceItem(
			const unsigned int _index
		,	const QString& _bundlePath
		,	const QRect& _rectInBundle );

	/*virtual*/ void setDefaultSurfaceItem( boost::intrusive_ptr< ISurfaceItem > _item );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< unsigned int, boost::intrusive_ptr< ISurfaceItem > >
		SurfaceItemsCollection;
	typedef
		SurfaceItemsCollection::const_iterator
		SurfaceItemsCollectionIterator;

/*---------------------------------------------------------------------------*/

	SurfaceItemsCollection m_surfaceItemsCollection;

	boost::intrusive_ptr< ISurfaceItem > m_defaultSurfaceItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SURFACE_ITEMS_CACHE_HPP__
