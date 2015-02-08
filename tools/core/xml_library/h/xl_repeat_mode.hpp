
#ifndef __XL_REPEAT_MODE_HPP__
#define __XL_REPEAT_MODE_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct RepeatMode
{
	enum Enum : qint32
	{
			Once = 0
		,	ZeroAndMore
		,	OneOrMore
	};
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_REPEAT_MODE_HPP__
