
#ifndef __LM_PLAYER_TYPE_HPP__
#define __LM_PLAYER_TYPE_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct PlayerType
{
	enum Enum : qint32
	{
			Blocked = 0
		,	Open
		,	Player
		,	AI

		,	Size
		,	Begin = Blocked
	};

	static QString toString( const Enum _enum )
	{
		switch( _enum )
		{
		case Player:
			return "Player";
		case AI:
			return "AI";
		case Open:
			return "Open";
		default:
			return "Blocked";
		}
	}

	static Enum fromString( const QString& _type )
	{
		if ( _type == "Player" )
			return Player;
		else if ( _type == "AI" )
			return AI;
		else if ( _type == "Open" )
			return Open;
		else
			return Blocked;
	}

	static bool isActivated( const Enum _enum )
	{
		return _enum == Player || _enum == AI;
	}

	static bool isFree( const Enum _enum )
	{
		return _enum == Open;
	}
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLAYER_TYPE_HPP__
