﻿#pragma once

#include "r2cm/r2cm_iItem.h"

namespace luaL_dofile_test
{
	class Basic : public r2cm::iItem
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() const override;
	};
}
