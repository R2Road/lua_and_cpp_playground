﻿//
// # ref
// - EN Manual : https://www.lua.org/manual/5.4/manual.html
// - KR Manual : https://wariua.github.io/lua-manual/5.4/
// - ... : http://lua-users.org/wiki/MathLibraryTutorial
// - Dave Poo : Embedding Lua in C++ : https://www.youtube.com/playlist?list=PLLwK93hM93Z3nhfJyRRWGRXHaXgNX0Itk
//

//
// Vld
//
#if defined( DEBUG ) || defined( _DEBUG )
	#include "vld/include/vld.h"
#endif

//
// Lua lib
//
#if defined( _WIN64 )
	#pragma comment( lib, "external/lua/x64/liblua54.a" )
#else
	#pragma comment( lib, "external/lua/x86/liblua54.a" )
#endif

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_WindowUtility.h"

#include "MainMenu.h"

int main()
{
	//
	// Environment : Title
	//
	r2cm::WindowUtility::ChangeTitle( "play_lua_and_cpp" );

	//
	// Environment : Size
	//
	r2cm::WindowUtility::Resize( 1024, 960 );

	//
	// Environment : Position
	//
	r2cm::WindowUtility::Move( 0, 0 );

	//
	// Setup
	//
	r2cm::Director director;
	director.Setup( MainMenu::Create( director ) );

	//
	// Process
	//
	director.Run();

	return 0;
}

