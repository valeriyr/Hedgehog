
#ifndef __T_TIME_HPP__
#define __T_TIME_HPP__


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace Time {

/*---------------------------------------------------------------------------*/

typedef unsigned long long Milliseconds;

/*---------------------------------------------------------------------------*/

inline Milliseconds currentTime()
{
	QDateTime currentTime( QDateTime::currentDateTimeUtc() );
	return currentTime.toMSecsSinceEpoch();
}

/*---------------------------------------------------------------------------*/

} // namespace Time
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __T_TIME_HPP__
