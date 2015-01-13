
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
	const QString Type = "SettingChanged";

	const QString Key = "SettingKey";
	const QString Value = "SettingValue";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __ST_EVENTS_HPP__
