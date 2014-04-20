
#include "settings/sources/ph/st_ph.hpp"

#include "settings/sources/settings/st_settings.hpp"

#include "settings/sources/environment/st_ienvironment.hpp"

#include "settings/h/st_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

/*---------------------------------------------------------------------------*/


Settings::Settings( IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_settings()
{
} // Settings::Settings


/*---------------------------------------------------------------------------*/


Settings::~Settings()
{
} // Settings::~Settings


/*---------------------------------------------------------------------------*/


void
Settings::regBool( const QString& _key, const bool _defaultValue )
{
	regProperty( _key, _defaultValue );

} // Settings::regBool


/*---------------------------------------------------------------------------*/


void
Settings::regString( const QString& _key, const QString& _defaultValue )
{
	regProperty( _key, _defaultValue );

} // Settings::regString


/*---------------------------------------------------------------------------*/


void
Settings::regUInt( const QString& _key, const unsigned int _defaultValue )
{
	regProperty( _key, _defaultValue );

} // Settings::regUInt


/*---------------------------------------------------------------------------*/


bool
Settings::getBool( const QString& _key ) const
{
	assert( hasProperty( _key ) );

	return m_settings.find( _key )->second.toBool();

} // Settings::getBool


/*---------------------------------------------------------------------------*/


QString
Settings::getString( const QString& _key ) const
{
	assert( hasProperty( _key ) );

	return m_settings.find( _key )->second.toString();

} // Settings::getString


/*---------------------------------------------------------------------------*/


unsigned int
Settings::getUInt( const QString& _key ) const
{
	assert( hasProperty( _key ) );

	return m_settings.find( _key )->second.toUInt();

} // Settings::getUInt


/*---------------------------------------------------------------------------*/


void
Settings::setBool( const QString& _key, const bool _value )
{
	setProperty( _key, _value );

} // Settings::setBool


/*---------------------------------------------------------------------------*/


void
Settings::setString( const QString& _key, const QString& _value )
{
	setProperty( _key, _value );

} // Settings::setString


/*---------------------------------------------------------------------------*/


void
Settings::setUInt( const QString& _key, const unsigned int _value )
{
	setProperty( _key, _value );

} // Settings::setUInt


/*---------------------------------------------------------------------------*/


bool
Settings::hasProperty( const QString& _key ) const
{
	return m_settings.find( _key ) != m_settings.end();

} // Settings::hasProperty


/*---------------------------------------------------------------------------*/


void
Settings::unregProperty( const QString& _key )
{
	m_settings.erase( _key );

} // Settings::unregProperty


/*---------------------------------------------------------------------------*/


template< typename _TPropertyType >
void
Settings::regProperty( const QString& _key, const _TPropertyType& _defaultValue )
{
	assert( !hasProperty( _key ) );

	m_settings.insert( std::make_pair( _key, QVariant( _defaultValue ) ) );

} // Settings::regProperty


/*---------------------------------------------------------------------------*/


template< typename _TPropertyType >
void
Settings::setProperty( const QString& _key, const _TPropertyType& _value )
{
	assert( hasProperty( _key ) );

	m_settings.find( _key )->second.setValue( _value );

	m_environment.riseEvent(
		Framework::Core::EventManager::Event( Events::SettingChanged::ms_type )
			.pushAttribute( Events::SettingChanged::ms_key, _key )
			.pushAttribute( Events::SettingChanged::ms_value, _value ) );

} // Settings::setProperty


/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
