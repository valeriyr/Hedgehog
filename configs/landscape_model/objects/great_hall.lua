
-- Great Hall

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 2500 )
object.m_healthData:pushBoolMember( HealthComponentCanBeRepair, true )
--object.m_healthData:pushBoolMethod( HealthComponentIsHealthy, HealthComponentIsHealthyDefault )
--object.m_healthData:pushVoidIntMethod( HealthComponentSetHealth, HealthComponentSetHealthDefault )

object.m_locateData = Object()
object.m_locateData:pushSizeMember( LocateComponentSize, QSize( 4, 4 ) )
object.m_locateData:pushIntMember( LocateComponentPassability, TerrainMapItem.Ground )
object.m_locateData:pushEmplacementMember( LocateComponentEmplacement, Emplacement.Ground )

object.m_selectionData = Object()
object.m_playerData = Object()

object.m_trainData = Object()

peonResourceData = ResourcesData()
peonResourceData:pushResource( QString( "Gold" ), 50 )

trainComponentStaticData = TrainComponentStaticData()
trainComponentStaticData:pushTrainData( QString( "Peon" ), TrainComponentTrainData( 10, peonResourceData ) )

object.m_trainData:pushTrainStaticDataMember( TrainComponentStaticDataKey, trainComponentStaticData )

object.m_resourceStorageData = Object()

resourceStorageStaticData = PossibleToStoreData()
resourceStorageStaticData:canStore( QString( "Gold" ) )
resourceStorageStaticData:canStore( QString( "Wood" ) )

object.m_resourceStorageData:pushStorageStaticDataMember( ResourceSourceComponentPossibleToStore, resourceStorageStaticData )


StaticData:regObjectStaticData( QString( "Great Hall" ), object )

-- Object creator

function GreatHallCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 2500 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( TrainComponentName ):pushBoolMember( TrainComponentProgress, TrainComponentProgressData() )

end

StaticData:regObjectCreator( QString( "Great Hall" ), QString( "GreatHallCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Great Hall's static data has been loaded."))