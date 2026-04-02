#pragma once
#include "Wishlist.h"
#include "Cart.h"
#include "Logger.h"
#include "Inventory.h"

namespace ShoppingCartSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class WishlistForm : public System::Windows::Forms::Form {
    public:
        WishlistForm(Wishlist^ wishlist, Cart^ cart, Logger^ logger) {
            this->wishlist = wishlist;
            this->cart = cart;
            this->logger = logger;
            InitializeComponent();
        }

    protected:
        ~WishlistForm() {
            if (components) {
                delete components;
            }
        }

    private:
        Wishlist^ wishlist;
        Cart^ cart;
        Logger^ logger;

        System::Windows::Forms::DataGridView^ dataGridWishlist;
        System::Windows::Forms::Button^ buttonRemove;
        System::Windows::Forms::Button^ buttonMoveToCart;
        System::Windows::Forms::NumericUpDown^ numericUpDownQty;
        System::Windows::Forms::Label^ lblQuantity;
        System::Windows::Forms::Button^ buttonClose;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->dataGridWishlist = (gcnew System::Windows::Forms::DataGridView());
            this->buttonRemove = (gcnew System::Windows::Forms::Button());
            this->buttonMoveToCart = (gcnew System::Windows::Forms::Button());
            this->numericUpDownQty = (gcnew System::Windows::Forms::NumericUpDown());
            this->lblQuantity = (gcnew System::Windows::Forms::Label());
            this->buttonClose = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridWishlist))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownQty))->BeginInit();
            this->SuspendLayout();

            // Form Styling
            this->BackColor = Color::CadetBlue;

            // DataGridWishlist Styling
            this->dataGridWishlist->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridWishlist->Location = System::Drawing::Point(30, 30);
            this->dataGridWishlist->Name = L"dataGridWishlist";
            this->dataGridWishlist->Size = System::Drawing::Size(640, 260);
            this->dataGridWishlist->ReadOnly = true;
            this->dataGridWishlist->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dataGridWishlist->MultiSelect = false;
            this->dataGridWishlist->AllowUserToAddRows = false;
            this->dataGridWishlist->BackgroundColor = Color::LightGray;
            this->dataGridWishlist->Font = gcnew Drawing::Font("Times New Roman", 14);
            this->dataGridWishlist->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font("Times New Roman", 15, FontStyle::Bold);
            this->dataGridWishlist->ColumnHeadersDefaultCellStyle->BackColor = Color::DarkSlateGray;
            this->dataGridWishlist->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            this->dataGridWishlist->EnableHeadersVisualStyles = false;
            this->dataGridWishlist->BorderStyle = BorderStyle::Fixed3D;
            this->dataGridWishlist->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dataGridWishlist->TabIndex = 0;

            // ButtonRemove Styling
            this->buttonRemove->Location = System::Drawing::Point(30, 310);
            this->buttonRemove->Name = L"buttonRemove";
            this->buttonRemove->Size = System::Drawing::Size(160, 50);
            this->buttonRemove->TabIndex = 1;
            this->buttonRemove->Text = L"Remove Item";
            this->buttonRemove->FlatStyle = FlatStyle::Flat;
            this->buttonRemove->BackColor = Color::Teal;
            this->buttonRemove->ForeColor = Color::Black;
            this->buttonRemove->Font = gcnew Drawing::Font("Times New Roman", 16, FontStyle::Bold);
            this->buttonRemove->FlatAppearance->BorderSize = 2;
            this->buttonRemove->FlatAppearance->BorderColor = Color::Black;
            this->buttonRemove->Click += gcnew System::EventHandler(this, &WishlistForm::buttonRemove_Click);

            // ButtonMoveToCart Styling
            this->buttonMoveToCart->Location = System::Drawing::Point(200, 310);
            this->buttonMoveToCart->Name = L"buttonMoveToCart";
            this->buttonMoveToCart->Size = System::Drawing::Size(160, 50);
            this->buttonMoveToCart->TabIndex = 2;
            this->buttonMoveToCart->Text = L"Move to Cart";
            this->buttonMoveToCart->FlatStyle = FlatStyle::Flat;
            this->buttonMoveToCart->BackColor = Color::Teal;
            this->buttonMoveToCart->ForeColor = Color::Black;
            this->buttonMoveToCart->Font = gcnew Drawing::Font("Times New Roman", 16, FontStyle::Bold);
            this->buttonMoveToCart->FlatAppearance->BorderSize = 2;
            this->buttonMoveToCart->FlatAppearance->BorderColor = Color::Black;
            this->buttonMoveToCart->Click += gcnew System::EventHandler(this, &WishlistForm::buttonMoveToCart_Click);

            // Quantity Label
            this->lblQuantity->Location = System::Drawing::Point(370, 315);
            this->lblQuantity->Name = L"lblQuantity";
            this->lblQuantity->Text = L"Qty:";
            this->lblQuantity->Font = gcnew Drawing::Font("Times New Roman", 16, FontStyle::Bold);
            this->lblQuantity->AutoSize = true;

            // NumericUpDownQty Styling
            this->numericUpDownQty->Location = System::Drawing::Point(430, 315);
            this->numericUpDownQty->Name = L"numericUpDownQty";
            this->numericUpDownQty->Size = System::Drawing::Size(80, 40);
            this->numericUpDownQty->Minimum = 1;
            this->numericUpDownQty->Maximum = 1000;
            this->numericUpDownQty->Value = System::Decimal(1);
            this->numericUpDownQty->Font = gcnew Drawing::Font("Times New Roman", 14);
            this->numericUpDownQty->TabIndex = 3;

            // ButtonClose Styling
            this->buttonClose->Location = System::Drawing::Point(520, 310);
            this->buttonClose->Name = L"buttonClose";
            this->buttonClose->Size = System::Drawing::Size(160, 50);
            this->buttonClose->TabIndex = 4;
            this->buttonClose->Text = L"Close Wishlist";
            this->buttonClose->TextAlign = ContentAlignment::MiddleCenter; // Center the text
            this->buttonClose->FlatStyle = FlatStyle::Flat;
            this->buttonClose->BackColor = Color::Teal;
            this->buttonClose->ForeColor = Color::Black;
            this->buttonClose->Font = gcnew Drawing::Font("Times New Roman", 16, FontStyle::Bold);
            this->buttonClose->FlatAppearance->BorderSize = 2;
            this->buttonClose->FlatAppearance->BorderColor = Color::Black;
            this->buttonClose->Click += gcnew System::EventHandler(this, &WishlistForm::buttonClose_Click);

            // Form Properties
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(700, 400);
            this->Controls->Add(this->buttonClose);
            this->Controls->Add(this->lblQuantity);
            this->Controls->Add(this->numericUpDownQty);
            this->Controls->Add(this->buttonMoveToCart);
            this->Controls->Add(this->buttonRemove);
            this->Controls->Add(this->dataGridWishlist);
            this->Name = L"WishlistForm";
            this->Text = L"Manage Wishlist";
            this->Load += gcnew System::EventHandler(this, &WishlistForm::WishlistForm_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridWishlist))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownQty))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

        void RefreshWishlistGrid() {
            dataGridWishlist->Rows->Clear();
            for each (Product ^ p in wishlist->getItems()) {
                if (p != nullptr) {
                    dataGridWishlist->Rows->Add(p->getProductID(), p->getName(), p->getPrice(), p->getQuantity(), p->getCategory());
                }
            }
        }

        System::Void WishlistForm_Load(System::Object^ sender, System::EventArgs^ e) {
            dataGridWishlist->Columns->Add("ID", "Product ID");
            dataGridWishlist->Columns->Add("Name", "Name");
            dataGridWishlist->Columns->Add("Price", "Price");
            dataGridWishlist->Columns->Add("Quantity", "Quantity");
            dataGridWishlist->Columns->Add("Category", "Category");
            RefreshWishlistGrid();
        }

        System::Void buttonRemove_Click(System::Object^ sender, System::EventArgs^ e) {
            if (dataGridWishlist->SelectedRows->Count > 0) {
                int id = Convert::ToInt32(dataGridWishlist->SelectedRows[0]->Cells[0]->Value);
                wishlist->removeFromWishlist(id);
                wishlist->saveToFile();
                RefreshWishlistGrid();
                logger->logInfo("Removed product ID " + id + " from wishlist");
            }
        }

        System::Void buttonMoveToCart_Click(System::Object^ sender, System::EventArgs^ e) {
            if (dataGridWishlist->SelectedRows->Count > 0) {
                int id = Convert::ToInt32(dataGridWishlist->SelectedRows[0]->Cells[0]->Value);
                Product^ p = nullptr;

                for each (Product ^ item in wishlist->getItems()) {
                    if (item != nullptr && item->getProductID() == id) {
                        p = item;
                        break;
                    }
                }

                if (p != nullptr) {
                    int qty = Convert::ToInt32(numericUpDownQty->Value);
                    if (p->getQuantity() >= qty) {
                        Product^ cloned = gcnew Product(p->getProductID(), p->getName(), p->getPrice(), qty, p->getCategory());
                        cart->addItem(cloned, qty);

                        // Update Inventory
                        Inventory^ inventory = gcnew Inventory();
                        inventory->loadFromFile();
                        inventory->updateQuantity(p->getProductID(), -qty);
                        inventory->saveToFile();

                        wishlist->removeFromWishlist(id);
                        wishlist->saveToFile();
                        RefreshWishlistGrid();
                        logger->logInfo("Moved product ID " + id + " to cart");
                    }
                    else {
                        MessageBox::Show("Insufficient stock!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
            }
        }

        System::Void buttonClose_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}