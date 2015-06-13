
#ifndef __TL_OBJECT_HPP__
#define __TL_OBJECT_HPP__

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "allocators/al_block_allocator.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

class Object;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

struct IMember
	:	public BlockAllocator<>
{
	virtual ~IMember() {}

	virtual IMember* clone() const = 0;

	virtual void* getValue() = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template< typename _TValue >
struct Member
	:	public IMember
{

	Member( const _TValue& _value )
		:	m_value( _value )
	{}

	virtual ~Member() {}

	/*virtual*/ IMember* clone() const { return new Member( m_value ); }

	/*virtual*/ void* getValue() { return &m_value; }

	_TValue m_value;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class MemberHolder
{

public:

	MemberHolder()
		:	m_member()
	{}

	template< typename _TTValue >
	MemberHolder( const _TTValue& _value )
		:	m_member( new Member< _TTValue >( _value ) )
	{}

	MemberHolder( const MemberHolder& _other )
	{
		if ( _other.m_member )
			m_member.reset( _other.m_member->clone() );
	}

	MemberHolder& operator= ( const MemberHolder& _other )
	{
		if ( &_other != this )
		{
			reset();

			if ( _other.m_member )
				m_member.reset( _other.m_member->clone() );
		}

		return *this;
	}

	~MemberHolder() { reset(); }

	void reset() { m_member.reset(); }

	IMember* getMember() const { return m_member.get(); }

private:

	boost::scoped_ptr< IMember > m_member;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#define EXPAND( PARAMETER )									PARAMETER

#define IF_NOT_ZERO_0( PARAMETER )
#define IF_NOT_ZERO_1( PARAMETER )							PARAMETER
#define IF_NOT_ZERO_2( PARAMETER )							PARAMETER
#define IF_NOT_ZERO_3( PARAMETER )							PARAMETER
#define IF_NOT_ZERO_4( PARAMETER )							PARAMETER

#define IF_NOT_ZERO( COUNT, PARAMETER )						IF_NOT_ZERO_##COUNT( PARAMETER )

#define FOR_EACH_0( MACRO, FAKE )
#define FOR_EACH_1( MACRO, FIRST )							MACRO( FIRST )
#define FOR_EACH_2( MACRO, FIRST, SECOND )					MACRO( FIRST ), FOR_EACH_1( MACRO, SECOND )
#define FOR_EACH_3( MACRO, FIRST, SECOND, THIRD )			MACRO( FIRST ), FOR_EACH_2( MACRO, SECOND, THIRD )
#define FOR_EACH_4( MACRO, FIRST, SECOND, THIRD, FOURTH )	MACRO( FIRST ), FOR_EACH_3( MACRO, SECOND, THIRD, FOURTH )

#define FOR_EACH( MACRO, COUNT, ... )						EXPAND( FOR_EACH_##COUNT( MACRO, __VA_ARGS__ ) )

#define TYPENAME_EXPANDER( PARAMETER )						typename PARAMETER
#define NAME_EXPANDER( PARAMETER )							PARAMETER##Arg
#define ARGUMENT_CONSTRUCTOR( PARAMETER )					PARAMETER NAME_EXPANDER( PARAMETER )
#define PASS( PARAMETER )									PARAMETER

#define COMMA												,
#define VOID_METHOD_CALL_TEMPLATE_LIST( COUNT, ... )		template< EXPAND( FOR_EACH( TYPENAME_EXPANDER, COUNT, __VA_ARGS__ ) ) >

#define DEFINE_METHOD( COUNT, ... )																																			\
																																											\
	template< typename _TReturn IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH( TYPENAME_EXPANDER, COUNT, __VA_ARGS__ ) ) >													\
	Object& pushMethod( const QString& _name, boost::function< _TReturn ( Object& IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH( PASS, COUNT, __VA_ARGS__ ) ) ) > _method )	\
	{																																										\
		assert( !hasMember( _name ) );																																		\
		m_members.insert( std::make_pair( _name, MemberHolder( _method ) ) );																								\
		return *this;																																						\
	}																																										\
																																											\
	template< typename _TReturn IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH( TYPENAME_EXPANDER, COUNT, __VA_ARGS__ ) ) >													\
	_TReturn callMethod( const QString& _name IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH( ARGUMENT_CONSTRUCTOR, COUNT, __VA_ARGS__ ) ) )									\
	{																																										\
		typedef boost::function< _TReturn ( Object& IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH(  PASS, COUNT, __VA_ARGS__ ) ) ) > FunctionType;							\
																																											\
		const FunctionType* member = findMember< FunctionType >( _name );																									\
		assert( member );																																					\
																																											\
		return ( *member )( *this IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH( NAME_EXPANDER, COUNT, __VA_ARGS__ ) ) );													\
	}																																										\
																																											\
	IF_NOT_ZERO( COUNT, EXPAND( VOID_METHOD_CALL_TEMPLATE_LIST( COUNT, __VA_ARGS__ ) ) )																					\
	void callVoidMethod( const QString& _name IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH( ARGUMENT_CONSTRUCTOR, COUNT, __VA_ARGS__ ) ) )									\
	{																																										\
		typedef boost::function< void ( Object& IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH(  PASS, COUNT, __VA_ARGS__ ) ) ) > FunctionType;								\
																																											\
		const FunctionType* member = findMember< FunctionType >( _name );																									\
		assert( member );																																					\
																																											\
		( *member )( *this IF_NOT_ZERO( COUNT, COMMA ) EXPAND( FOR_EACH( NAME_EXPANDER, COUNT, __VA_ARGS__ ) ) );															\
	}																																										\

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class Object
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	typedef boost::shared_ptr< Object > Ptr;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Object() {}

	~Object() { clear(); }

