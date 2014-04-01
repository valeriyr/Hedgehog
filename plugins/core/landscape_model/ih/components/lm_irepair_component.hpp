
#ifndef __LM_IREPAIR_COMPONENT_HPP__
#define __LM_IREPAIR_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

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
				const int _healthBySecond
			,	const float _costPercent
			)
			:	m_healthBySecond( _healthBySecond )
			,	m_costPercent( _costPercent )
		{}

		const int m_healthBySecond;

		const float m_costPercent;
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
