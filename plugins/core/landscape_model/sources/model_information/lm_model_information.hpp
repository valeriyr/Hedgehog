
#ifndef __LM_MODEL_INFORMATION_HPP__
#define __LM_MODEL_INFORMATION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_imodel_information.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class ModelInformation
	:	public Tools::Core::BaseWrapper< IModelInformation >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ModelInformation( const IEnvironment& _environment );

	virtual ~ModelInformation();

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString getLandscapesDirectory() const;

	/*virtual*/ QString getReplaysDirectory() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString generateLandscapePath( const QString& _name ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MODEL_INFORMATION_HPP__
