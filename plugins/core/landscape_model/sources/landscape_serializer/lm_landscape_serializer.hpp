
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

	/*virtual*/ void save( const ILandscape& _landscape, const QString& _filePath ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onHMapElement( const QString& _version, const int _width, const int _height );
	void onSurfaceElement( const QString& _data );
	void onObjectElement( const QString& _name, const int _x, const int _y, const IPlayer::Id& _playerId );
	void onStartPoint( const IPlayer::Id& _playerId, const int _x, const int _y );

	void onFinishParsing();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	ILandscape* m_currentLoadLandscape;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_SERIALIZER_HPP__
