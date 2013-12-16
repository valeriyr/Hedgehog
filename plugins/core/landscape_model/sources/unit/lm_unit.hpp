
#ifndef __LM_UNIT_HPP__
#define __LM_UNIT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iunit.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Unit
	:	public Tools::Core::BaseWrapper< IUnit >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Unit(	boost::intrusive_ptr< IObjectType > _type
		,	const QRect& _possition );

	virtual ~Unit();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IObjectType > getType() const;

	/*virtual*/ const int getHealth() const;

	/*virtual*/ const QRect& getPosition() const;

	/*virtual*/ const IUnit::IdType& getUniqueId() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IObjectType > m_type;

	int m_health;

	QRect m_possition;

	const IUnit::IdType m_id;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_UNIT_HPP__
