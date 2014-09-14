
#ifndef __ST_QVARIANT_EXTENSIONS_HPP__
#define __ST_QVARIANT_EXTENSIONS_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace Streaming {

/*---------------------------------------------------------------------------*/

inline QString toString( const QVariant& _value )
{
	QByteArray byteArray;
	QBuffer writeBuffer( &byteArray );
	writeBuffer.open( QIODevice::WriteOnly );
	QDataStream out( &writeBuffer );

	out << _value;

	writeBuffer.close();

	return QString::fromUtf8( byteArray.toBase64() );
}

/*---------------------------------------------------------------------------*/

inline QVariant fromString( const QString& _value )
{
	QByteArray data = QByteArray::fromBase64( _value.toUtf8() );
	QBuffer readBuffer( &data );
	readBuffer.open( QIODevice::ReadOnly );
	QDataStream in( &readBuffer );

	QVariant result;

	in >> result;

	return result;
}

/*---------------------------------------------------------------------------*/

} // namespace Streaming
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __ST_QVARIANT_EXTENSIONS_HPP__
