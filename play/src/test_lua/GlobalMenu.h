#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class GlobalMenu
{
private:
	GlobalMenu() = delete;

public:
	static const char* GetTitle() { return "Global"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};