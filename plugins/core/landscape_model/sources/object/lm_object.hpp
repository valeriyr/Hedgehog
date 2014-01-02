
#ifndef __LM_OBJECT_HPP__
#define __LM_OBJECT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iobject.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Object
	:	public Tools::Core::BaseWrapper< IObject >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Object( boost::intrusive_ptr< IObjectType > _type, const QPoint& _possition );

	virtual ~Object();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IObjectType > getType() const;

	/*virtual*/ const int getHealth() const;

	/*virtual*/ const QPoint& getPosition() const;

	/*virtual*/ const QRect getRect() const;

	/*virtual*/ const IObject::IdType& getUniqueId() const;

	/*virtual*/ const ObjectState::Enum getState() const;

	/*virtual*/ const Direction::Enum getDirection() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setPosition( const QPoint& _position );

	/*virtual*/ void setState( const ObjectState::Enum _state );

	/*virtual*/ void setDirection( const Direction::Enum _direction );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IObjectType > m_type;

	int m_health;

	QPoint m_possition;

	ObjectState::Enum m_state;

	Direction::Enum m_direction;

	const IObject::IdType m_id;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_OBJECT_HPP__
