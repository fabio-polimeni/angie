#ifndef ANGIE_BITFIELD_HPP
#define ANGIE_BITFIELD_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-02-09													
/// Updated : 																
/// Licence : This source is under MIT License								
/// File    : bitfield.hpp 														
///////////////////////////////////////////////////////////////////////////////
/// Description:															
///																			
///	A class that allows to use a C++11 enum class definition as flag type.
/// E.g.
///	enum class Input { In = 0, Out = 1 };
/// Bitfield<Input> in_out = Input.In | Input.Out;
///////////////////////////////////////////////////////////////////////////////
#include <bitset>
#include <type_traits>

#include <angie/config.hpp>
#include <angie/types.hpp>

namespace angie
{
	template < typename T >
	class Bitfield
	{
		
	private:

		typedef T enum_t;
		typedef typename std::underlying_type<T>::type underlying_t;
		
		static_assert(sizeof(underlying_t) <= sizeof(unsigned long long),
			"The enum T can't be bigger than long long (at least 64 bits) bits!");

		typedef std::bitset<sizeof(underlying_t)*8> bitset_t;
		bitset_t m_Bitset;

	public:

		Bitfield( void ) : m_Bitset(static_cast<underlying_t>(0)) { }
		Bitfield( T value ) : m_Bitset(1<<static_cast<underlying_t>(value)) { }
		
		//Bitfield( const Bitfield& bf ) : m_Bitset(bf.m_Bitset) { }
		//Bitfield( Bitfield&& bf ) : m_Bitset(std::move(bf.m_Bitset)) { }

		Bitfield( const bitset_t& bs ) : m_Bitset(bs) { }

		bitset_t& Bitset( void ) { return m_Bitset; }
		const bitset_t& Bitset( void ) const { return m_Bitset; }

		void Set( T value ) { m_Bitset.set(1<<static_cast<underlying_t>(value)); }
		void Reset( T value ) { m_Bitset.reset(1<<static_cast<underlying_t>(value)); }
		void Flip( T value ) { m_Bitset.flip(1<<static_cast<underlying_t>(value)); }

		void Set( void ) { m_Bitset.set(); }
		void Reset( void ) { m_Bitset.reset(); }
		void Flip( void ) { m_Bitset.flip(); }

		bool All( void ) const { return m_Bitset.all(); }
		bool Any( void ) const { return m_Bitset.any(); }
		bool None( void ) const { return m_Bitset.none(); }

		bool Has( T value ) const { return m_Bitset.test(static_cast<size_t>(value)); }

		bool operator==( const Bitfield& rhs ) const { return m_Bitset == rhs.m_Bitset; }
		
		Bitfield&	operator&=( const Bitfield& other ) { m_Bitset &= other.m_Bitset; return *this; }
		Bitfield&	operator|=( const Bitfield& other ) { m_Bitset |= other.m_Bitset; return *this; }
		Bitfield&	operator^=( const Bitfield& other ) { m_Bitset ^= other.m_Bitset; return *this; }
		Bitfield	operator~() const { return ~m_Bitset; }

		Bitfield	operator<<( size_t pos ) const { return m_Bitset << pos; }
		Bitfield&	operator<<=( size_t pos ) { m_Bitset << pos; return *this; }
		Bitfield	operator>>( size_t pos ) const { return m_Bitset >> pos; }
		Bitfield&	operator>>=( size_t pos ) { m_Bitset >>= pos; return *this; }

	};

	template< typename T > inline
	Bitfield<T> operator&(const Bitfield<T>& left, const Bitfield<T>& right) noexcept
	{
		Bitfield<T> ans(left);
		return (ans &= right);
	}

	template< typename T > inline
	Bitfield<T> operator&(T left, T right) noexcept
	{
		Bitfield<T> ans(left);
		return (ans &= right);
	}

	template< typename T > inline
	Bitfield<T> operator|(const Bitfield<T>& left, const Bitfield<T>& right) noexcept
	{
		Bitfield<T> ans(left);
		return (ans |= right);
	}

	template< typename T > inline
	Bitfield<T> operator|(T left, T right) noexcept
	{
		Bitfield<T> ans(left);
		return (ans |= right);
	}

	template< typename T > inline
	Bitfield<T> operator^(const Bitfield<T>& left, const Bitfield<T>& right) noexcept
	{
		Bitfield<T> ans(left);
		return (ans ^= right);
	}

	template< typename T > inline
	Bitfield<T> operator^(T left, T right) noexcept
	{
		Bitfield<T> ans(left);
		return (ans ^= right);
	}
}

#endif // ANGIE_BITFIELD_HPP
