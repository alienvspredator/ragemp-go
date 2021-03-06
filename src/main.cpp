#include <iostream>
#include <filesystem>

#include "main.hpp"
#include "GoPlugin.hpp"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			// Initialize once for each new process.
			// Return FALSE to fail DLL load.
			break;

		case DLL_PROCESS_DETACH:
			GoPlugin::GetInstance().Terminate();
			break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

RAGE_API rage::IPlugin *InitializePlugin(rage::IMultiplayer *mp)
{
	GoPlugin::GetInstance().SetMultiplayer(mp);
	GoPlugin::GetInstance().Initialize();
	return new rage::IPlugin;
}