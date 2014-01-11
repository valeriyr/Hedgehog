
#ifndef __LM_HEALTH_COMPONENT_STATIC_DATA_HPP__
#define __LM_HEALTH_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct HealthComponentStaticData
{
	HealthComponentStaticData( const int _maximumHealth )
		:	m_maximumHealth( _maximumHealth )
	{}

	const int m_maximumHealth;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_HEALTH_COMPONENT_STATIC_DATA_HPP__