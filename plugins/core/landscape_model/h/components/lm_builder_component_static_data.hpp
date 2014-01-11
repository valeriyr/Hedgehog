
#ifndef __LM_BUILDER_COMPONENT_STATIC_DATA_HPP__
#define __LM_BUILDER_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct BuildObjectData
{
	BuildObjectData(
			const int _creationTime
		,	const QString& _objectName
		)
		:	m_creationTime( _creationTime )
		,	m_objectName( _objectName )
	{}

	const int m_creationTime;
	const QString m_objectName;
};


/*---------------------------------------------------------------------------*/


struct BuilderComponentStaticData
{
	typedef
		std::vector< boost::shared_ptr< const BuildObjectData > >
		BuildObjectsDataCollection;
	typedef
		BuildObjectsDataCollection::const_iterator
		BuildObjectsDataCollectionIterator;

	BuilderComponentStaticData()
		:	m_buildObjects()
	{}

	void pushBuildObjectData( boost::shared_ptr< BuildObjectData > _data )
	{
		m_buildObjects.push_back( _data );
	}

	BuildObjectsDataCollection m_buildObjects;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILDER_COMPONENT_STATIC_DATA_HPP__
