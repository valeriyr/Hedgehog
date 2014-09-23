
#ifndef __LM_VICTORY_CONDITION_HPP__
#define __LM_VICTORY_CONDITION_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct VictoryCondition
{
	enum Enum
	{
			Undefined = 0

		,	Endless
		,	StayAlone

		,	Size
		,	Begin = Endless
	};

	static QString toString( const Enum _enum )
	{
		switch( _enum )
		{
		case StayAlone:
			return "StayAlone";
		case Endless:
			return "Endless";
		default:
			return "Undefined";
		}
	}

	static Enum fromString( const QString& _type )
	{
		if ( _type == "StayAlone" )
			return StayAlone;
		if ( _type == "Endless" )
			return Endless;
		else
			return Undefined;
	}
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_VICTORY_CONDITION_HPP__
