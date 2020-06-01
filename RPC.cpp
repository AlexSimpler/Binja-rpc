#include "stdafx.hpp"
#include "RPC.hpp"
#include <discord_register.h>
#include <discord_rpc.h>

bool RPC::initialize() const {
	const char* client_id = "715921722326515814";
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize(client_id, &Handle, 1, nullptr);

	return true;
}

bool RPC::updatePresence() const
{
	int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Playing Solo";
	discordPresence.details = "Competitive";
	discordPresence.startTimestamp = eptime;
	discordPresence.endTimestamp = NULL;
	discordPresence.largeImageKey = "logo";
	discordPresence.largeImageText = "Binary ninja personal";
	Discord_UpdatePresence(&discordPresence);
	cout << "Successfully updated RPC" << endl;

	return true;
}