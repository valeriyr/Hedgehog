
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
			ResourcesDataCollection::iterator
			ResourcesDataCollectionIterator;
		typedef
			ResourcesDataCollection::const_iterator
			ResourcesDataCollectionConstIterator;

		int getResourceValue( const QString& _resourceName ) const
		{
			ResourcesDataCollectionConstIterator iterator = m_data.find( _resourceName );
			assert( iterator != m_data.end() );

			return iterator->second;
		}

		void incResource( const QString& _resourceName, const int _incTo )
		{
			ResourcesDataCollectionIterator iterator = m_data.find( _resourceName );

			if ( iterator != m_data.end() )
				iterator->second += _incTo;
		}

		ResourcesDataCollection m_data;
	};

/*---------------------------------------------------------------------------*/

	virtual Id getUniqueId() const = 0;

	virtual ResourcesData& getResourcesData() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPLAYER_HPP__
