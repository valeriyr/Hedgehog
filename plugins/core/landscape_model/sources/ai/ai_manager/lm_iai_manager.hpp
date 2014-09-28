
#ifndef __LM_IAI_MANAGER_HPP__
#define __LM_IAI_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IAIManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct AIData
	{
		AIData(
				const QString& _race
			,	const QString& _thinkFunction
			,	const QString& _eventsCallbackFunction
			)
			:	m_race( _race )
			,	m_thinkFunction( _thinkFunction )
			,	m_eventsCallbackFunction( _eventsCallbackFunction )
		{}

		const QString m_race;
		const QString m_thinkFunction;
		const QString m_eventsCallbackFunction;
	};

/*---------------------------------------------------------------------------*/

	virtual void regAI(
			const QString& _name
		,	const QString& _race
		,	const QString& _thinkFunction
		,	const QString& _eventsCallbackFunction ) = 0;

/*---------------------------------------------------------------------------*/

	virtual QString getAIForRace( const QString& _race ) const = 0;

	virtual const AIData& getAIData( const QString& _name ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IAI_MANAGER_HPP__
