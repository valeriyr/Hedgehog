
#ifndef __LM_OBJECT_STATES_HPP__
#define __LM_OBJECT_STATES_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ObjectState
{
	enum Enum : qint32
	{
			Standing		= 0
		,	Moving
		,	Attacking
		,	Training
		,	Building
		,	Repairing
		,	Collecting
		,	Dying
		,	UnderConstruction
		,	UnderCollecting
	};

	static QString toString( const Enum _state )
	{
		switch( _state )
		{
		case Standing:
			return "Standing";
		case Moving:
			return "Moving";
		case Attacking:
			return "Attacking";
		case Training:
			return "Training";
		case Building:
			return "Building";
		case Repairing:
			return "Repairing";
		case Collecting:
			return "Collecting";
		case Dying:
			return "Dying";
		case UnderConstruction:
			return "UnderConstruction";
		case UnderCollecting:
			return "UnderCollecting";
		}

		assert( !"Unsupported state!" );

		return QString();
	}
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_OBJECT_STATES_HPP__