/*---------------------------------------------------------------------------*/

	template< typename _TMember >
	const _TMember& getMember( const QString& _name ) const
	{
		return findMemberRecursive< _TMember >( _name );
	}

	template< typename _TMember >
	_TMember& getMember( const QString& _name )
	{
		return findMemberRecursive< _TMember >( _name );
	}

	Ptr getMemberObject( const QString& _name )
	{
		return findMemberObject( _name );
	}

	Ptr getMemberObject( const QString& _name ) const
	{
		return findMemberObject( _name );
	}

/*---------------------------------------------------------------------------*/

	bool hasMember( const QString& _name ) const
	{
		QStringList list( _name.split( "." ) );

		assert( list.size() >= 1 );

		QString child( list.first() );
		list.pop_front();

		if ( list.size() == 0 )
		{
			return m_members.find( _name ) != m_members.end();
		}
		else if ( hasMember< Object >( child ) )
		{
			return findMember< Object >( child )->hasMember( generateName( list ) );
		}
		else if ( hasMember< Ptr >( child ) )
		{
			return ( *findMember< Ptr >( child ) )->hasMember( generateName( list ) );
		}

		return false;
	}

	template< typename _TMember >
	bool hasMember( const QString& _name ) const
	{
		QStringList list( _name.split( "." ) );

		assert( list.size() >= 1 );

		QString child( list.first() );
		list.pop_front();

		if ( list.size() == 0 )
		{
			return findMember< _TMember >( child );
		}
		else if ( hasMember< Object >( child ) )
		{
			return findMember< Object >( child )->hasMember< _TMember >( generateName( list ) );
		}
		else if ( hasMember< Ptr >( child ) )
		{
			return ( *findMember< Ptr >( child ) )->hasMember< _TMember >( generateName( list ) );
		}

		return false;
	}

