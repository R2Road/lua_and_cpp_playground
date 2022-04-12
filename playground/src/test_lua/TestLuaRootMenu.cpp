#include "pch.h"
#include "TestLuaRootMenu.h"

#include <conio.h>
#include <sstream>

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "lua_state_test.h"
#include "luaL_dofile_test.h"
#include "luaL_dostring_test.h"
#include "luaL_openlibs_test.h"

#include "function_cpp2lua_test.h"
#include "function_lua2cpp_test.h"

#include "GlobalMenu.h"
#include "MainMenu.h"
#include "StackMenu.h"
#include "TableMenu.h"

namespace
{
	std::string MakeMenuString()
	{
		std::stringstream ss;
		ss << "+ Menu" << r2::linefeed;
		ss << "R : step_PCall_04_CallCPPFunction" << r2::linefeed;

		ss << r2::linefeed << "Press Number" << r2::linefeed;

		return std::string( ss.str() );
	}

	void ShowMenu()
	{
		static std::string menu_string( std::move( MakeMenuString() ) );
		std::cout << menu_string;
	}
}

r2cm::MenuUp TestLuaRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', lua_state_test::Basic::GetInstance() );
		ret->AddItem(
			'2'
			, []()->const char* { return StackMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( StackMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'3'
			, []()->const char* { return GlobalMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( GlobalMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem( '4', luaL_dostring_test::Basic::GetInstance() );
		ret->AddItem( '5', luaL_dofile_test::Basic::GetInstance() );
		ret->AddItem( '6', luaL_openlibs_test::Basic::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem(
			'q'
			, []()->const char* { return TableMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TableMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);


		ret->AddLineFeed();


		ret->AddItem( 'a', function_cpp2lua_test::Basic::GetInstance() );
		ret->AddItem( 's', function_cpp2lua_test::Argument2::GetInstance() );
		ret->AddItem( 'd', function_cpp2lua_test::GetTable::GetInstance() );


		ret->AddLineFeed();
		


		ret->AddSplit();


		ret->AddItem(
			32
			, []()->const char* { return "All"; }
			, []()->r2cm::eTestEndAction
			{
				int input = 0;
				bool process = true;
				while( process )
				{
					ShowMenu();

					input = _getch();
					system( "cls" );

					switch( input )
					{
					case 'r':
						step::PCall_04_CallCPPFunction();
						break;

					case 27: // ESC
						process = false;
						break;
					}

					std::cout << r2::linefeed << "Press Any Key" << r2::linefeed;
					_getch();
					system( "cls" );
				}

				return r2cm::eTestEndAction::Pause;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return MainMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( MainMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}