
#ifndef __ST_SETTINGS_HPP__
#define __ST_SETTINGS_HPP__

/*---------------------------------------------------------------------------*/

#include "settings/ih/st_isettings.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class Settings
	:	public Tools::Core::BaseWrapper< ISettings >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Settings( IEnvironment& _environment );

	virtual ~Settings();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regBool( const QString& _key, const bool _defaultValue );

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool getBool( const QString& _key ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setBool( const QString& _key, const bool _value );

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool hasProperty( const QString& _key ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	template< typename _TPropertyType >
	void regProperty( const QString& _key, const _TPropertyType& _defaultValue );

	template< typename _TPropertyType >
	void setProperty( const QString& _key, const _TPropertyType& _value );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, QVariant >
		SettingsCollection;
	typedef
		SettingsCollection::iterator
		SettingsCollectionIterator;

/*---------------------------------------------------------------------------*/

	IEnvironment& m_environment;

	SettingsCollection m_settings;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __ST_SETTINGS_HPP__
