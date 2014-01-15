
-- Elven Archer

do
	elvenArcherName = QString( "Elven Archer" )
	elvenArcherAtlas = QString( "units/elven_archer" )

	do -- standing up animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Standing, Direction.Up )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 0, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing down animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Standing, Direction.Down )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 288, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing left animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Standing, Direction.Left )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 144, 0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing right animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Standing, Direction.Right )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 144, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving up animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Moving, Direction.Up )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving down animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Moving, Direction.Down )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving left animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Moving, Direction.Left )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,  72, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 144, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 216, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 288, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving right animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Moving, Direction.Right )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack up animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Attacking, Direction.Up )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 0, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 432, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack down animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Attacking, Direction.Down )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 288, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 432, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack left animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Attacking, Direction.Left )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 144, 360, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 432, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack right animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Attacking, Direction.Right )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 300, QRect( 144, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 432, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying up animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Dying, Direction.Up )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying down animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Dying, Direction.Down )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying left animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Dying, Direction.Left )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 504, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 576, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 648, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying right animation

		animationName = generateAnimationName( AnySkinIdentifier, elvenArcherName, ObjectState.Dying, Direction.Right )

		animationInfo = AnimationInfo( animationName, elvenArcherAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 576, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 648, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end
end

-- Grunt

do
	gruntName = QString( "Grunt" )
	gruntAtlas = QString( "units/grunt" )

	do -- standing up animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Standing, Direction.Up )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 0, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing down animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Standing, Direction.Down )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 288, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing left animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Standing, Direction.Left )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 144, 0, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing right animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Standing, Direction.Right )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 144, 0, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving up animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Moving, Direction.Up )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving down animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Moving, Direction.Down )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving left animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Moving, Direction.Left )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,  72, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 144, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 216, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 288, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- moving right animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Moving, Direction.Right )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,  72, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 144, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 216, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 288, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack up animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Attacking, Direction.Up )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 576, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack down animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Attacking, Direction.Down )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 576, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack left animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Attacking, Direction.Left )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 360, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 432, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 504, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 576, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- attack right animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Attacking, Direction.Right )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 360, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 432, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 504, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 576, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying up animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Dying, Direction.Up )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 648, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 720, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 0, 792, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying down animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Dying, Direction.Down )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 648, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 720, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 288, 792, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying left animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Dying, Direction.Left )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 648, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 720, 72, 72 ), true ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 792, 72, 72 ), true ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- dying right animation

		animationName = generateAnimationName( AnySkinIdentifier, gruntName, ObjectState.Dying, Direction.Right )

		animationInfo = AnimationInfo( animationName, gruntAtlas )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 648, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 720, 72, 72 ) ) )
		animationInfo:addFrame( FrameInfo( 100, QRect( 144, 792, 72, 72 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

end

-- Orc Barracks

do
	orcBarracksName = QString( "Orc Barracks" )

	do -- standing down animation

		animationName = generateAnimationName( AnySkinIdentifier, orcBarracksName, ObjectState.Standing, Direction.Down )

		animationInfo = AnimationInfo( animationName, QString( "buildings/orc/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing down animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), orcBarracksName, ObjectState.Standing, Direction.Down )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/orc/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

end

-- Human Barracks

do
	humanBarracksName = QString( "Human Barracks" )

	do -- standing down animation

		animationName = generateAnimationName( AnySkinIdentifier, humanBarracksName, ObjectState.Standing, Direction.Down )

		animationInfo = AnimationInfo( animationName, QString( "buildings/human/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

	do -- standing down animation ( winter skin )

		animationName = generateAnimationName( QString( "winter" ), humanBarracksName, ObjectState.Standing, Direction.Down )

		animationInfo = AnimationInfo( animationName, QString( "skins/winter/human/barracks" ) )
		animationInfo:addFrame( FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) )

		AnimationsCache:regAnimation( animationInfo );

	end

end

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Objects graphics info has been loaded."))