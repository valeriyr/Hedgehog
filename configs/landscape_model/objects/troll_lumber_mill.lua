
-- Troll Lumber Mill

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 900 )
object.m_healthData:pushBoolMember( HealthComponentCanBeRepair, true )
--object.m_healthData:pushBoolMethod( HealthComponentIsHealthy, HealthComponentIsHealthyDefault )
--object.m_healthData:pushVoidIntMethod( HealthComponentSetHealth, HealthComponentSetHealthDefault )

object.m_locateData = Object()
object.m_locateData:pushSizeMember( LocateComponentSize, QSize( 3, 3 ) )
object.m_locateData:pushIntMember( LocateComponentPassability, TerrainMapItem.Ground )
object.m_locateData:pushEmplacementMember( LocateComponentEmplacement, Emplacement.Ground )

object.m_selectionData = Object()
object.m_playerData = Object()

object.m_trainData = Object()

trollAxethrowerResourceData = ResourcesData()
trollAxethrowerResourceData:pushResource( QString( "Gold" ), 350 )
trollAxethrowerResourceData:pushResource( QString( "Wood" ), 300 )

trainComponentStaticData = TrainComponentStaticData()
trainComponentStaticData:pushTrainData( QString( "Troll Axethrower" ), TrainComponentTrainData( 40, trollAxethrowerResourceData ) )

object.m_trainData:pushTrainStaticDataMember( TrainComponentStaticDataKey, trainComponentStaticData )

StaticData:regObjectStaticData( QString( "Troll Lumber Mill" ), object )

-- Object creator

function TrollLumberMillCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 900 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( TrainComponentName ):pushBoolMember( TrainComponentProgress, TrainComponentProgressData() )

end

StaticData:regObjectCreator( QString( "Troll Lumber Mill" ), QString( "TrollLumberMillCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Troll Lumber Mill's static data has been loaded."))