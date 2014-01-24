
-- Human Barracks

do
	humanBarracksName = QString( "Human Barracks" )

	do -- standing south animation

		animationName = generateAnimationName( AnySkinIdentifier, humanBarracksName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "buildings/human/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), humanBarracksName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/human/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Human Barracks's graphics info has been loaded."))