#include <iostream>
#include <filesystem>

#include "globals.h"

#include "sdk/rage.hpp"
#include "golang_defines.h"
#include "GoPlugin.h"

namespace fs = std::experimental::filesystem;

RAGE_API rage::IPlugin *InitializePlugin(rage::IMultiplayer *mp)
{	
	g_multiplayer = mp;

	// Iterate all DLLs
	std::cout << "[GO] Go plugins starting up.." << std::endl;

	for (auto & p : fs::directory_iterator("gopackages"))
	{
		auto path = p.path().wstring();
		LPCWSTR name = path.c_str();

		std::cout << "[GO] Reading ";
		wprintf(name);
		std::cout << std::endl;

		GoPlugin *plugin = new GoPlugin(name);
		int err;
		if (!(err = plugin->TryInitialize(mp)))
		{
			// Success
			// Add the plugin to a list?
			std::cout << "[GO] Successfully started plugin" << std::endl;
		}
		else
		{
			delete plugin;

			std::cout << "[GO] Plugin failed to start. Error code: " << err << std::endl;
		}
	}

	return new rage::IPlugin;
}