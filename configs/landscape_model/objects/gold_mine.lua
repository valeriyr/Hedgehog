
-- Gold Mine

object = ObjectStaticData()

object.m_locateData = Object()
object.m_locateData:pushSizeMember( LocateComponentSize, QSize( 3, 3 ) )
object.m_locateData:pushIntMember( LocateComponentPassability, TerrainMapItem.Ground )
object.m_locateData:pushEmplacementMember( LocateComponentEmplacement, Emplacement.Ground )

object.m_selectionData = Object()

object.m_resourceSourceData = Object()
object.m_resourceSourceData:pushStringMember( ResourceSourceComponentResourceType, QString( "Gold" ) )

StaticData:regObjectStaticData( QString( "Gold Mine" ), object )

-- Object creator

function GoldMineCreator( gameObject )

	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( ResourceSourceComponentName ):pushIntMember( ResourceSourceComponentResourceValue, 10000 )
	gameObject:getObjectPtrMember( ResourceSourceComponentName ):pushIdMember( ResourceSourceComponentObjectInside, WrongIdValue )

end

StaticData:regObjectCreator( QString( "Gold Mine" ), QString( "GoldMineCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Gold Mine's static data has been loaded."))