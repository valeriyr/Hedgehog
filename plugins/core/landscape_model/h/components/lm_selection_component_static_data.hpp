
#ifndef __LM_SELECTION_COMPONENT_STATIC_DATA_HPP__
#define __LM_SELECTION_COMPONENT_STATIC_DATA_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct SelectionComponentStaticData
{
	SelectionComponentStaticData( const bool _canBeSelected )
		:	m_canBeSelected( _canBeSelected )
	{}

	const bool m_canBeSelected;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SELECTION_COMPONENT_STATIC_DATA_HPP__
