
#ifndef __ST_ISETTINGS_HPP__
#define __ST_ISETTINGS_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_SETTINGS = 0;

/*---------------------------------------------------------------------------*/

struct ISettings
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void regBool( const QString& _key, const bool _defaultValue ) = 0;

/*---------------------------------------------------------------------------*/

	virtual bool getBool( const QString& _key ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void setBool( const QString& _key, const bool _value ) = 0;

/*---------------------------------------------------------------------------*/

	virtual bool hasProperty( const QString& _key ) const = 0;

	virtual void unregProperty( const QString& _key ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __ST_ISETTINGS_HPP__
