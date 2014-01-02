
#ifndef __LM_IOBJECT_TYPE_HPP__
#define __LM_IOBJECT_TYPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_terrain_map_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IObjectType
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct ObjectToCreateData
	{
		ObjectToCreateData(
				const unsigned int _creationTime
			,	const QString& _objectName
			)
			:	m_creationTime( _creationTime )
			,	m_objectName( _objectName )
		{}

		unsigned int m_creationTime;

		QString m_objectName;
	};

	typedef
		std::vector< ObjectToCreateData >
		ObjectToCreateDataCollection;
	typedef
		ObjectToCreateDataCollection::const_iterator
		ObjectToCreateDataCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual const QString& getName() const = 0;

	virtual const int getMaximumHealth() const = 0;

	virtual const QSize& getSize() const = 0;

	virtual const TerrainMapItem::MaskType getPassability() const = 0;

	virtual const unsigned int getMovingSpeed() const = 0;

/*---------------------------------------------------------------------------*/

	virtual bool canCreateObjects() const = 0;

	virtual void fetchObjectsThatCanCreate( ObjectToCreateDataCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IOBJECT_TYPE_HPP__
