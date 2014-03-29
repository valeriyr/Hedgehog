
#ifndef __LM_MODEL_LOCKER_HPP__
#define __LM_MODEL_LOCKER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_imodel_locker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModel;
class LandscapeModel;

/*---------------------------------------------------------------------------*/

class ModelLocker
	:	public Tools::Core::BaseWrapper< IModelLocker >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ModelLocker( boost::intrusive_ptr< LandscapeModel >& _landscapeModel );

	virtual ~ModelLocker();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscapeModel > getLandscapeModel() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QMutexLocker m_lockerHolder;

	boost::intrusive_ptr< LandscapeModel > m_landscapeModel;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MODEL_LOCKER_HPP__
