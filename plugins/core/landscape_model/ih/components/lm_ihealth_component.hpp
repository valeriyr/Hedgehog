
#ifndef __LM_IHEALTH_COMPONENT_HPP__
#define __LM_IHEALTH_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IHealthComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		StaticData( const int _maximumHealth, const bool _canBeRepair )
			:	m_maximumHealth( _maximumHealth )
			,	m_canBeRepair( _canBeRepair )
		{}

		const int m_maximumHealth;

		const bool m_canBeRepair;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const int getHealth() const = 0;

	virtual void setHealth( const int _health ) = 0;

	virtual bool isHealthy() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IHEALTH_COMPONENT_HPP__
