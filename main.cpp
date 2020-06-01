#include "stdafx.hpp"
#include "RPC.hpp"
#include <Binary Ninja/binaryninjacore.h>
#include <Binary Ninja/binaryninjaapi.h>

using namespace BinaryNinja;

void entry(BinaryView* bv, uint64_t addr) {
	FileMetadata* current_file = bv->GetFile();
	LogInfo(current_file->GetFilename().c_str());
}

int main()
{
	PluginCommand::RegisterForAddress("DiscordRichPresence", "A rich presence plugin for Binary Ninja", entry);

	RPC* rpc = new RPC;

	rpc->initialize();
	rpc->updatePresence();

	std::cin.get();
	return 0;
}