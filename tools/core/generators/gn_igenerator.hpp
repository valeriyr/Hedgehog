
#ifndef __GN_IGENERATOR_HPP__
#define __GN_IGENERATOR_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace Generators {

/*---------------------------------------------------------------------------*/

struct IGenerator
{
	typedef qint32 IdType;

	virtual IdType generate() = 0;

	virtual reset() = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Generators
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __GN_IGENERATOR_HPP__
