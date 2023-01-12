#include "MainForm.h"

//===================================================
// File: MainForm.cpp
// Contents: Starting file for the program. 
// It is not recomended to do any changes in code bellow
// Author: Adrian Zarêba
//===================================================


using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	JAProjectEdgeDetection::MainForm form;
	Application::Run(% form);
}
