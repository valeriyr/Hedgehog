
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/unique_id_generator/lm_unique_id_generator.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


UniqueIdGenerator::UniqueIdGenerator()
	:	m_idCounter( 0 )
{
} // UniqueIdGenerator::UniqueIdGenerator


/*---------------------------------------------------------------------------*/


Tools::Core::Generators::IGenerator::IdType
UniqueIdGenerator::generate()
{
	return ++m_idCounter;

} // UniqueIdGenerator::generate


/*---------------------------------------------------------------------------*/


void
UniqueIdGenerator::reset()
{
	m_idCounter = 0;

} // UniqueIdGenerator::reset


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
