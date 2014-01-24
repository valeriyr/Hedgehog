
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

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Orc Barracks's graphics info has been loaded."))