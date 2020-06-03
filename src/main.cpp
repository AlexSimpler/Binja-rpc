#include "stdafx.hpp"
#include "RPC.hpp"
#include "Binja.hpp"

using namespace BinaryNinja;

void entry(BinaryView* bv, uint64_t addr) {
	FileMetadata* current_file = bv->GetFile();
	LogInfo(current_file->GetFilename().c_str());
}

extern "C"
{
	BINARYNINJAPLUGIN bool CorePluginInit()
	{
		Log(InfoLog, "Loaded C++ plugin 'binja-rpc'");

		RPC* rpc = new RPC;
		rpc->initialize();
		rpc->updatePresence();
		LogInfo("Connected to discord?");

		return true;
	}
};