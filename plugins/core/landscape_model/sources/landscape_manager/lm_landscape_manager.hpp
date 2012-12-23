
#ifndef __LM_LANDSCAPE_MANAGER_HPP__
#define __LM_LANDSCAPE_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeSerializer;

/*---------------------------------------------------------------------------*/

class LandscapeManager
	:	public Tools::Core::BaseWrapper< ILandscapeManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeManager( const ILandscapeSerializer& _landscapeSerializer );

	virtual ~LandscapeManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initCurrentLandscape ( const QString& _filePath );

	/*virtual*/ void closeCurrentLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ ILandscape::Ptr getCurrentLandscape() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeSerializer& m_landscapeSerializer;

	ILandscape::Ptr m_currentLandscape;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MANAGER_HPP__
