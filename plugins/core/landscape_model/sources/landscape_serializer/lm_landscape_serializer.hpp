
#ifndef __LM_LANDSCAPE_SERIALIZER_HPP__
#define __LM_LANDSCAPE_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"

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

	/*virtual*/ void load( ILandscape& _landscape, const QString& _filePath );

	/*virtual*/ void loadObjects( const ILandscapeModel& _landscapeModel, ILandscape& _landscape, const QString& _filePath );

	/*virtual*/ void save( const ILandscapeModel& _landscapeModel, const ILandscape& _landscape, const QString& _filePath ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onHMapElement( ILandscape& _landscape, const QString& _version, const int _width, const int _height );
	void onSurfaceElement( ILandscape& _landscape, const QString& _data );
	void onObjectElement(
			const ILandscapeModel& _landscapeModel
		,	ILandscape& _landscape
		,	const QString& _name
		,	const int _x
		,	const int _y
		,	const StartPoint::Id& _id );
	void onStartPoint( ILandscape& _landscape, const StartPoint::Id& _id, const int _x, const int _y );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_SERIALIZER_HPP__
