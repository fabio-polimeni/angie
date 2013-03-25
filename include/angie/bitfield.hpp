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
	class bitfield
	{
		
	public:

		typedef T enum_t;
		typedef typename std::underlying_type<T>::type underlying_t;
		typedef std::bitset<sizeof(underlying_t)*8> bitset_t;
		
	private:
		
		static_assert(sizeof(underlying_t) <= sizeof(unsigned long long),
			"The enum T can't be bigger than long long (at least 64 bits) bits!");

		bitset_t m_Bitset;

		bitfield( const bitset_t& bs ) : m_Bitset(bs) { }

	public:

		bitfield( void ) : m_Bitset(static_cast<underlying_t>(0)) { }
		bitfield( T value ) : m_Bitset(1<<static_cast<underlying_t>(value)) { }
		
		//Bitfield( const Bitfield& bf ) : m_Bitset(bf.m_Bitset) { }
		//Bitfield( Bitfield&& bf ) : m_Bitset(std::move(bf.m_Bitset)) { }

		bitset_t& Bitset( void ) { return m_Bitset; }
		const bitset_t& Bitset( void ) const { return m_Bitset; }

		void set( T value ) { m_Bitset.set(1<<static_cast<underlying_t>(value)); }
		void reset( T value ) { m_Bitset.reset(1<<static_cast<underlying_t>(value)); }
		void flip( T value ) { m_Bitset.flip(1<<static_cast<underlying_t>(value)); }

		void set( void ) { m_Bitset.set(); }
		void reset( void ) { m_Bitset.reset(); }
		void flip( void ) { m_Bitset.flip(); }

		bool all( void ) const { return m_Bitset.all(); }
		bool any( void ) const { return m_Bitset.any(); }
		bool none( void ) const { return m_Bitset.none(); }

		bool all( const bitfield& other ) const { return (*this & other) == other; }
		bool any( const bitfield& other ) const { return (*this & other).any(); }

		bool has( T value ) const { return m_Bitset.test(static_cast<size_t>(value)); }

		bool operator==( const bitfield& rhs ) const { return m_Bitset == rhs.m_Bitset; }
		
		bitfield&	operator&=( const bitfield& other ) { m_Bitset &= other.m_Bitset; return *this; }
		bitfield&	operator|=( const bitfield& other ) { m_Bitset |= other.m_Bitset; return *this; }
		bitfield&	operator^=( const bitfield& other ) { m_Bitset ^= other.m_Bitset; return *this; }
		bitfield	operator~() const { return ~m_Bitset; }

		bitfield	operator<<( size_t pos ) const { return m_Bitset << pos; }
		bitfield&	operator<<=( size_t pos ) { m_Bitset << pos; return *this; }
		bitfield	operator>>( size_t pos ) const { return m_Bitset >> pos; }
		bitfield&	operator>>=( size_t pos ) { m_Bitset >>= pos; return *this; }

	};

	template< typename T > inline
	bitfield<T> operator&(const bitfield<T>& left, const bitfield<T>& right) noexcept
	{
		bitfield<T> ans(left);
		return (ans &= right);
	}

	template< typename T > inline
	bitfield<T> operator&(T left, T right) noexcept
	{
		bitfield<T> ans(left);
		return (ans &= right);
	}

	template< typename T > inline
	bitfield<T> operator&(T left, const bitfield<T>& right) noexcept
	{
		bitfield<T> ans(left);
		return (ans &= right);
	}

	template< typename T > inline
	bitfield<T> operator&(const bitfield<T>& left, T right) noexcept
	{
		bitfield<T> ans(left);
		return (ans &= right);
	}

	template< typename T > inline
	bitfield<T> operator|(const bitfield<T>& left, const bitfield<T>& right) noexcept
	{
		bitfield<T> ans(left);
		return (ans |= right);
	}

	template< typename T > inline
	bitfield<T> operator|(T left, T right) noexcept
	{
		bitfield<T> ans(left);
		return (ans |= right);
	}

	template< typename T > inline
	bitfield<T> operator|(T left, const bitfield<T>& right) noexcept
	{
		bitfield<T> ans(left);
		return (ans |= right);
	}

	template< typename T > inline
	bitfield<T> operator|(const bitfield<T>& left, T right) noexcept
	{
		bitfield<T> ans(left);
		return (ans |= right);
	}

	template< typename T > inline
	bitfield<T> operator^(const bitfield<T>& left, const bitfield<T>& right) noexcept
	{
		bitfield<T> ans(left);
		return (ans ^= right);
	}

	template< typename T > inline
	bitfield<T> operator^(T left, T right) noexcept
	{
		bitfield<T> ans(left);
		return (ans ^= right);
	}

	template< typename T > inline
	bitfield<T> operator^(T left, const bitfield<T>& right) noexcept
	{
		bitfield<T> ans(left);
		return (ans ^= right);
	}

	template< typename T > inline
	bitfield<T> operator^(const bitfield<T>& left, T right) noexcept
	{
		bitfield<T> ans(left);
		return (ans ^= right);
	}

	template< typename T > inline
	bitfield<T> operator~(T mask) noexcept
	{
		bitfield<T> ans(mask);
		return ~ans;
	}
}

#endif // ANGIE_BITFIELD_HPP
