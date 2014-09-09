
-- Dragon

do
	objectName = QString( "Dragon" )
	objectAtlas = QString( "units/dragon" )

	do -- standing north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Standing, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,  80, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 160, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 240, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,  80, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 160, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 240, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Moving, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,  80, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 160, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 240, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 0, 320, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 88, 320, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 176, 320, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 264, 320, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 352, 320, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 264, 320, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 176, 320, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Attacking, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 88, 320, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.North )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.East )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south east animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.West )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north west animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.Dying, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, objectAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Dragon's graphics info has been loaded."))