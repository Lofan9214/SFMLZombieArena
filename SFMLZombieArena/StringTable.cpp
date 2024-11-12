#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

const std::wstring StringTable::Undefined = L"Undefined Id";

bool StringTable::Load()
{
	Release();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;


	std::string strLang = "";
	switch (Variables::currentLang)
	{
	case Languages::Korean:
		strLang = "_Korean";
		break;
	case Languages::English:
		strLang = "_English";
		break;
	case Languages::Japanese:
		strLang = "_Japanese";
		break;
	}
	filePath = "tables/string_table" + strLang + ".csv";

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

	for (int i = 0;i < doc.GetRowCount();++i)
	{
		std::vector<std::string> strings = doc.GetRow<std::string>(i);
		auto it = table.find(strings[0]);

		table[strings[0]] = converter.from_bytes(strings[1]);
	}
	return true;
}

void StringTable::Release()
{
	table.clear();
}

void StringTable::OnLocalize()
{
	Load();
}

const std::wstring& StringTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}

	return find->second;
}
