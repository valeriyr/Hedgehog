
-- Orc Barracks

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 1200 )
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

gruntResourceData = ResourcesData()
gruntResourceData:pushResource( QString( "Gold" ), 400 )
gruntResourceData:pushResource( QString( "Wood" ), 200 )

trainComponentStaticData = TrainComponentStaticData()
trainComponentStaticData:pushTrainData( QString( "Grunt" ), TrainComponentTrainData( 30, gruntResourceData ) )

object.m_trainData:pushTrainStaticDataMember( TrainComponentStaticDataKey, trainComponentStaticData )

StaticData:regObjectStaticData( QString( "Orc Barracks" ), object )

-- Object creator

function OrcBarracksCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 1200 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( TrainComponentName ):pushBoolMember( TrainComponentProgress, TrainComponentProgressData() )

end

StaticData:regObjectCreator( QString( "Orc Barracks" ), QString( "OrcBarracksCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Orc Barracks's static data has been loaded."))