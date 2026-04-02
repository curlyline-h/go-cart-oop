#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "Authentication.h"
#include "Inventory.h"
#include "Product.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace ShoppingCartSystem {

    public ref class AdminForm : public Form {
    public:
        AdminForm(Authentication^ auth) {
            this->auth = auth;
            inventory = gcnew Inventory();
            inventory->loadFromFile();
            InitializeComponent();
            loadProducts();
        }

    protected:
        ~AdminForm() {
            if (components) delete components;
        }

    private:
        Authentication^ auth;
        Inventory^ inventory;
        System::ComponentModel::Container^ components;

        Label^ lblTitle;
        Label^ lblName;
        Label^ lblPrice;
        Label^ lblQty;
        Label^ lblAddCategory;
        TextBox^ txtName;
        TextBox^ txtPrice;
        TextBox^ txtQty;
        ComboBox^ comboAddCategory;
        Button^ btnAdd;
        Button^ btnDelete;
        Button^ btnLogout;
        DataGridView^ grid;

        void styleButton(Button^ btn) {
            btn->FlatStyle = FlatStyle::Flat;
            btn->BackColor = Color::Teal;
            btn->ForeColor = Color::Black;
            btn->Font = gcnew Drawing::Font("Times New Roman", 16, FontStyle::Bold);
            btn->FlatAppearance->BorderSize = 2;
            btn->FlatAppearance->BorderColor = Color::Black;
        }

        void styleGrid(DataGridView^ grid) {
            grid->BackgroundColor = Color::LightGray;
            grid->Font = gcnew Drawing::Font("Times New Roman", 14);
            grid->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font("Times New Roman", 15, FontStyle::Bold);
            grid->ColumnHeadersDefaultCellStyle->BackColor = Color::DarkSlateGray;
            grid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            grid->EnableHeadersVisualStyles = false;
            grid->BorderStyle = BorderStyle::Fixed3D;
        }

        void styleInput(TextBox^ box) {
            box->Font = gcnew Drawing::Font("Times New Roman", 14);
        }

        void styleComboBox(ComboBox^ combo) {
            combo->Font = gcnew Drawing::Font("Times New Roman", 14);
        }

        void styleLabel(Label^ lbl) {
            lbl->Font = gcnew Drawing::Font("Times New Roman", 14, FontStyle::Bold);
        }

        void InitializeComponent(void) {
            components = gcnew System::ComponentModel::Container();
            lblTitle = gcnew Label();
            lblName = gcnew Label();
            lblPrice = gcnew Label();
            lblQty = gcnew Label();
            lblAddCategory = gcnew Label();
            txtName = gcnew TextBox();
            txtPrice = gcnew TextBox();
            txtQty = gcnew TextBox();
            comboAddCategory = gcnew ComboBox();
            btnAdd = gcnew Button();
            btnDelete = gcnew Button();
            btnLogout = gcnew Button();
            grid = gcnew DataGridView();

            this->Text = "Admin Inventory";
            this->WindowState = FormWindowState::Maximized;
            this->BackColor = Color::CadetBlue;

            // Title Label
            lblTitle->Text = "Inventory Manager";
            lblTitle->Font = gcnew Drawing::Font("Times New Roman", 26, FontStyle::Bold);
            lblTitle->Location = Point(80, 30);
            lblTitle->AutoSize = true;

            // Input Labels and TextBoxes
            lblName->Text = "Name:";
            lblName->Location = Point(80, 100);
            lblName->AutoSize = true;
            styleLabel(lblName);

            txtName->Location = Point(200, 95);
            txtName->Size = Drawing::Size(200, 30);
            styleInput(txtName);

            lblPrice->Text = "Price:";
            lblPrice->Location = Point(420, 100);
            lblPrice->AutoSize = true;
            styleLabel(lblPrice);

            txtPrice->Location = Point(500, 95);
            txtPrice->Size = Drawing::Size(100, 30);
            styleInput(txtPrice);

            lblQty->Text = "Quantity:";
            lblQty->Location = Point(620, 100);
            lblQty->AutoSize = true;
            styleLabel(lblQty);

            txtQty->Location = Point(720, 95);
            txtQty->Size = Drawing::Size(100, 30);
            styleInput(txtQty);

            lblAddCategory->Text = "Category:";
            lblAddCategory->Location = Point(840, 100);
            lblAddCategory->AutoSize = true;
            styleLabel(lblAddCategory);

            comboAddCategory->Location = Point(940, 95);
            comboAddCategory->Size = Drawing::Size(200, 30);
            comboAddCategory->DropDownStyle = ComboBoxStyle::DropDownList;
            styleComboBox(comboAddCategory);
            // Populate categories for adding products
            comboAddCategory->Items->AddRange(gcnew array<Object^> {
                "Groceries", "Electronics", "Clothing & Accessories", "Home & Kitchen",
                    "Health & Beauty", "Sports & Outdoors", "Toys & Games",
                    "Books & Stationery", "Automotive", "Pet Supplies"
            });
            comboAddCategory->SelectedIndex = 0;

            // Buttons
            btnAdd->Text = "Add";
            btnAdd->Location = Point(1160, 95);
            btnAdd->Size = Drawing::Size(120, 38);
            styleButton(btnAdd);
            btnAdd->Click += gcnew EventHandler(this, &AdminForm::btnAdd_Click);

            btnDelete->Text = "Delete";
            btnDelete->Location = Point(1300, 95);
            btnDelete->Size = Drawing::Size(120, 38);
            styleButton(btnDelete);
            btnDelete->Click += gcnew EventHandler(this, &AdminForm::btnDelete_Click);

            btnLogout->Text = "Logout";
            btnLogout->Location = Point(1300, 670);
            btnLogout->Size = Drawing::Size(120, 38);
            styleButton(btnLogout);
            btnLogout->Click += gcnew EventHandler(this, &AdminForm::btnLogout_Click);

            // DataGridView
            grid->Location = Point(80, 150);
            grid->Size = Drawing::Size(1340, 500);
            grid->ReadOnly = true;
            grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            grid->MultiSelect = false;
            grid->ColumnCount = 5;
            grid->Columns[0]->Name = "ID";
            grid->Columns[1]->Name = "Name";
            grid->Columns[2]->Name = "Price";
            grid->Columns[3]->Name = "Quantity";
            grid->Columns[4]->Name = "Category";
            grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            styleGrid(grid);

            // Add Controls
            this->Controls->AddRange(gcnew array<Control^> {
                lblTitle, lblName, txtName, lblPrice, txtPrice,
                    lblQty, txtQty, lblAddCategory, comboAddCategory,
                    btnAdd, btnDelete, btnLogout, grid
            });
        }

        void loadProducts() {
            grid->Rows->Clear();
            array<Product^>^ products = inventory->searchProducts("");
            for each(Product ^ p in products) {
                if (p != nullptr) {
                    grid->Rows->Add(p->getProductID(), p->getName(), p->getPrice(), p->getQuantity(), p->getCategory());
                }
            }
        }

        void btnAdd_Click(Object^ sender, EventArgs^ e) {
            try {
                String^ name = txtName->Text->Trim();
                double price = Convert::ToDouble(txtPrice->Text->Trim());
                int qty = Convert::ToInt32(txtQty->Text->Trim());
                String^ category = comboAddCategory->SelectedItem != nullptr ? comboAddCategory->SelectedItem->ToString() : "";

                if (String::IsNullOrEmpty(name) || String::IsNullOrEmpty(category)) {
                    MessageBox::Show("Name and Category cannot be empty.");
                    return;
                }

                int id = grid->RowCount + 1;
                Product^ p = gcnew Product(id, name, price, qty, category);
                inventory->addProduct(p);
                inventory->saveToFile();
                loadProducts();
                txtName->Clear();
                txtPrice->Clear();
                txtQty->Clear();
                comboAddCategory->SelectedIndex = 0;
                MessageBox::Show("Product added.");
            }
            catch (...) {
                MessageBox::Show("Invalid input. Please check your entries.");
            }
        }

        void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (grid->SelectedRows->Count > 0) {
                int id = Convert::ToInt32(grid->SelectedRows[0]->Cells[0]->Value);
                inventory->deleteProduct(id);
                inventory->saveToFile();
                loadProducts();
                MessageBox::Show("Product deleted.");
            }
            else {
                MessageBox::Show("Please select a product to delete.");
            }
        }

        void btnLogout_Click(Object^ sender, EventArgs^ e) {
            auth->logout();
            this->Close();
        }
    };
}