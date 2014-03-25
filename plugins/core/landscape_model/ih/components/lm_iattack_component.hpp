
#ifndef __LM_IATTACK_COMPONENT_HPP__
#define __LM_IATTACK_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Object;

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
			,	const float _distance
			,	const int _aiming
			,	const int _reloading
			)
			:	m_minDamage( _minDamage )
			,	m_maxDamage( _maxDamage )
			,	m_distance( _distance )
			,	m_aiming( _aiming )
			,	m_reloading( _reloading )
		{}

		const int m_minDamage;

		const int m_maxDamage;

		const float m_distance;

		const int m_aiming;

		const int m_reloading;
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

#endif // __LM_IATTACK_COMPONENT_HPP__
