
-- Orc Barracks

do
	orcBarracksName = QString( "Orc Barracks" )

	do -- standing south animation

		animationName = generateAnimationName( AnySkinIdentifier, orcBarracksName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "buildings/orc/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), orcBarracksName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/orc/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( summer skin )

		animationName = generateAnimationName( QString( "summer" ), orcBarracksName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/summer/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( wasteland skin )

		animationName = generateAnimationName( QString( "wasteland" ), orcBarracksName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/wasteland/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- dying south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), orcBarracksName, ObjectState.Dying, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/destroyed" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- under construction south animation

		animationName = generateAnimationName( AnySkinIdentifier, orcBarracksName, ObjectState.UnderConstruction, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "buildings/land_construction" ) )
		animationInfo:addFrame( FrameInfo( 5000, QRect( 0, 0, 64, 64 ) ) )
		animationInfo:addFrame( FrameInfo( 16000, QRect( 0, 64, 64, 64 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Orc Barracks's graphics info has been loaded."))