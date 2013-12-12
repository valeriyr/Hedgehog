
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


bool
Settings::getBool( const QString& _key ) const
{
	assert( hasProperty( _key ) );

	return m_settings.find( _key )->second.toBool();

} // Settings::getBool


/*---------------------------------------------------------------------------*/


void
Settings::setBool( const QString& _key, const bool _value )
{
	setProperty( _key, _value );

} // Settings::setBool


/*---------------------------------------------------------------------------*/


bool
Settings::hasProperty( const QString& _key ) const
{
	return m_settings.find( _key ) != m_settings.end();

} // Settings::hasProperty


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

	SettingsCollectionIterator iterator = m_settings.find( _key );

	EventManager::Event settingChangedEvent( Events::SettingChanged::ms_type );
	settingChangedEvent.pushAttribute( Events::SettingChanged::ms_value, _value );

	iterator->second.setValue( _value );

	m_environment.riseEvent( settingChangedEvent );

} // Settings::setProperty


/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
