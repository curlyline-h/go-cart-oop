#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "Authentication.h"
#include "Logger.h"
#include "MainForm.h"
#include "AdminForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

namespace ShoppingCartSystem
{
    public ref class LoginForm : public Form {
    public:
        LoginForm()
        {
            InitializeComponent();
            auth = gcnew Authentication();
            logger = gcnew Logger();
        }

    protected:
        ~LoginForm()
        {
            if (components)
                delete components;
        }

    private:
        System::ComponentModel::Container^ components;
        Authentication^ auth;
        Logger^ logger;

        Panel^ panelBackground;
        Label^ lblTitle;
        Label^ lblUsername;
        Label^ lblPassword;
        TextBox^ txtUsername;
        TextBox^ txtPassword;
        Button^ btnLogin;
        Button^ btnSignup;
        CheckBox^ checkBoxIsAdmin;

        void InitializeComponent(void)
        {
            this->Text = "Login Form";
            this->WindowState = FormWindowState::Maximized;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(240, 240, 245);
            this->BackgroundImage = Image::FromFile("background.png");
            this->BackgroundImageLayout = ImageLayout::Stretch;

            // Initialize semi-transparent panel for controls
            panelBackground = gcnew Panel();
            panelBackground->BackColor = Color::FromArgb(150, 255, 255, 255);
            panelBackground->BorderStyle = BorderStyle::None;

            // Initialize title label with no shadow effect
            lblTitle = gcnew Label();
            lblTitle->Text = "METRO SUPERMARKET";
            lblTitle->Font = gcnew Drawing::Font("Segoe UI Light", 48, FontStyle::Bold);
            lblTitle->ForeColor = Color::Black; // Changed to flat black
            lblTitle->BackColor = Color::Transparent;
            lblTitle->AutoSize = true;
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            lblTitle->Paint += gcnew PaintEventHandler(this, &LoginForm::lblTitle_Paint);
      
            // Initialize username label
            lblUsername = gcnew Label();
            lblUsername->Text = "USERNAME:";
            lblUsername->Font = gcnew Drawing::Font("Times New Roman", 20, FontStyle::Bold);
            lblUsername->ForeColor = Color::Black;
            lblUsername->BackColor = Color::Transparent;
            lblUsername->AutoSize = true;

            // Initialize username textbox with rounded corners and border
            txtUsername = gcnew TextBox();
            txtUsername->Font = gcnew Drawing::Font("Times New Roman", 16);
            txtUsername->Width = 350;
            txtUsername->Height = 80;
            txtUsername->BorderStyle = BorderStyle::None;
            txtUsername->BackColor = Color::FromArgb(255, 255, 255);
            txtUsername->Paint += gcnew PaintEventHandler(this, &LoginForm::txtBox_Paint);
            txtUsername->GotFocus += gcnew EventHandler(this, &LoginForm::txtBox_GotFocus);
            txtUsername->TabStop = true;
            txtUsername->Enabled = true;

            // Initialize password label
            lblPassword = gcnew Label();
            lblPassword->Text = "PASSWORD:";
            lblPassword->Font = gcnew Drawing::Font("Times New Roman", 20, FontStyle::Bold);
            lblPassword->ForeColor = Color::Black;
            lblPassword->BackColor = Color::Transparent;
            lblPassword->AutoSize = true;

            // Initialize password textbox with rounded corners and border
            txtPassword = gcnew TextBox();
            txtPassword->Font = gcnew Drawing::Font("Times New Roman", 16);
            txtPassword->Width = 350;
            txtPassword->Height = 80;
            txtPassword->BorderStyle = BorderStyle::None;
            txtPassword->BackColor = Color::FromArgb(255, 255, 255);
            txtPassword->UseSystemPasswordChar = true;
            txtPassword->Paint += gcnew PaintEventHandler(this, &LoginForm::txtBox_Paint);
            txtPassword->GotFocus += gcnew EventHandler(this, &LoginForm::txtBox_GotFocus);
            txtPassword->TabStop = true;
            txtPassword->Enabled = true;

            // Initialize admin checkbox
            checkBoxIsAdmin = gcnew CheckBox();
            checkBoxIsAdmin->Text = "Sign up as Admin";
            checkBoxIsAdmin->Font = gcnew Drawing::Font("Times New Roman", 16, FontStyle::Bold);
            checkBoxIsAdmin->ForeColor = Color::Black;
            checkBoxIsAdmin->BackColor = Color::Transparent;
            checkBoxIsAdmin->AutoSize = true;

            // Initialize login button with solid color and hover effect
            btnLogin = gcnew Button();
            btnLogin->Text = "Login";
            btnLogin->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
            btnLogin->Width = 150;
            btnLogin->Height = 50;
            btnLogin->FlatStyle = FlatStyle::Flat;
            btnLogin->FlatAppearance->BorderSize = 0;
            btnLogin->BackColor = Color::FromArgb(46, 139, 87); 
            btnLogin->ForeColor = Color::White;
            btnLogin->Region = gcnew System::Drawing::Region(CreateRoundedRectangle(150, 50, 15));
            btnLogin->MouseEnter += gcnew EventHandler(this, &LoginForm::btnLogin_MouseEnter);
            btnLogin->MouseLeave += gcnew EventHandler(this, &LoginForm::btnLogin_MouseLeave);
            btnLogin->Click += gcnew EventHandler(this, &LoginForm::btnLogin_Click);

            // Initialize signup button with solid color and hover effect
            btnSignup = gcnew Button();
            btnSignup->Text = "Signup";
            btnSignup->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
            btnSignup->Width = 150;
            btnSignup->Height = 50;
            btnSignup->FlatStyle = FlatStyle::Flat;
            btnSignup->FlatAppearance->BorderSize = 0;
            btnSignup->BackColor = Color::FromArgb(255, 140, 0);
            btnSignup->ForeColor = Color::White;
            btnSignup->Region = gcnew System::Drawing::Region(CreateRoundedRectangle(150, 50, 15));
            btnSignup->MouseEnter += gcnew EventHandler(this, &LoginForm::btnSignup_MouseEnter);
            btnSignup->MouseLeave += gcnew EventHandler(this, &LoginForm::btnSignup_MouseLeave);
            btnSignup->Click += gcnew EventHandler(this, &LoginForm::btnSignup_Click);

            // Add controls to the panel
            panelBackground->Controls->Add(lblTitle);
            panelBackground->Controls->Add(lblUsername);
            panelBackground->Controls->Add(txtUsername);
            panelBackground->Controls->Add(lblPassword);
            panelBackground->Controls->Add(txtPassword);
            panelBackground->Controls->Add(checkBoxIsAdmin);
            panelBackground->Controls->Add(btnLogin);
            panelBackground->Controls->Add(btnSignup);

            // Add the panel to the form
            this->Controls->Add(panelBackground);

            // Center-align controls when form loads
            this->Load += gcnew EventHandler(this, &LoginForm::LoginForm_Load);
            this->Resize += gcnew EventHandler(this, &LoginForm::LoginForm_Resize);

            // Initial positioning
            CenterControls();
        }

        // Helper method to create rounded rectangle for controls
        GraphicsPath^ CreateRoundedRectangle(int width, int height, int radius) {
            GraphicsPath^ path = gcnew GraphicsPath();
            Rectangle rect = Rectangle(0, 0, width, height);
            int diameter = radius * 2;
            path->AddArc(rect.X, rect.Y, diameter, diameter, 180, 90);
            path->AddArc(rect.Width - diameter, rect.Y, diameter, diameter, 270, 90);
            path->AddArc(rect.Width - diameter, rect.Height - diameter, diameter, diameter, 0, 90);
            path->AddArc(rect.X, rect.Height - diameter, diameter, diameter, 90, 90);
            path->CloseFigure();
            return path;
        }

        // Paint event for title (now just flat black text)
        void lblTitle_Paint(Object^ sender, PaintEventArgs^ e) {
            Label^ label = safe_cast<Label^>(sender);
            Graphics^ g = e->Graphics;
            g->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

            // Gradient brush
            LinearGradientBrush^ gradientBrush = gcnew LinearGradientBrush(
                label->ClientRectangle,
                Color::Firebrick,
                Color::Black,
                LinearGradientMode::Horizontal
            );
            g->DrawString(label->Text, label->Font, Brushes::Gray, PointF(3, 3)); // Shadow
            g->DrawString(label->Text, label->Font, Brushes::White, PointF(0, 0)); // Main Text

            g->DrawString(label->Text, label->Font, gradientBrush, PointF(0, 0));
        }


        // Paint event for textboxes to add a border
        void txtBox_Paint(Object^ sender, PaintEventArgs^ e) {
            TextBox^ txtBox = safe_cast<TextBox^>(sender);
            Graphics^ g = e->Graphics;
            Pen^ borderPen = gcnew Pen(Color::Gray, 1);
            Rectangle rect = Rectangle(1, 1, txtBox->Width - 3, txtBox->Height - 3);
            GraphicsPath^ path = CreateRoundedRectangle(txtBox->Width, txtBox->Height, 10);
            g->DrawPath(borderPen, path);
        }


        // Ensure caret visibility when textbox gains focus
        void txtBox_GotFocus(Object^ sender, EventArgs^ e) {
            TextBox^ txtBox = safe_cast<TextBox^>(sender);
            txtBox->Focus();
        }

        // Hover effects for login button
        Void btnLogin_MouseEnter(System::Object^ sender, EventArgs^ e) {
            btnLogin->BackColor = Color::FromArgb(60, 179, 113); // Lighter green
        }

        Void btnLogin_MouseLeave(System::Object^ sender, EventArgs^ e) {
            btnLogin->BackColor = Color::FromArgb(46, 139, 87); // Original green
        }
       
        // Hover effects for signup button
        Void btnSignup_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
            btnSignup->BackColor = System::Drawing::Color::FromArgb(255, 165, 0); // Lighter orange
        }
        Void btnSignup_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
            btnSignup->BackColor = System::Drawing::Color::FromArgb(255, 140, 0); // Original darker orange
        }
        void CenterControls() {
            int formWidth = this->ClientSize.Width;
            int formHeight = this->ClientSize.Height;

            int titleHeight = lblTitle->Height;
            int usernameHeight = Math::Max(lblUsername->Height, txtUsername->Height);
            int passwordHeight = Math::Max(lblPassword->Height, txtPassword->Height);
            int checkboxHeight = checkBoxIsAdmin->Height;
            int buttonHeight = btnLogin->Height;
            int spacing = 30;
            int totalHeight = titleHeight + usernameHeight + passwordHeight + checkboxHeight + buttonHeight + (spacing * 4);

            int startY = (formHeight - totalHeight) / 2;

            int panelWidth = Math::Max(500, lblTitle->Width);
            panelBackground->Size = System::Drawing::Size(panelWidth, totalHeight + 40);
            panelBackground->Location = Point((formWidth - panelBackground->Width) / 2, startY - 20);

            lblTitle->Location = Point((panelBackground->Width - lblTitle->Width) / 2, 20);

            int usernameY = 20 + titleHeight + spacing;
            int usernameRowWidth = lblUsername->Width + txtUsername->Width + 15;
            lblUsername->Location = Point((panelBackground->Width - usernameRowWidth) / 2, usernameY);
            txtUsername->Location = Point(lblUsername->Location.X + lblUsername->Width + 15, usernameY);

            int passwordY = usernameY + usernameHeight + spacing;
            int passwordRowWidth = lblPassword->Width + txtPassword->Width + 15;
            lblPassword->Location = Point((panelBackground->Width - passwordRowWidth) / 2, passwordY);
            txtPassword->Location = Point(lblPassword->Location.X + lblPassword->Width + 15, passwordY);

            int checkboxY = passwordY + passwordHeight + spacing;
            checkBoxIsAdmin->Location = Point((panelBackground->Width - checkBoxIsAdmin->Width) / 2, checkboxY);

            int buttonY = checkboxY + checkboxHeight + spacing;
            int totalButtonWidth = btnLogin->Width + btnSignup->Width + 30;
            btnLogin->Location = Point((panelBackground->Width - totalButtonWidth) / 2, buttonY);
            btnSignup->Location = Point(btnLogin->Location.X + btnLogin->Width + 30, buttonY);
        }

        void LoginForm_Load(Object^ sender, EventArgs^ e) {
            auth->loadFromFile();
            logger->logInfo("LoginForm loaded");
            CenterControls();
            txtUsername->Select();
        }

        void LoginForm_Resize(Object^ sender, EventArgs^ e) {
            CenterControls();
        }

        void btnLogin_Click(Object^ sender, EventArgs^ e) {
            String^ username = txtUsername->Text;
            String^ password = txtPassword->Text;

            try {
                if (auth->login(username, password)) {
                    if (auth->getCurrentUser()->getIsAdmin()) {
                        AdminForm^ adminForm = gcnew AdminForm(auth);
                        this->Hide();
                        adminForm->ShowDialog();
                        this->Show();
                    }
                    else {
                        MainForm^ mainForm = gcnew MainForm(auth);
                        this->Hide();
                        mainForm->ShowDialog();
                        this->Show();
                    }
                }
                else {
                    MessageBox::Show("Invalid credentials.", "Error");
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Login Error: " + ex->Message, "Error");
            }
        }

        void btnSignup_Click(Object^ sender, EventArgs^ e) {
            String^ username = txtUsername->Text;
            String^ password = txtPassword->Text;
            bool isAdmin = checkBoxIsAdmin->Checked;

            try {
                if (auth->signup(username, password, isAdmin)) {
                    MessageBox::Show("Signup successful!", "Success");
                }
                else {
                    MessageBox::Show("Username already exists!", "Error");
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Signup Error: " + ex->Message, "Error");
            }
        }
    };
}