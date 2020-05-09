#include "MyForm.h"
#include "MyForm2.h"
#include <Windows.h>
#include <shellapi.h>

using namespace Methodicmoroz; // Название проекта


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());
	return 0;
}
