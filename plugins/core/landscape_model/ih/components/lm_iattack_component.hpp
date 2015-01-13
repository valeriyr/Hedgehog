
#ifndef __LM_IATTACK_COMPONENT_HPP__
#define __LM_IATTACK_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_constants.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class GameObject;

/*---------------------------------------------------------------------------*/

struct IAttackComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		StaticData(
				const int _minDamage
			,	const int _maxDamage
			,	const int _distance
			,	const TickType _aiming
			,	const TickType _reloading
			)
			:	m_minDamage( _minDamage )
			,	m_maxDamage( _maxDamage )
			,	m_distance( _distance )
			,	m_aiming( _aiming )
			,	m_reloading( _reloading )
		{}

		const int m_minDamage;

		const int m_maxDamage;

		const int m_distance;

		const TickType m_aiming;

		const TickType m_reloading;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< GameObject > getTargetObject() const = 0;

	virtual void setTargetObject( boost::shared_ptr< GameObject > _object ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IATTACK_COMPONENT_HPP__
