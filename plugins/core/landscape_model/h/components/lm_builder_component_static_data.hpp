
#ifndef __LM_BUILDER_COMPONENT_STATIC_DATA_HPP__
#define __LM_BUILDER_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct BuildObjectsData
{
	BuildObjectsData(
			const qint64 _creationTime
		,	const QString& _objectName
		)
		:	m_creationTime( _creationTime )
		,	m_objectName( _objectName )
	{}

	const qint64 m_creationTime;
	const QString m_objectName;
};


/*---------------------------------------------------------------------------*/


struct BuilderComponentStaticData
{
	typedef
		std::vector< boost::shared_ptr< const BuildObjectsData > >
		BuildObjectsDataCollection;
	typedef
		BuildObjectsDataCollection::const_iterator
		BuildObjectsDataCollectionIterator;

	BuilderComponentStaticData( const BuildObjectsDataCollection& _buildObjects )
		:	m_buildObjects( _buildObjects )
	{}

	const BuildObjectsDataCollection m_buildObjects;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILDER_COMPONENT_STATIC_DATA_HPP__
