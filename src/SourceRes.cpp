#include "SourceRes.h"

// The plugin is a static singleton that is exported as an interface.
SequencePlugin g_SequencePlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(SequencePlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_SequencePlugin);

SequencePlugin::SequencePlugin(){}
SequencePlugin::~SequencePlugin(){}

bool SequencePlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	ConnectTier1Libraries(&interfaceFactory, 1);

	engine = (IVEngineClient*)interfaceFactory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);

	if (!engine)
	{
		Warning("[SourceRes] Unable to connect to the game engine, probably due to unupported engine interface version.\n");
		return false;
	}

	ConVar_Register(0);
	return true;
}

void SequencePlugin::Unload(void)
{
	ConVar_Unregister();
	DisconnectTier1Libraries();
}

const char *SequencePlugin::GetPluginDescription(void)
{
	return PLUGIN_DESC;
}

// Unused.
void SequencePlugin::Pause(void){}
void SequencePlugin::UnPause(void){}
void SequencePlugin::LevelInit(char const *pMapName){}
void SequencePlugin::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax){}
void SequencePlugin::GameFrame(bool simulating){}
void SequencePlugin::LevelShutdown(void){}
void SequencePlugin::ClientActive(edict_t *pEntity){}
void SequencePlugin::ClientDisconnect(edict_t *pEntity){}
void SequencePlugin::ClientPutInServer(edict_t *pEntity, char const *playername){}
void SequencePlugin::SetCommandClient(int index){}
void SequencePlugin::ClientSettingsChanged(edict_t *pEdict){}
PLUGIN_RESULT SequencePlugin::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen){ return PLUGIN_CONTINUE; }
PLUGIN_RESULT SequencePlugin::ClientCommand(edict_t *pEntity, const CCommand &args){ return PLUGIN_CONTINUE; }
PLUGIN_RESULT SequencePlugin::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID){ return PLUGIN_CONTINUE; }
void SequencePlugin::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue){}
void SequencePlugin::OnEdictAllocated(edict_t *edict){}
void SequencePlugin::OnEdictFreed(const edict_t *edict){}

CON_COMMAND(sr_list, "List all currently available resolutions.")
{
	// Get video modes.
	vmode_s *modeList;
	int count;
	engine->GetVideoModes(count, modeList);

	DevMsg("Reading video mode array from offset: %#x\n", modeList);

	for (auto i = 0; i < count; i++)
	{
		vmode_s mode = modeList[i];
		Msg("%ix%i\n", mode.width, mode.height);
	}
}
