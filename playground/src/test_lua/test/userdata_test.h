﻿#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace userdata_test
{
	class New : public r2cm::iItem, public r2cm::SingleTon<New>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Constructor : public r2cm::iItem, public r2cm::SingleTon<Constructor>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Destructor : public r2cm::iItem, public r2cm::SingleTon<Destructor>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class OOP_1 : public r2cm::iItem, public r2cm::SingleTon<OOP_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class OOP_2 : public r2cm::iItem, public r2cm::SingleTon<OOP_2>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Field_1 : public r2cm::iItem, public r2cm::SingleTon<Field_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Field_2 : public r2cm::iItem, public r2cm::SingleTon<Field_2>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}
