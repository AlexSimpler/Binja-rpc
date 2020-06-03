#include "stdafx.hpp"
#include "RPC.hpp"
#include <discord_register.h>
#include <discord_rpc.h>
#include "Binja.hpp"

bool RPC::initialize() const {
	const char* client_id = "715921722326515814";
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));//null out the handle to avoid access denied errors
	Discord_Initialize(client_id, &Handle, 1, nullptr);//initialitze the rpc with the client id

	return true;
}

bool RPC::updatePresence() const
{
	//create an epoch time format out of the current time (now())
	int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Reversing a binary";
	discordPresence.details = "Competitive";
	discordPresence.startTimestamp = eptime;
	discordPresence.endTimestamp = NULL;
	discordPresence.largeImageKey = "logo";
	discordPresence.largeImageText = strcat(const_cast<char*>("Binary ninja "), BinaryNinja::GetVersionString().c_str());//conver std::string to pcstr
	Discord_UpdatePresence(&discordPresence);
	cout << "Successfully updated RPC" << endl;

	return true;
}