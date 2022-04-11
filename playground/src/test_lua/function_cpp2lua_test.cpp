﻿#include "pch.h"
#include "function_cpp2lua_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace function_cpp2lua_test
{
	r2cm::iItem::TitleFuncT Argument2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Argument 2";
		};
	}
	r2cm::iItem::DoFuncT Argument2::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			std::cout << r2::tab << "+ Add Function : Sum( arg1, arg2 )" << r2::linefeed2;
			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_cpp2lua_test_01.lua" ) );
			DECLARATION_MAIN( const int arg_count = 2 );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready With Arg x 1" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				EXPECT_TRUE( lua_isfunction( lua_state_obj, 1 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call With Arg x 1" << r2::linefeed2;

				EXPECT_EQ( LUA_ERRRUN, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintLuaError( lua_state_obj );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready With Arg x 2" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 456 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call With Arg x 2" << r2::linefeed2;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const auto result = lua_tonumber( lua_state_obj, -1 ) );
				std::cout << r2::tab << "result : " << result << r2::linefeed;
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}
