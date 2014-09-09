
-- Gold Mine

do
	objectName = QString( "Gold Mine" )

	do -- standing south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/gold_mine" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 96, 96 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( summer skin )

		animationName = generateAnimationName( QString( "summer" ), objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/summer/gold_mine" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 96, 96 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- standing south animation ( wasteland skin )

		animationName = generateAnimationName( QString( "wasteland" ), objectName, ObjectState.Standing, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/wasteland/gold_mine" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 0, 96, 96 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- under collecting south animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), objectName, ObjectState.UnderCollecting, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/gold_mine" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 96, 96, 96 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- under collecting south animation ( summer skin )

		animationName = generateAnimationName( QString( "summer" ), objectName, ObjectState.UnderCollecting, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/summer/gold_mine" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 96, 96, 96 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

	do -- under collecting south animation ( wasteland skin )

		animationName = generateAnimationName( QString( "wasteland" ), objectName, ObjectState.UnderCollecting, Direction.South )

		animationInfo = AnimationInfo( animationName, QString( "skins/wasteland/gold_mine" ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 96, 96, 96 ) ) )

		AnimationsCache:regAnimation( animationInfo )

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Gold Mine's graphics info has been loaded."))