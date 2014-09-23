
#ifndef __LM_UNIQUE_ID_GENERATOR_HPP__
#define __LM_UNIQUE_ID_GENERATOR_HPP__

#include "generators/gn_igenerator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class UniqueIdGenerator
	:	public Tools::Core::Generators::IGenerator
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	UniqueIdGenerator();

/*---------------------------------------------------------------------------*/

	/*virtual*/ Tools::Core::Generators::IGenerator::IdType generate();

	/*virtual*/ void reset();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	Tools::Core::Generators::IGenerator::IdType m_idCounter;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GN_UNIQUE_ID_GENERATOR_HPP__
