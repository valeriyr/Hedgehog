
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/object_type/lm_object_type.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ObjectType::ObjectType(
		const QString& _name
	,	const int _maximumHealth
	,	const QSize& _size
	,	const TerrainMapItem::MaskType _passability
	,	const unsigned int _movingSpeed
	,	const IObjectType::ObjectToCreateDataCollection& _objectsToCreate
	)
	:	m_name( _name )
	,	m_maximumHealth( _maximumHealth )
	,	m_size( _size )
	,	m_passability( _passability )
	,	m_movingSpeed( _movingSpeed )
	,	m_objectsToCreate( _objectsToCreate )
{
} // ObjectType::ObjectType


/*---------------------------------------------------------------------------*/


ObjectType::~ObjectType()
{
} // ObjectType::ObjectType


/*---------------------------------------------------------------------------*/


const QString&
ObjectType::getName() const
{
	return m_name;

} // ObjectType::getName


/*---------------------------------------------------------------------------*/


const int
ObjectType::getMaximumHealth() const
{
	return m_maximumHealth;

} // ObjectType::getMaximumHealth


/*---------------------------------------------------------------------------*/


const QSize&
ObjectType::getSize() const
{
	return m_size;

} // ObjectType::getSize


/*---------------------------------------------------------------------------*/


const TerrainMapItem::MaskType
ObjectType::getPassability() const
{
	return m_passability;

} // ObjectType::getPassability


/*---------------------------------------------------------------------------*/


const unsigned int
ObjectType::getMovingSpeed() const
{
	return m_movingSpeed;

} // ObjectType::getMovingSpeed


/*---------------------------------------------------------------------------*/


bool
ObjectType::canCreateObjects() const
{
	return !m_objectsToCreate.empty();

} // ObjectType::canCreateObjects


/*---------------------------------------------------------------------------*/


void
ObjectType::fetchObjectsThatCanCreate( IObjectType::ObjectToCreateDataCollection& _collection ) const
{
	_collection = m_objectsToCreate;

} // ObjectType::fetchObjectsThatCanCreate


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
