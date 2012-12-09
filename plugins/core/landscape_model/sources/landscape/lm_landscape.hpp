
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< IEditableLandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape( const unsigned int _width, const unsigned int _height );

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ ILandscapeObject::Ptr getLadscapeObject( const Point& _point ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void createWaterItem( const Point& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const unsigned int m_width;

	const unsigned int m_height;

	typedef
		std::map< Point, ILandscapeObject::Ptr >
		LandscapeItemsCollection;
	typedef
		LandscapeItemsCollection::iterator
		LandscapeItemsCollectionIterator;
	typedef
		LandscapeItemsCollection::const_iterator
		LandscapeItemsCollectionConstIterator;
	LandscapeItemsCollection m_LandscapeItems;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
