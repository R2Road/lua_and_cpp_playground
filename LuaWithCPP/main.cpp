﻿//
// # ref
// - https://www.lua.org/manual/5.4/manual.html
// - http://lua-users.org/wiki/MathLibraryTutorial
//

#include "pch.h"

#include <conio.h>
#include <iostream>
#include <sstream>
#include <utility>
#include <Windows.h>

#ifdef _WIN32
#pragma comment( lib, "lua54/liblua54.a" )
#endif

#include "step_LuaState.h"
#include "step_DoString.h"
#include "step_GetGlobal.h"
#include "step_IsNumber.h"
#include "step_OpenLibs.h"
#include "step_DoFile.h"
#include "step_GetTable.h"
#include "step_PCall_01.h"
#include "step_PCall_02.h"
#include "step_PCall_03.h"
#include "step_PCall_04.h"

std::string MakeMenuString()
{
	std::stringstream ss;
	ss << "+ Menu" << std::endl;
	ss << "1 : step_LuaState" << std::endl;
	ss << "2 : step_DoString" << std::endl;
	ss << "3 : step_GetGlobal" << std::endl;
	ss << "4 : step_IsNumber" << std::endl;
	ss << "5 : step_OpenLibs" << std::endl;
	ss << "6 : step_DoFile" << std::endl;
	ss << "7 : step_GetTable" << std::endl;
	ss << "8 : step_PCall_01" << std::endl;
	ss << "9 : step_PCall_02" << std::endl;
	ss << "- : step_PCall_03" << std::endl;

	ss << "Q : step_PCall_04_CallCPPFunction" << std::endl;

	ss << std::endl << "Press Number" << std::endl;

	return std::string( ss.str() );
}

void ShowMenu()
{
	static std::string menu_string( std::move( MakeMenuString() ) );
	std::cout << menu_string;
}

int main()
{
	system( "mode con lines=50 cols=120" );

	int input = 0;
	while( true )
	{
		ShowMenu();

		input = _getch();
		system( "cls" );

		switch( input )
		{
		case '1':
			step::LuaState();
			break;
		case '2':
			step::DoString();
			break;
		case '3':
			step::GetGlobal();
			break;
		case '4':
			step::IsNumber();
			break;
		case '5':
			step::OpenLibs();
			break;
		case '6':
			step::DoFile();
			break;
		case '7':
			step::GetTable();
			break;
		case '8':
			step::PCall_01();
			break;
		case '9':
			step::PCall_02();
			break;
		case '-':
			step::PCall_03();
			break;
		case 'q':
			step::PCall_04_CallCPPFunction();
			break;

		case 27: // ESC
			return 0;
		}

		std::cout << std::endl << "Press Any Key" << std::endl;
		_getch();
		system( "cls" );
	}


	return 0;
}
