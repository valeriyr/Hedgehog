
#ifndef __LM_MOVE_COMPONENT_STATIC_DATA_HPP__
#define __LM_MOVE_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct MoveComponentStaticData
{
	MoveComponentStaticData( const unsigned int _movingSpeed )
		:	m_movingSpeed( _movingSpeed )
	{}

	const unsigned int m_movingSpeed;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MOVE_COMPONENT_STATIC_DATA_HPP__
