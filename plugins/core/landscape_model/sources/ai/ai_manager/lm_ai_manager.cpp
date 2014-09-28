
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/ai/ai_manager/lm_ai_manager.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


AIManager::AIManager( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_aiDatas()
{
} // AIManager::AIManager


/*---------------------------------------------------------------------------*/


AIManager::~AIManager()
{
} // AIManager::~AIManager


/*---------------------------------------------------------------------------*/


void
AIManager::regAI(
		const QString& _name
	,	const QString& _race
	,	const QString& _thinkFunction
	,	const QString& _eventsCallbackFunction )
{
	assert( m_aiDatas.find( _name ) == m_aiDatas.end() );

	m_aiDatas.insert( std::make_pair( _name, AIData( _race, _thinkFunction, _eventsCallbackFunction ) ) );

} // AIManager::regAI


/*---------------------------------------------------------------------------*/


QString
AIManager::getAIForRace( const QString& _race ) const
{
	AIDatasCollectionIterator
			begin = m_aiDatas.begin()
		,	end = m_aiDatas.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->second.m_race == _race )
			return begin->first;
	}

	return QString();

} // AIManager::getAIForRace


/*---------------------------------------------------------------------------*/


const IAIManager::AIData&
AIManager::getAIData( const QString& _name ) const
{
	AIDatasCollectionIterator iterator = m_aiDatas.find( _name );

	assert( iterator != m_aiDatas.end() );

	return iterator->second;

} // AIManager::getAIData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
