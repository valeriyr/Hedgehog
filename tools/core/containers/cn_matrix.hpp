
#ifndef __CN_MATRIX_HPP__
#define __CN_MATRIX_HPP__


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace Containers {

/*---------------------------------------------------------------------------*/

template < typename _TElementType >
class Matrix
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Matrix()
		:	m_width( 0 )
		,	m_height( 0 )
		,	m_matrix( NULL )
	{
	}

	Matrix( const unsigned int _width, const unsigned int _height )
		:	m_width( 0 )
		,	m_height( 0 )
		,	m_matrix( NULL )
	{
		resize( _width, _height );
	}

	~Matrix()
	{
		clear();
	}

/*---------------------------------------------------------------------------*/

	Matrix( const Matrix& _matrix )
	{
		*this = _matrix;
	}

	Matrix& operator = ( const Matrix& _matrix )
	{
		resize( _matrix.m_width, _matrix.m_height );

		for ( unsigned int i = 0; i < m_width; ++i )
		{
			for ( unsigned int j = 0; j < m_height; ++j )
			{
				m_matrix[ i ][ j ] = _matrix.m_matrix[ i ][ j ];
			}
		}
	}

/*---------------------------------------------------------------------------*/

	void resize( const unsigned int _width, const unsigned int _height )
	{
		assert( _width > 0 );
		assert( _height > 0 );

		if ( m_width != _width || m_height != _height )
		{
			clear();

			m_width = _width;
			m_height = _height;

			m_matrix = new _TElementType*[ m_width ];
			for ( unsigned int i = 0; i < m_width; ++i )
				m_matrix[ i ] = new _TElementType[ m_height ];
		}

		for ( unsigned int i = 0; i < m_width; ++i )
		{
			for ( unsigned int j = 0; j < m_height; ++j )
			{
				m_matrix[ i ][ j ] = _TElementType();
			}
		}
	}

	void clear()
	{
		if ( m_matrix )
		{
			for ( unsigned int i = 0; i < m_width; ++i )
				delete m_matrix[ i ];
			delete [] m_matrix;

			m_matrix = NULL;
			m_width = 0;
			m_height = 0;
		}
	}

/*---------------------------------------------------------------------------*/

	const unsigned int getWidth() const
	{
		return m_width;
	}

	const unsigned int getHeight() const
	{
		return m_height;
	}

	const _TElementType& getElement( const unsigned int _x, const unsigned int _y ) const
	{
		assert( m_width > 0 );
		assert( m_height > 0 );

		assert( _x >= 0 );
		assert( _y >= 0 );
		assert( _x < m_width );
		assert( _y < m_height );

		return m_matrix[ _x ][ _y ];
	}

	void setElement( const unsigned int _x, const unsigned int _y, const _TElementType& _element )
	{
		assert( m_width > 0 );
		assert( m_height > 0 );

		assert( _x >= 0 );
		assert( _y >= 0 );
		assert( _x < m_width );
		assert( _y < m_height );

		m_matrix[ _x ][ _y ] = _element;
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	unsigned int m_width;

	unsigned int m_height;

	_TElementType ** m_matrix;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Containers
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __CN_MATRIX_HPP__
