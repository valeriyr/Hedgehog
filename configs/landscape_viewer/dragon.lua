
-- Dragon

do
	dragonName = QString( "Dragon" )
	dragonAtlas = QString( "units/dragon" )

	do -- standing north animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.North )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing north east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.East )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.West )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing north west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Standing, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.North )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.East )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.South )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,  80, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 160, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 240, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving south west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,  80, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 160, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 240, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.West )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,  80, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 160, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 240, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- moving north west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Moving, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,  80, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 160, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 240, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.North )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 240, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 240, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.East )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 240, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 240, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.South )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 240, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352, 400, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 352,   0, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack south west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 240, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264, 400, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 264,   0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.West )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 240, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176, 400, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 176,   0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- attack north west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Attacking, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 240, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88, 400, 88, 80 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 88,   0, 88, 80 ), true ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.North )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 72, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 72, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 72, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.NorthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 72, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 72, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 72, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.East )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south east animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.SouthEast )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.SouthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.West )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying north west animation

		animationName = generateAnimationName( AnySkinIdentifier, dragonName, ObjectState.Dying, Direction.NorthWest )

		animationInfo = AnimationInfo( animationName, dragonAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 528,   0, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 616, 480, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 704, 560, 88, 80 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 792, 640, 88, 80 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Dragon's graphics info has been loaded."))