#include "TableMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/table_test.h"

#include "TestLuaRootMenu.h"

r2cm::MenuUp TableMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', table_test::GenerateTest::GetInstance() );
		ret->AddItem( '2', table_test::Add2GlobalTest::GetInstance() );
		ret->AddItem( '3', table_test::PushAndGetTest_1::GetInstance() );
		ret->AddItem( '4', table_test::PushAndGetTest_2::GetInstance() );
		ret->AddItem( '5', table_test::PushAndGetTest_3::GetInstance() );
		ret->AddItem( '6', table_test::PushAndGetTest_4::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'q', table_test::LuaFunction_And_GetTable::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return TestLuaRootMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestLuaRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}