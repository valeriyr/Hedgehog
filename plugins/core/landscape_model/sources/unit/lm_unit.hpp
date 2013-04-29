
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
	:	public Tools::Core::BaseWrapper< IUnit>
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Unit(	const QString& _name
		,	const QString& _bundlePath
		,	const QRect& _rectInBundle );

	Unit( const Unit& _unit );

	virtual ~Unit();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getName() const;

	/*virtual*/ const QString& getBundlePath() const;

	/*virtual*/ const QRect& getRectInBundle() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IUnit > clone() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QString m_name;

	QString m_bundlePath;

	QRect m_rectInBundle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_UNIT_HPP__
