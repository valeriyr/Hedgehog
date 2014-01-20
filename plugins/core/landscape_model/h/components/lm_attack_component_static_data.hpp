
#ifndef __LM_ATTACK_COMPONENT_STATIC_DATA_HPP__
#define __LM_ATTACK_COMPONENT_STATIC_DATA_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct AttackComponentStaticData
{
	AttackComponentStaticData(
			const int _minDamage
		,	const int _maxDamage
		,	const int _distance
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

	const int m_distance;

	const int m_aiming;

	const int m_reloading;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ATTACK_COMPONENT_STATIC_DATA_HPP__
