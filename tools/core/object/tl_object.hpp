
#ifndef __TL_OBJECT_HPP__
#define __TL_OBJECT_HPP__

#include <boost/scoped_ptr.hpp>

#include "allocators/al_block_allocator.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

struct IMember
	:	public BlockAllocator<>
{
	virtual ~IMember() {}

	virtual IMember* clone() const = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template< typename _TValue >
struct Member
	:	public IMember
{

public:

	Member( const _TValue& _value )
		:	m_value( _value )
	{}

	virtual ~Member() {}

	/*virtual*/ IMember* clone() const { return new Member( m_value ); }

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
		:	m_member()
	{
		if ( _other.m_member )
			m_member.reset( _other.m_member->clone() );
	}

	MemberHolder& operator= ( const MemberHolder& _other )
	{
		reset();

		if ( _other.m_member )
			m_member.reset( _other.m_member->clone() );

		return *this;
	}

	~MemberHolder() { reset(); }

	void reset()
	{
		m_member.reset();
	}

	IMember* getMember() const { return m_member.get(); }

private:

	boost::scoped_ptr< IMember > m_member;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class Object
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Object() {}

	~Object() { clear(); }

/*---------------------------------------------------------------------------*/

	template< typename _TMember >
	const _TMember& getMember( const QString& _name ) const
	{
		_TMember* member = getMemberPtr< _TMember >( _name );
		assert( member );

		return *member;
	}

	template< typename _TMember >
	bool getMember( const QString& _name, _TMember& _output ) const
	{
		_TMember* member = getMemberPtr< _TMember >( _name );

		if ( member == NULL )
			return false;

		_output = *member;

		return true;
	}

	template< typename _TMember >
	_TMember& getMember( const QString& _name )
	{
		_TMember* member = getMemberPtr< _TMember >( _name );
		assert( member );

		return *member;
	}

	template< typename _TMember >
	_TMember* getMemberPtr( const QString& _name ) const
	{
		MembersCollectionIterator iterator = m_members.find( _name );

		if ( iterator == m_members.end() )
			return NULL;

		Member< _TMember >* member = dynamic_cast< Member< _TMember >* >( iterator->second.getMember() );

		return member != NULL ? &member->m_value : NULL;
	}

/*---------------------------------------------------------------------------*/

	bool hasMember( const QString& _name ) const { return m_members.find( _name ) != m_members.end(); }

/*---------------------------------------------------------------------------*/

	template< typename _TMember >
	Object& pushMember( const QString& _name, const _TMember& _value )
	{
		assert( !hasMember( _name ) );
		m_members.insert( std::make_pair( _name, MemberHolder( _value ) ) );
		return *this;
	}

/*---------------------------------------------------------------------------*/

	void removeMember( const QString& _name )
	{
		m_members.erase( _name );
	}

	void clear()
	{
		m_members.clear();
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
