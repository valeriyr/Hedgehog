
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
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

	/*virtual*/ LandscapeItems::Enum getLadscapeItem( const ILandscape::Point& _point ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setLadscapeItem(
			const ILandscape::Point& _point
		,	const LandscapeItems::Enum _item );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const unsigned int m_width;

	const unsigned int m_height;

	typedef
		std::map< Point, LandscapeItems::Enum >
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
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
