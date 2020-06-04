#pragma once
#include "Binja.hpp"

struct RPC
{
	bool initialize();
	bool updatePresence(BinaryNinja::BinaryView*, uint64_t);
	bool goIdle(BinaryNinja::BinaryView*, uint64_t);
	bool CheckFile(BinaryNinja::FileMetadata*, BinaryNinja::FileMetadata*);
private:
	BinaryNinja::BinaryView* view;
	uint64_t addy;
};