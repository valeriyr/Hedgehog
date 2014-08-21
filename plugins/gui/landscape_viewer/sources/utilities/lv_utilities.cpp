
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/utilities/lv_utilities.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {
namespace Utilities {

/*---------------------------------------------------------------------------*/

static const QString ColorPartSeparator = ", ";

/*---------------------------------------------------------------------------*/


QString
colorToString( const QColor& _color )
{
	QString text;
	QTextStream stream( &text );

	stream << _color.red() << ColorPartSeparator << _color.green() << ColorPartSeparator << _color.blue();

	return text;

} // colorToString


/*---------------------------------------------------------------------------*/


QColor
colorFromString( const QString& _string )
{
	QStringList parts( _string.split( ColorPartSeparator ) );

	return QColor( parts[ 0 ].toInt(), parts[ 1 ].toInt(), parts[ 2 ].toInt() );

} // colorFromString


/*---------------------------------------------------------------------------*/

} // namespace Utilities
} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
