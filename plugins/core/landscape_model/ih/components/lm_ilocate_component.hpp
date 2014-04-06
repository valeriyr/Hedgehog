
#ifndef __LM_ILOCATE_COMPONENT_HPP__
#define __LM_ILOCATE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_terrain_map_data.hpp"
#include "landscape_model/h/lm_directions.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILocateComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		StaticData(
				const QSize& _size
			,	const TerrainMapItem::MaskType _passability
			,	const Emplacement::Enum _emplacement
			)
			:	m_size( _size )
			,	m_passability( _passability )
			,	m_emplacement( _emplacement )
		{}

		const QSize m_size;
		const TerrainMapItem::MaskType m_passability;
		const Emplacement::Enum m_emplacement;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const Direction::Enum getDirection() const = 0;

	virtual void setDirection( const Direction::Enum _direction ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const QRect getRect() const = 0;

	virtual const QPoint& getLocation() const = 0;

	virtual void setLocation( const QPoint& _location ) = 0;

/*---------------------------------------------------------------------------*/

	virtual bool isHidden() const = 0;

	virtual void setHidden( const bool _hidden ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILOCATE_COMPONENT_HPP__
