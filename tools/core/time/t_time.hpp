
#ifndef __T_TIME_HPP__
#define __T_TIME_HPP__


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace Time {

/*---------------------------------------------------------------------------*/

typedef qint64 Milliseconds;

/*---------------------------------------------------------------------------*/

inline Milliseconds currentTime()
{
	return QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
}

/*---------------------------------------------------------------------------*/

} // namespace Time
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __T_TIME_HPP__
