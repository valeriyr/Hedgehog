
#ifndef __LM_IREPAIR_COMPONENT_HPP__
#define __LM_IREPAIR_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_constants.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Object;

/*---------------------------------------------------------------------------*/

struct IRepairComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		StaticData(
				const TickType _healthByTick
			,	const int _costPercent
			)
			:	m_healthByTick( _healthByTick )
			,	m_costPercent( _costPercent )
		{}

		const TickType m_healthByTick;

		const int m_costPercent; /* 0 - 100 */
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getTargetObject() const = 0;

	virtual void setTargetObject( boost::shared_ptr< Object > _object ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IREPAIR_COMPONENT_HPP__
