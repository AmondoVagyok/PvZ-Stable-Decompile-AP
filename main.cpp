#include "LawnApp.h"
#include "Resources.h"
#include "Sexy.TodLib/TodStringFile.h"
#include "GameConstants.h"

extern "C" {
#include <tinyfiledialogs.h>
}

#include <filesystem>

using namespace Sexy;

bool (*gAppCloseRequest)();				//[0x69E6A0]
bool (*gAppHasUsedCheatKeys)();			//[0x69E6A4]
SexyString (*gGetCurrentLevelName)();

//0x44E8F0
#include <shlwapi.h> 
static std::string GetExeDirectory() {
	char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH); 
	PathRemoveFileSpecA(exePath);

	return std::string(exePath);
}

bool PrepareMainPak()
{
	// Locate the PvZ main.pak file
	std::string mainPakDir;
	if (Sexy::FileExists("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Plants Vs Zombies\\main.pak"))
	{
		mainPakDir = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Plants Vs Zombies";
	}
	
	if (mainPakDir.empty())
	{
		MessageBoxA(nullptr, "Please locate the main.pak file from your legally acquired copy of Plants vs. Zombies: Game of the Year edition.", "Game Setup", MB_OK | MB_ICONINFORMATION);
		
		const char* filterPatterns[] = { "main.pak" };

		const char* main_pak_path = tinyfd_openFileDialog(
			"Find main.pak",
			NULL,
			2,
			filterPatterns,
			"main.pak",
			0
		);
		
		if (!main_pak_path)
		{
			return false;
		}
		
		mainPakDir = Sexy::GetFileDir(main_pak_path);
	}
	
	auto mainPakFileSize = std::filesystem::file_size(mainPakDir + "\\main.pak");
	if (mainPakFileSize != 45453180 && mainPakFileSize != 44925610) {
		MessageBoxA(nullptr, "The main.pak file is invalid.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	
	std::error_code ec;
	std::filesystem::copy(mainPakDir + "\\properties", "properties", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing, ec);
	if (ec)
	{
		MessageBoxA(nullptr, "Could not copy Properties directory.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	std::filesystem::copy(mainPakDir + "\\main.pak", "main.pak", ec);
	if (ec)
	{
		MessageBoxA(nullptr, "Could not copy main.pak file.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	
	return true;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	gHInstance = hInstance;

#if defined(_SHOW_OUTPUT_CONSOLE)
    AllocConsole();

    FILE* dummy;
    freopen_s(&dummy, "CONIN$", "r", stdin);
    freopen_s(&dummy, "CONOUT$", "w", stdout);
    freopen_s(&dummy, "CONOUT$", "w", stderr);

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;
    GetConsoleMode(hInput, &prevMode);

	SetConsoleMode(hInput, (prevMode & ~ENABLE_QUICK_EDIT_MODE) | ENABLE_EXTENDED_FLAGS | ENABLE_INSERT_MODE | ENABLE_PROCESSED_INPUT);
#endif

	TodStringListSetColors(gLawnStringFormats, gLawnStringFormatCount);
	gGetCurrentLevelName = LawnGetCurrentLevelName;
	gAppCloseRequest = LawnGetCloseRequest;
	gAppHasUsedCheatKeys = LawnHasUsedCheatKeys;
	
	if (!Sexy::FileExists("main.pak"))
	{
		if (!PrepareMainPak())
		{
			return 1;
		}
	}

	gLawnApp = new LawnApp();
	std::string exeDir = GetExeDirectory();
	if (Sexy::FileExists(exeDir + "\\properties\\resources.xml")) {
		gLawnApp->mChangeDirTo = exeDir;
	}
	else {
		gLawnApp->mChangeDirTo = (!Sexy::FileExists(_S("properties\\resources.xml")) &&
			Sexy::FileExists(_S("..\\properties\\resources.xml"))) ?
			_S("..") : _S(".");
	}
	
	gLawnApp->Init();
	gLawnApp->Start();
	gLawnApp->Shutdown();
	if (gLawnApp)
		delete gLawnApp;

	return 0;
};