/*---------------------------------------------------------------------------*/

	DEFINE_METHOD( 0 )
	DEFINE_METHOD( 1, _TParamerer1 )
	DEFINE_METHOD( 2, _TParamerer1, _TParamerer2 )
	DEFINE_METHOD( 3, _TParamerer1, _TParamerer2, _TParamerer3 )
	DEFINE_METHOD( 4, _TParamerer1, _TParamerer2, _TParamerer3, _TParamerer4 )

/*---------------------------------------------------------------------------*/

	template< typename _TMember >
	Object& pushMember( const QString& _name, const _TMember& _value )
	{
		QStringList list( _name.split( "." ) );

		assert( list.size() >= 1 );
		assert( !hasMember< _TMember >( _name ) );

		QString child( list.first() );
		list.pop_front();

		if ( list.size() == 0 )
		{
			assert( !hasMember( child ) );
			m_members.insert( std::make_pair( child, MemberHolder( _value ) ) );
		}
		else if ( hasMember< Object >( child ) )
		{
			findMember< Object >( child )->pushMember( generateName( list ), _value );
		}
		else if ( hasMember< Ptr >( child ) )
		{
			( *findMember< Ptr >( child ) )->pushMember( generateName( list ), _value );
		}
		else
		{
			assert( !hasMember( child ) );

			Ptr object( new Object() );
			m_members.insert( std::make_pair( child, MemberHolder( object ) ) );

			object->pushMember( generateName( list ), _value );
		}

		return *this;
	}

	void removeMember( const QString& _name )
	{
		QStringList list( _name.split( "." ) );

		assert( list.size() >= 1 );

		QString child( list.first() );
		list.pop_front();

		if ( list.size() == 0 )
		{
			m_members.erase( child );
		}
		else if ( hasMember< Object >( child ) )
		{
			findMember< Object >( child )->removeMember( generateName( list ) );
		}
		else if ( hasMember< Ptr >( child ) )
		{
			( *findMember< Ptr >( child ) )->removeMember( generateName( list ) );
		}
	}

	void clear()
	{
		m_members.clear();
	}

/*---------------------------------------------------------------------------*/

	static QString generateName( const QString& _part1, const QString& _part2 )
	{
		return _part1 + "." + _part2;
	}

	static QString generateName( const QString& _part1, const QString& _part2, const QString& _part3 )
	{
		return generateName( _part1, _part2 ) + "." + _part3;
	}

	static QString generateName( const QStringList& _list )
	{
		QString name;

		QStringList::ConstIterator
				begin = _list.begin()
			,	end = _list.end();

		for ( ; begin != end; ++begin )
		{
			if ( begin != _list.begin() )
				name += ".";

			name += *begin;
		}

		return name;
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	template< typename _TMember >
	_TMember* findMember( const QString& _name ) const
	{
		MembersCollectionIterator iterator = m_members.find( _name );

		if ( iterator == m_members.end() )
			return NULL;

		Member< _TMember >* member = dynamic_cast< Member< _TMember >* >( iterator->second.getMember() );

		return member != NULL ? &member->m_value : NULL;
	}

	template< typename _TMember >
	_TMember& findMemberRecursive( const QString& _name ) const
	{
		QStringList list( _name.split( "." ) );

		assert( list.size() >= 1 );
		assert( hasMember< _TMember >( _name ) );

		QString child( list.first() );
		list.pop_front();

		if ( list.size() == 0 )
			return *findMember< _TMember >( child );
		else if ( hasMember< Object >( child ) )
			return findMember< Object >( child )->getMember< _TMember >( generateName( list ) );
		else
			return ( *findMember< Ptr >( child ) )->getMember< _TMember >( generateName( list ) );
	}

	Ptr findMemberObject( const QString& _name ) const
	{
		if ( !hasMember< Ptr >( _name ) )
			return Ptr();

		return findMemberRecursive< Ptr >( _name );
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef std::map< QString, MemberHolder > MembersCollection;
	typedef MembersCollection::const_iterator MembersCollectionIterator;

	MembersCollection m_members;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __TL_OBJECT_HPP__
