
#ifndef __LM_STATIC_DATA_HPP__
#define __LM_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_istatic_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class StaticData
	:	public Tools::Core::BaseWrapper< IStaticData >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	StaticData();

	virtual ~StaticData();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IStaticData::ObjectStaticData getObjectStaticData( const QString& _name ) const;

	/*virtual*/ void fetchObjectsStaticData( IStaticData::StaticDataCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regObjectStaticData( const QString& _name, const ObjectStaticData& _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IStaticData::StaticDataCollection m_staticData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ÛTATIC_DATA_HPP__
