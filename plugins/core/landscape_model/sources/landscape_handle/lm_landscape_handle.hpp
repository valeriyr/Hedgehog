
#ifndef __LM_LANDSCAPE_HANDLE_HPP__
#define __LM_LANDSCAPE_HANDLE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_handle.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeManagerInternal;

/*---------------------------------------------------------------------------*/

class LandscapeHandle
	:	public Tools::Core::BaseWrapper< ILandscapeHandle >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeHandle( ILandscapeManagerInternal& _landscapeManager );

	virtual ~LandscapeHandle();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeManagerInternal& m_landscapeManager;

	QMutexLocker m_lockerHolder;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_HANDLE_HPP__
