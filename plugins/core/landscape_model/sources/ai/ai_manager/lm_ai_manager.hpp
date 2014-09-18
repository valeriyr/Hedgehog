
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

class AiManager
	:	public Tools::Core::BaseWrapper< IAiManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AiManager( const IEnvironment& _environment );

	virtual ~AiManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regAi( const QString& _name, const QString& _race );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct AiData
	{
		AiData( const QString& _race )
			:	m_race( _race )
		{}

		const QString m_race;
	};

	typedef
		std::map< QString, AiData >
		AiDatasCollection;
	typedef
		AiDatasCollection::const_iterator
		AiDatasCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	AiDatasCollection m_aiDatas;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_AI_MANAGER_HPP__
