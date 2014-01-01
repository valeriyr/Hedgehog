
#ifndef __LM_UNIT_HPP__
#define __LM_UNIT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iobject_type.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class ObjectType
	:	public Tools::Core::BaseWrapper< IObjectType >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ObjectType(	const QString& _name
			,	const int _maximumHealth
			,	const QSize& _size
			,	const TerrainMapItem::MaskType _passability
			,	const unsigned int _movingSpeed );

	virtual ~ObjectType();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getName() const;

	/*virtual*/ const int getMaximumHealth() const;

	/*virtual*/ const QSize& getSize() const;

	/*virtual*/ const TerrainMapItem::MaskType getPassability() const;

	/*virtual*/ const unsigned int getMovingSpeed() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QString m_name;

	const int m_maximumHealth;

	const QSize m_size;

	const TerrainMapItem::MaskType m_passability;

	const unsigned int m_movingSpeed;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_UNIT_HPP__
