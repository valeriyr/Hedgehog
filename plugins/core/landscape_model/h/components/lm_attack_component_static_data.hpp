
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
			const unsigned int _minDamage
		,	const unsigned int _maxDamage
		,	const unsigned int _distance
		)
		:	m_minDamage( _minDamage )
		,	m_maxDamage( _maxDamage )
		,	m_distance( _distance )
	{}

	const unsigned int m_minDamage;

	const unsigned int m_maxDamage;

	const unsigned int m_distance;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ATTACK_COMPONENT_STATIC_DATA_HPP__
