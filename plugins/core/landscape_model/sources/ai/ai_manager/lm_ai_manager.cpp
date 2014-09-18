
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/ai/ai_manager/lm_ai_manager.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


AiManager::AiManager( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_aiDatas()
{
} // AiManager::AiManager


/*---------------------------------------------------------------------------*/


AiManager::~AiManager()
{
} // AiManager::~AiManager


/*---------------------------------------------------------------------------*/


void
AiManager::regAi( const QString& _name, const QString& _race )
{
	assert( m_aiDatas.find( _name ) == m_aiDatas.end() );

	m_aiDatas.insert( std::make_pair( _name, AiData( _race ) ) );

	m_environment.executeLuaFunction( _name );
	m_environment.executeLuaFunction( _name );
	m_environment.executeLuaFunction( _name );
	m_environment.executeLuaFunction( _name );
	m_environment.executeLuaFunction( _name );
	m_environment.executeLuaFunction( _name );
	m_environment.executeLuaFunction( _name );

} // AiManager::regAi


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
