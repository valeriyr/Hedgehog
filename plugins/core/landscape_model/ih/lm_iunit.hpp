
#ifndef __LM_IUNIT_HPP__
#define __LM_IUNIT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IUnit
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual const QString& getName() const = 0;

	virtual const QString& getBundlePath() const = 0;

	virtual const QRect& getRectInBundle() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUnit > clone() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
