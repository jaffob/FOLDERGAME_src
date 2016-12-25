// FOLDERGAME.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void loseGame(int signal)
{
	// If this is the real EXE, delete thyself.
#ifndef _DEBUG
	char szExeFileName[MAX_PATH];
	GetModuleFileName(NULL, szExeFileName, MAX_PATH);
	string exename(szExeFileName);

	ofstream bat;
	bat.open("FOLDERGAME.BAT");
	bat << ":Repeat" << endl;
	bat << "del \"" << exename << "\"" << endl;
	bat << "if exist \"" << exename << "\" goto Repeat" << endl;
	bat << "del \"%0\"" << endl;
	bat.close();

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SecureZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	char cmdline[] = "cmd.exe /C FOLDERGAME.BAT";
	CreateProcess(NULL, cmdline, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
#endif
	exit(0);
}

int main()
{
	signal(SIGINT, loseGame);
	signal(SIGTERM, loseGame);

	cout << "Enter passphrase: ";
	string input;
	cin >> input;

	// We have lost.
	if (cin.fail() || cin.eof() || md5(input + "0fv923j0k9fvdsd9nfr3").compare("178c4e1dca6e7da311aa0e382e632e82"))
	{
		loseGame(0);
	}

	// We have won.
    return 0;
}

