#pragma once
#include "DataTable.h"
#include "Item.h"

struct DataItem
{
	Item::Types id;
	std::string textureId;
	int value = 0;
	float interval = 0.f;
};

class ItemTable : public DataTable
{
public:
	static DataItem Undefined;

protected:
	std::unordered_map<Item::Types, DataItem> table;

	std::string filePath = "tables/item_table.csv";
public:
	ItemTable() : DataTable(Types::Item) {}
	~ItemTable() = default;

	bool Load() override;
	void Release() override;

	const DataItem& Get(Item::Types id);
};

