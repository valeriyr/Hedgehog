
#ifndef __LM_LANDSCAPE_SERIALIZER_HPP__
#define __LM_LANDSCAPE_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class LandscapeSerializer
	:	public Tools::Core::BaseWrapper< ILandscapeSerializer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeSerializer();

	virtual ~LandscapeSerializer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void load(
			IEditableLandscape& _landscape
		,	const QString& _filePath ) const;

	/*virtual*/ void save(
			const ILandscape& _landscape
		,	const QString& _filePath ) const;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_SERIALIZER_HPP__
