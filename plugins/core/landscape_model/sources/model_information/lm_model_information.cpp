
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/model_information/lm_model_information.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ModelInformation::ModelInformation( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // ModelInformation::ModelInformation


/*---------------------------------------------------------------------------*/


ModelInformation::~ModelInformation()
{
} // ModelInformation::~ModelInformation


/*---------------------------------------------------------------------------*/


QString
ModelInformation::getLandscapesDirectory() const
{
	return m_environment.getApplicationDirectory() + "/" + Resources::LandscapesDirectoryName;

} // ModelInformation::getLandscapesDirectory


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
