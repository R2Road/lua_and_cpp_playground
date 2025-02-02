﻿#include "memory_allocation_test.h"
#include "memory_allocation_test_helper_custom.hpp"
#include "memory_allocation_test_helper_pool_01.hpp"
#include "memory_allocation_test_helper_pool_02.hpp"

#include <conio.h>

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace memory_allocation_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "memory allocation : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			OUTPUT_NOTE( "luaL_newstate 를 사용하면 lauxlib.c 의 기본 메모리 할당자 l_alloc 가 사용된다." );

			std::cout << r2cm::split;

			{
				OUTPUT_FILE( "resources/lua_l_alloc.txt" );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( lua_State* lua_state_obj = luaL_newstate() );
				PROCESS_MAIN( lua_close( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Custom::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "memory allocation : Custom";
		};
	}
	r2cm::iItem::DoFunctionT Custom::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			OUTPUT_NOTE( "lua_newstate 를 사용하면 메모리 할당자의 설정이 가능하다." );
			OUTPUT_NOTE( "memory pool 등이 활용될 때 사용하자." );
			OUTPUT_NOTE( "ud( user data ) 는 추가 작업을 위해 무언가를 넘겨 주고 싶을 때 사용하자." );

			std::cout << r2cm::split;

			{
				OUTPUT_FILE( "src/test_lua/test/memory_allocation_test_helper_custom.hpp" );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( void* ud = nullptr );
				DECLARATION_MAIN( lua_State* lua_state_obj = lua_newstate( CustomMemoryAllocator::l_alloc, ud ) );
				PROCESS_MAIN( lua_close( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Pool_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "memory allocation : Pool 1";
		};
	}
	r2cm::iItem::DoFunctionT Pool_1::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			OUTPUT_FILE( "src/test_lua/test/memory_allocation_test_helper_pool_01.hpp" );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( LuaMemoryPool_01 pool );
			DECLARATION_MAIN( lua_State* l = lua_newstate( LuaMemoryPool_01::l_alloc, &pool ) );
			
			std::cout << r2cm::split;

			PROCESS_MAIN( lua_close( l ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Pool_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "memory allocation : Pool 2";
		};
	}
	r2cm::iItem::DoFunctionT Pool_2::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			OUTPUT_FILE( "src/test_lua/test/memory_allocation_test_helper_pool_02.hpp" );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( constexpr int pool_size = 1024 * 30 );
			DECLARATION_MAIN( char memory[pool_size] = {} );
			DECLARATION_MAIN( LuaMemoryPool_02 pool( &memory[0], &memory[pool_size - 1] ) );
			DECLARATION_MAIN( lua_State* l = lua_newstate( LuaMemoryPool_02::l_alloc, &pool ) );
			pool.OutputInfo();

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( luaL_openlibs( l ) );
				pool.OutputInfo();
			}

			std::cout << r2cm::split;

			{
				OUTPUT_FILE( "resources/memory_allocation_test_pool_01.lua" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::DoFile_Silent( l, "resources/memory_allocation_test_pool_01.lua" ) );

				std::cout << r2cm::linefeed;

				pool.OutputInfo();
			}

			std::cout << r2cm::split;

			PROCESS_MAIN( lua_close( l ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
