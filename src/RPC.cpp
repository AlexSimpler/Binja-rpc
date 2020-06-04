#include "stdafx.hpp"
#include "RPC.hpp"
#include <discord_register.h>
#include <discord_rpc.h>

using namespace BinaryNinja;
namespace fs = std::experimental::filesystem;

bool RPC::initialize() {
	const char* client_id = "715921722326515814";
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));//null out the handle to avoid access denied errors
	Discord_Initialize(client_id, &Handle, 1, nullptr);//initialitze the rpc with the client id

	return true;
}

bool RPC::updatePresence(BinaryView* bv, uint64_t addr)
{
	static bool init = false;
	if (!init)
	{
		init = !init;
		view = bv;
		addy = addr;
	}

	string current_file = (bv->GetFile())->GetFilename();
	PathStripPathA((LPSTR)current_file.c_str());
	Ref<Platform> platform = bv->GetDefaultPlatform();
	string current_platform = platform->GetName();

	//create an epoch time format out of the current time (now())
	int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = current_platform.c_str();//TODO put the current_platform -> not working!
	discordPresence.state = (string("Reversing ") + current_file).c_str();
	discordPresence.startTimestamp = eptime;
	discordPresence.endTimestamp = NULL;
	discordPresence.largeImageKey = "logo";
	discordPresence.largeImageText = (string("Binary ninja v") + BinaryNinja::GetVersionString()).c_str();//conver std::string to pcstr
	Discord_UpdatePresence(&discordPresence);

	return true;
}

bool RPC::goIdle(BinaryNinja::BinaryView*, uint64_t)
{
	int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Idling...";
	discordPresence.startTimestamp = eptime;
	discordPresence.endTimestamp = NULL;
	discordPresence.largeImageKey = "logo";
	discordPresence.largeImageText = (string("Binary ninja v") + BinaryNinja::GetVersionString()).c_str();//conver std::string to pcstr
	Discord_UpdatePresence(&discordPresence);

	return true;
}

bool RPC::CheckFile(FileMetadata* file, FileMetadata* current)
{
	/*if (file != NULL)
	{
		if (file != current)
			updatePresence(view, addy);
	}
	else {
		goIdle(view, addy);
	}*/
	return true;
}