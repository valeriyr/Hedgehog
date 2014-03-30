
-- Great Hall

do
	greatHallName = QString( "Great Hall" )

	do -- standing south animation ( summer skin )

		animationName = generateAnimationName( QString( "summer" ), greatHallName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/summer/orc/great_hall" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 128, 128 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( wasteland skin )

		animationName = generateAnimationName( QString( "wasteland" ), greatHallName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/wasteland/orc/great_hall" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 128, 128 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), greatHallName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/orc/great_hall" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 128, 128 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( summer skin )

		animationName = generateAnimationName( QString( "summer" ), greatHallName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/summer/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( wasteland skin )

		animationName = generateAnimationName( QString( "wasteland" ), greatHallName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/wasteland/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), greatHallName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- under construction south animation

		animationName = generateAnimationName( AnySkinIdentifier, greatHallName, ObjectState.UnderConstruction, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "buildings/land_construction" ) )
		animationInfo:addFrame( FrameInfo( 5000, QRect( 0, 0, 64, 64 ) ) )
		animationInfo:addFrame( FrameInfo( 15000, QRect( 0, 64, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Great Hall's graphics info has been loaded."))