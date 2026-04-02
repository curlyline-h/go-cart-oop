#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class QuantityInputForm : public Form {
public:
    property String^ InputValue;

    QuantityInputForm(String^ prompt, bool numericOnly, int maxValue ) {
        maxValue = 100;
        this->Text = "Input Required";
        this->Size = Drawing::Size(300, 150);
        this->StartPosition = FormStartPosition::CenterParent;

        Label^ lbl = gcnew Label();
        lbl->Text = prompt;
        lbl->Location = Point(20, 20);
        lbl->AutoSize = true;
        this->Controls->Add(lbl);

        if (numericOnly) {
            NumericUpDown^ numericInput = gcnew NumericUpDown();
            numericInput->Minimum = 1;
            numericInput->Maximum = maxValue;
            numericInput->Value = 1;
            numericInput->Location = Point(20, 50);
            numericInput->Width = 240;
            this->Controls->Add(numericInput);
            this->Tag = numericInput;
        }
        else {
            TextBox^ textInput = gcnew TextBox();
            textInput->Location = Point(20, 50);
            textInput->Width = 240;
            this->Controls->Add(textInput);
            this->Tag = textInput;
        }

        Button^ ok = gcnew Button();
        ok->Text = "OK";
        ok->Location = Point(50, 90);
        ok->DialogResult = ::DialogResult::OK;
        this->Controls->Add(ok);

        Button^ cancel = gcnew Button();
        cancel->Text = "Cancel";
        cancel->Location = Point(150, 90);
        cancel->DialogResult = ::DialogResult::Cancel;
        this->Controls->Add(cancel);

        this->AcceptButton = ok;
        this->CancelButton = cancel;

        this->FormClosing += gcnew FormClosingEventHandler(this, &QuantityInputForm::onClosing);
    }

private:
    void onClosing(Object^ sender, FormClosingEventArgs^ e) {
        if (this->DialogResult == ::DialogResult::OK) {
            Control^ ctrl = safe_cast<Control^>(this->Tag);
            if (ctrl->GetType() == TextBox::typeid) {
                InputValue = safe_cast<TextBox^>(ctrl)->Text;
            }
            else if (ctrl->GetType() == NumericUpDown::typeid) {
                InputValue = safe_cast<NumericUpDown^>(ctrl)->Value.ToString();
            }
        }
    }
};
