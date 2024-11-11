#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

const std::wstring StringTable::Undefined = L"Undefined Id";

bool StringTable::Load()
{
	Release();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	//std::string strLang = "";
	//switch (lang)
	//{
	//case Languages::Korean:
	//	strLang = "Korean";
	//	break;
	//case Languages::English:
	//	strLang = "English";
	//	break;
	//case Languages::Japanese:
	//	strLang = "Japanese";
	//	break;
	//}
	//
	//filePath = "tables/string_table_" + strLang + ".csv";


	for (int j = 0;j < (int)Languages::Count;++j)
	{
		std::string strLang = "";
		switch ((Languages)j)
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

			//if (it != table.end())
			//{
			//	std::cout << "스트링 테이블 키 중복!" << std::endl;
			//	return false;
			//}

			auto& vec = table[strings[0]];
			vec.push_back(converter.from_bytes(strings[1]));
			//vec.push_back(std::wstring(strings[j+1].begin(),strings[j+1].end()));
		}
	}
	return true;
}

void StringTable::Release()
{
	table.clear();
}

const std::wstring& StringTable::Get(const std::string& id)
{
	return Get(id, Variables::currentLang);
}

const std::wstring& StringTable::Get(const std::string& id, Languages lang)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}

	return (find->second)[(int)lang];
}
