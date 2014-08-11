
#ifndef __LM_ILANDSCAPE_SERIALIZER_HPP__
#define __LM_ILANDSCAPE_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape;
struct ILandscapeModel;

/*---------------------------------------------------------------------------*/

struct ILandscapeSerializer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void load( ILandscape& _landscape, const QString& _filePath ) = 0;

	virtual void loadObjects( const ILandscapeModel& _landscapeModel, ILandscape& _landscape, const QString& _filePath ) = 0;

	virtual void save( const ILandscapeModel& _landscapeModel, const ILandscape& _landscape, const QString& _filePath ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_SERIALIZER_HPP__
