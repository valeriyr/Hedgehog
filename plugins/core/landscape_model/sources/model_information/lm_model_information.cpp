
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/model_information/lm_model_information.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/h/lm_resources.hpp"


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


QString
ModelInformation::getReplaysDirectory() const
{
	return m_environment.getApplicationDirectory() + "/" + Resources::ReplaysDirectoryName;

} // ModelInformation::getReplaysDirectory


/*---------------------------------------------------------------------------*/


QString
ModelInformation::generateLandscapePath( const QString& _name ) const
{
	return getLandscapesDirectory() + "/" + _name + "." + Resources::LandscapeFileExtension;

} // ModelInformation::generateLandscapePath


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
