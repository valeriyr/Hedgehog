
-- Ground tiles with water borders
--
-- 		1 --- 2 --- 3
-- 		|     |     |
-- 		4 --- 5 --- 6
-- 		|     |     |
--		7 --- 8 --- 9

GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 1, QString( "surface" ), QRect( 352, 416, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 2, QString( "surface" ), QRect( 128, 416, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 3, QString( "surface" ), QRect( 128, 448, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 4, QString( "surface" ), QRect( 256, 416, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 5, QString( "surface" ), QRect( 384, 384, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 6, QString( "surface" ), QRect(  32, 448, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 7, QString( "surface" ), QRect( 256, 448, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 8, QString( "surface" ), QRect( 160, 448, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ), 9, QString( "surface" ), QRect( 352, 448, 32, 32 ) );

GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 1, QString( "surface" ), QRect(  64, 544, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 2, QString( "surface" ), QRect( 224, 512, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 3, QString( "surface" ), QRect( 352, 544, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 4, QString( "surface" ), QRect( 416, 512, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 5, QString( "surface" ), QRect(  64, 512, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 6, QString( "surface" ), QRect( 224, 544, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 7, QString( "surface" ), QRect(   0, 576, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 8, QString( "surface" ), QRect( 448, 544, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ), 9, QString( "surface" ), QRect(  64, 576, 32, 32 ) );

GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 1, QString( "surface" ), QRect( 192, 416, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 2, QString( "surface" ), QRect( 416, 384, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 3, QString( "surface" ), QRect( 448, 416, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 4, QString( "surface" ), QRect(  96, 416, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 5, QString( "surface" ), QRect(  32, 352, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 6, QString( "surface" ), QRect( 384, 416, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 7, QString( "surface" ), QRect(  96, 448, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 8, QString( "surface" ), QRect(   0, 448, 32, 32 ) );
GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 9, QString( "surface" ), QRect( 160, 448, 32, 32 ) );

-- Water tiles

GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "summer" ),    101, QString( "surface" ), QRect( 256, 640, 32, 32 ) );

GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "winter" ),    101, QString( "surface" ), QRect( 352, 640, 32, 32 ) );

GraphicsInfoCache:regSurfaceItemGraphicsInfo( QString( "wasteland" ), 101, QString( "surface" ), QRect( 0, 608, 32, 32 ) );

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Surface graphics info has loaded."))