#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) 
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Show the LoginForm modally (blocks until closed)
    ShoppingCartSystem::LoginForm^ loginForm = gcnew ShoppingCartSystem::LoginForm();
    loginForm->ShowDialog();  // Use ShowDialog instead of Application::Run

    return 0;
}
