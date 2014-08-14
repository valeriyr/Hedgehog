
#ifndef __LM_IPLAYER_HPP__
#define __LM_IPLAYER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_resources_data.hpp"
#include "landscape_model/h/lm_start_point.hpp"
#include "landscape_model/h/lm_player_type.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IPlayer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef int Id;
	static const int ms_wrondId = -1;

/*---------------------------------------------------------------------------*/

	virtual Id getUniqueId() const = 0;

	virtual PlayerType::Enum getType() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QString& getRace() const = 0;

	virtual const StartPoint::Id& getStartPointId() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const ResourcesData& getResourcesData() const = 0;

	virtual void substructResources( const ResourcesData& _data ) = 0;

	virtual void addResources( const ResourcesData& _data ) = 0;

	virtual void addResources( const QString& _resourceName, const int _value ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPLAYER_HPP__
