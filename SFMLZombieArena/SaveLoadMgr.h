#pragma once

#include "SaveData.h"

class SaveLoadMgr : public Singleton<SaveLoadMgr>
{
	friend Singleton<SaveLoadMgr>;

private:
	SaveLoadMgr() = default;
	~SaveLoadMgr() = default;

	std::string savePath = "save.json";

public:
	void Save(const SaveDataVC& saveData);
	void SaveV1(const SaveDataV1& saveData);
	SaveDataVC Load();

};

