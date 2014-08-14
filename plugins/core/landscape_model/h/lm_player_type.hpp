
#ifndef __LM_PLAYER_TYPE_HPP__
#define __LM_PLAYER_TYPE_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct PlayerType
{
	enum Enum
	{
			None		= 0
		,	Player
		,	AI

		,	Size
		,	Begin = None
	};

	static QString toString( const Enum _enum )
	{
		switch( _enum )
		{
		case Player:
			return "Player";
		case AI:
			return "AI";
		default:
			return "None";
		}
	}

	static Enum fromString( const QString& _type )
	{
		if ( _type == "Player" )
			return Player;
		else if ( _type == "AI" )
			return AI;
		else
			return None;
	}
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLAYER_TYPE_HPP__
