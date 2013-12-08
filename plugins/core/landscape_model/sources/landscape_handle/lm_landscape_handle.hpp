
#ifndef __LM_LANDSCAPE_HANDLE_HPP__
#define __LM_LANDSCAPE_HANDLE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_handle.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModelInternal;

/*---------------------------------------------------------------------------*/

class LandscapeHandle
	:	public Tools::Core::BaseWrapper< ILandscapeHandle >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeHandle( ILandscapeModelInternal& _landscapeModel );

	virtual ~LandscapeHandle();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IEditableLandscape > getLandscape() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeModelInternal& m_landscapeModel;

	QMutexLocker m_lockerHolder;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_HANDLE_HPP__
