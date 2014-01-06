
#ifndef __LM_LOCATE_COMPONENT_STATIC_DATA_HPP__
#define __LM_LOCATE_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_terrain_map_data.hpp"
#include "landscape_model/h/lm_directions.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct LocateComponentStaticData
{
	LocateComponentStaticData(
			const QSize& _size
		,	const TerrainMapItem::MaskType _passability
		)
		:	m_size( _size )
		,	m_passability( _passability )
	{}

	const QSize m_size;
	const TerrainMapItem::MaskType m_passability;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LOCATE_COMPONENT_STATIC_DATA_HPP__
