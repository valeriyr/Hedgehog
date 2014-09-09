
-- Elven Archer

do
	objectName = QString( "Elven Archer" )
	objectAtlas = QString( "units/elven_archer" )

	do -- standing north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,  72, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 144, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 216, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 288, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,  72, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 144, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 216, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 288, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,  72, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 144, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 216, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 288, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 0, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 72, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 144, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 216, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 288, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 216, 360, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 432, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 144, 360, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 432, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 72, 360, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 432, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 504, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 576, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 216, 648, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 504, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 576, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 648, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 504, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 576, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 72, 648, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Elven Archer's graphics info has been loaded."))