
-- Human Barracks

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 1000 )
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

elvenArcherResourceData = ResourcesData()
elvenArcherResourceData:pushResource( QString( "Gold" ), 300 )
elvenArcherResourceData:pushResource( QString( "Wood" ), 100 )

footmanResourceData = ResourcesData()
footmanResourceData:pushResource( QString( "Gold" ), 300 )
footmanResourceData:pushResource( QString( "Wood" ), 100 )

trainComponentStaticData = TrainComponentStaticData()
trainComponentStaticData:pushTrainData( QString( "Elven Archer" ), TrainComponentTrainData( 45, elvenArcherResourceData ) )
trainComponentStaticData:pushTrainData( QString( "Footman" ), TrainComponentTrainData( 35, footmanResourceData ) )

object.m_trainData:pushTrainStaticDataMember( TrainComponentStaticDataKey, trainComponentStaticData )

StaticData:regObjectStaticData( QString( "Human Barracks" ), object )

-- Object creator

function HumanBarracksCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 1000 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( TrainComponentName ):pushBoolMember( TrainComponentProgress, TrainComponentProgressData() )

end

StaticData:regObjectCreator( QString( "Human Barracks" ), QString( "HumanBarracksCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Human Barracks's static data has been loaded."))