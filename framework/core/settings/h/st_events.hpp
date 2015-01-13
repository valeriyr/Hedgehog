
#ifndef __ST_EVENTS_HPP__
#define __ST_EVENTS_HPP__


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {
namespace Events {

/*---------------------------------------------------------------------------*/

namespace SettingChanged
{
	const QString ms_type = "SettingChanged";

	const QString ms_key = "SettingKey";
	const QString ms_value = "SettingValue";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __ST_EVENTS_HPP__
