
#ifndef __LM_IPLAYER_HPP__
#define __LM_IPLAYER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/h/lm_resources_data.hpp"

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

/*---------------------------------------------------------------------------*/

	virtual ResourcesData& getResourcesData() = 0;

	virtual void incResource( const QString& _resourceName, const int _incTo ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPLAYER_HPP__
