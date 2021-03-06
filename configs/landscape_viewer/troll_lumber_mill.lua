
-- Troll Lumber Mill

do
	objectName = QString( "Troll Lumber Mill" )

	do -- standing south animation ( summer skin )

		animationName = generateAnimationName( QString( "summer" ), objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/summer/orc/troll_lumber_mill" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( wasteland skin )

		animationName = generateAnimationName( QString( "wasteland" ), objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/wasteland/orc/troll_lumber_mill" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/orc/troll_lumber_mill" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( summer skin )

		animationName = generateAnimationName( QString( "summer" ), objectName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/summer/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( wasteland skin )

		animationName = generateAnimationName( QString( "wasteland" ), objectName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/wasteland/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), objectName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- under construction south animation

		animationName = generateAnimationName( AnySkinIdentifier, objectName, ObjectState.UnderConstruction, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "buildings/land_construction" ) )
		animationInfo:addFrame( FrameInfo( 4000, QRect( 0, 0, 64, 64 ) ) )
		animationInfo:addFrame( FrameInfo( 12000, QRect( 0, 64, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Troll Lumber Mill's graphics info has been loaded."))