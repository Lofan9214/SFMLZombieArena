#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

bool StringTable::Load()
{
	Release();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

	for (int i = 0;i < doc.GetRowCount();++i)
	{
		std::vector<std::string> strings = doc.GetRow<std::string>(i);
		auto it = table.find(strings[0]);

		if (it != table.end())
		{
			std::cout << "스트링 테이블 키 중복!" << std::endl;
			continue;
		}
		for (int j = 0;j < (int)Languages::Count;++j)
		{
			auto& vec = table[strings[0]];
			vec.push_back(converter.from_bytes(strings[j + 1]));
			//vec.push_back(std::wstring(strings[j+1].begin(),strings[j+1].end()));
		}
	}

	for (auto& pair : table)
	{
		std::cout << pair.first << " ";
		std::wcout.imbue(std::locale("korean"));
		for (auto& str : pair.second)
		{
			std::wcout << str << " ";
		}
		std::cout << std::endl;
	}

	return false;
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
		return L"";
	}

	return (find->second)[(int)lang];
}
