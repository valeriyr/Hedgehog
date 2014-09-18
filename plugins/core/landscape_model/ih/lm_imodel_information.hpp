
#ifndef __LM_IMODEL_INFORMATION_HPP__
#define __LM_IMODEL_INFORMATION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_MODEL_INFORMATION = 3;

/*---------------------------------------------------------------------------*/

struct IModelInformation
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual QString getLandscapesDirectory() const = 0;

	virtual QString getReplaysDirectory() const = 0;

	virtual QString getScriptsRootDirectory() const = 0;

	virtual QString getObjectsScriptsDirectory() const = 0;

	virtual QString getAiScriptsDirectory() const = 0;

/*---------------------------------------------------------------------------*/

	virtual QString generateLandscapePath( const QString& _name ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IMODEL_INFORMATION_HPP__
