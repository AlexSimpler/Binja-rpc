#include "stdafx.hpp"
#include "RPC.hpp"
#include "Binja.hpp"

using namespace BinaryNinja;
RPC* rpc = new RPC;

static FileMetadata* current_file;

bool callback(BinaryView* bv, uint64_t addr)
{
	static bool init = false;
	current_file = bv->GetFile();

	if (!init) {
		init = !init;
		rpc->updatePresence(bv, addr);
	}
	if (bv->GetFile())
	{
		if (bv->GetFile() != current_file)
			rpc->updatePresence(bv, addr);
	}
	return true;
}

extern "C" {
	BINARYNINJAPLUGIN bool CorePluginInit()
	{
		Log(InfoLog, "Loaded c++ plugin 'binja-rpc'");
		PluginCommand::RegisterForAddress("Discord Rich Presence\\Update Presence", "", nullptr, &callback);
		rpc->initialize();

		return true;
	}
}
