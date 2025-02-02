﻿#include "r2lua.h"

#include <cassert>

namespace r2lua
{
	eType GetType( const Value& v )
	{
		return std::visit(
			[]( const auto& x )
			{
				return x.GetType();
			}
			, v
		);
	}
	const char* const GetTypeName( const Value& v )
	{
		const auto r2lua_type = GetType( v );
		return GetTypeName( r2lua_type );
	}
	const char* const GetTypeName( const eType t )
	{
		switch( t )
		{
		case r2lua::eType::Bool:
			return "Bool";
		case r2lua::eType::Number:
			return "Number";
		case r2lua::eType::String:
			return "String";
		default:
			return "Undefined";
		}
	}



	void Push( lua_State* const lua_state_obj, bool b )
	{
		lua_pushboolean( lua_state_obj, b );
	}
	void Push( lua_State* const lua_state_obj, int n )
	{
		Push( lua_state_obj, static_cast<lua_Number>( n ) );
	}
	void Push( lua_State* const lua_state_obj, lua_Number n )
	{
		lua_pushnumber( lua_state_obj, n );
	}
	void Push( lua_State* const lua_state_obj, const char* const str )
	{
		lua_pushstring( lua_state_obj, str );
	}

	r2lua::Value GetValueFromStack( lua_State* const lua_state_obj, int index )
	{
		switch( lua_type( lua_state_obj, index ) )
		{
		case LUA_TBOOLEAN:
			return r2lua::Bool( lua_toboolean( lua_state_obj, index ) );

		case LUA_TNUMBER:
			return r2lua::Number( lua_tonumber( lua_state_obj, index ) );

		case LUA_TSTRING:
			return r2lua::String( lua_tostring( lua_state_obj, index ) );

		default:
			assert( false );
			break;
		}

		return r2lua::Number( 0 );
	}

	r2lua::ValueVector GetValuesFromStack( lua_State* const lua_state_obj )
	{
		r2lua::ValueVector ret;
		{
			const int stack_size = lua_gettop( lua_state_obj );

			for( int i = 1; stack_size >= i; ++i )
			{
				ret.emplace_back( GetValueFromStack( lua_state_obj, i ) );
			}
		}
		return ret;
	}
}