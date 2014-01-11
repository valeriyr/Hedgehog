
#ifndef __LM_IPLAYER_HPP__
#define __LM_IPLAYER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

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

	struct ResourcesData
	{
		typedef
			std::map< QString, int >
			ResourcesDataCollection;
		typedef
			ResourcesDataCollection::const_iterator
			ResourcesDataCollectionIterator;

		ResourcesDataCollection m_data;
	};

/*---------------------------------------------------------------------------*/

	virtual Id getUniqueId() const = 0;

	virtual const ResourcesData& getResourcesData() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPLAYER_HPP__
