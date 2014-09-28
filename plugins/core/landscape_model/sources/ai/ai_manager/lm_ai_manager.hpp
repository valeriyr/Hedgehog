
#ifndef __LM_AI_MANAGER_HPP__
#define __LM_AI_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/ai/ai_manager/lm_iai_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class AIManager
	:	public Tools::Core::BaseWrapper< IAIManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AIManager( const IEnvironment& _environment );

	virtual ~AIManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regAI(
			const QString& _name
		,	const QString& _race
		,	const QString& _thinkFunction
		,	const QString& _eventsCallbackFunction );

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString getAIForRace( const QString& _race ) const;

	/*virtual*/ const IAIManager::AIData& getAIData( const QString& _name ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, IAIManager::AIData >
		AIDatasCollection;
	typedef
		AIDatasCollection::const_iterator
		AIDatasCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	AIDatasCollection m_aiDatas;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_AI_MANAGER_HPP__
