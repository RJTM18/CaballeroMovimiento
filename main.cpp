#include "pch.h"
#include "FrmJuego.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MobimientoSprites::FrmJuego());
	return 0;
}