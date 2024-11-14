#include "stdafx.h"
#include "SaveLoadMgr.h"
#include "json.hpp"
using json = nlohmann::json;

void SaveLoadMgr::Save(const SaveDataVC& saveData)
{
	json j = saveData;
	std::ofstream f(savePath);

	f << j.dump(4) << std::endl;
	f.close();
}

void SaveLoadMgr::SaveV1(const SaveDataV1& saveData)
{
	json j = saveData;
	std::ofstream f(savePath);

	f << j.dump(4) << std::endl;
	f.close();
}

SaveDataVC SaveLoadMgr::Load()
{
	std::ifstream f(savePath);

	json j = json::parse(f);

	f.close();

	int version = j["version"];
	SaveData* saveData = nullptr;

	switch (version)
	{
	case 1:
	{
		SaveDataV1 v1 = j.get<SaveDataV1>();
		saveData = new SaveDataV1(v1);
		break;
	}
	default:
	{
		SaveDataVC vc = j.get<SaveDataVC>();
		saveData = new SaveDataVC(vc);
		break;
	}
	}

	while (saveData->version < Variables::currentVersion)
	{
		SaveData* oldData = saveData;
		saveData = oldData->VersionUp();
		delete oldData;
	}

	SaveDataVC* ptr = dynamic_cast<SaveDataVC*>(saveData);
	SaveDataVC ret(*ptr);
	delete saveData;

	return ret;
}
