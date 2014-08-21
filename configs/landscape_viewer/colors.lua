
-- Colors

GraphicsInfo:regPossiblePlayersColor( QColor( 255, 0, 0 ) );
GraphicsInfo:regPossiblePlayersColor( QColor( 0, 0, 255 ) );
GraphicsInfo:regPossiblePlayersColor( QColor( 255, 255, 0 ) );
GraphicsInfo:regPossiblePlayersColor( QColor( 255, 0, 255 ) );
GraphicsInfo:regPossiblePlayersColor( QColor( 0, 255, 255 ) );

GraphicsInfo:setNobodyObjectColor( QColor( 32, 32, 32 ) );

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Players colors have been loaded."))