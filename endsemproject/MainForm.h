#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#using <Microsoft.VisualBasic.dll>
#include "OrderHistory.h"
#include "Order.h"
#include "Authentication.h"
#include "Logger.h"
#include "Inventory.h"
#include "Cart.h"
#include "Wishlist.h"
#include "WishlistForm.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace Microsoft::VisualBasic;

namespace ShoppingCartSystem {

    public ref class MainForm : public Form {
    public:
        MainForm(Authentication^ auth) {
            this->auth = auth;
            orderHistory = gcnew OrderHistory();
            orderHistory->loadFromFile();
            logger = gcnew Logger();
            cart = gcnew Cart();
            int userId = auth->getCurrentUser()->getUserID();
            wishlist = gcnew Wishlist(userId);
            wishlist->loadFromFile();

            InitializeComponent();
        }

    protected:
        ~MainForm() {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;
        Authentication^ auth;
        Logger^ logger;
        Cart^ cart;
        Wishlist^ wishlist;
        OrderHistory^ orderHistory;
        Label^ lblWelcome;
        Button^ btnLogout;
        Button^ btnViewProducts;
        Button^ btnCategories;
        ComboBox^ comboCategories;
        NumericUpDown^ quantitySelector;
        Button^ btnAddToCart;
        Button^ btnViewCart;
        Button^ btnRemoveFromCart;
        Button^ btnCheckout;
        Button^ btnApplyDiscount;
        Button^ btnOrderHistory;
        DataGridView^ productGrid;
        DataGridView^ cartGrid;
        TextBox^ txtSearch;
        Button^ btnSearch;

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

        void InitializeComponent(void) {
            components = gcnew System::ComponentModel::Container();
            lblWelcome = gcnew Label();
            btnLogout = gcnew Button();
            btnViewProducts = gcnew Button();
            btnCategories = gcnew Button();
            comboCategories = gcnew ComboBox();
            quantitySelector = gcnew NumericUpDown();
            btnAddToCart = gcnew Button();
            btnViewCart = gcnew Button();
            btnRemoveFromCart = gcnew Button();
            btnCheckout = gcnew Button();
            btnApplyDiscount = gcnew Button();
            btnOrderHistory = gcnew Button();
            productGrid = gcnew DataGridView();
            cartGrid = gcnew DataGridView();
            txtSearch = gcnew TextBox();
            btnSearch = gcnew Button();
            btnViewCart->Click += gcnew EventHandler(this, &MainForm::btnViewCart_Click);
            Button^ btnAddToWishlist = gcnew Button();
            btnAddToWishlist->Text = "Add to Wishlist";
            btnAddToWishlist->Location = Point(695, 480);
            styleButton(btnAddToWishlist);
            btnAddToWishlist->Click += gcnew EventHandler(this, &MainForm::btnAddToWishlist_Click);
            Controls->Add(btnAddToWishlist);
            btnAddToWishlist->Height = 70;
            btnAddToWishlist->Width = 150;
            Button^ btnWishlist = gcnew Button();
            btnWishlist->Text = "Wishlist";
            btnWishlist->Location = Point(695, 560);
            btnWishlist->Height = 50;
            btnWishlist->Width = 150;
            styleButton(btnWishlist);
            btnWishlist->Click += gcnew EventHandler(this, &MainForm::btnWishlist_Click);
            Controls->Add(btnWishlist);
            this->Text = "Shopping Cart System - Main";
            this->WindowState = FormWindowState::Maximized;
            this->BackColor = Color::CadetBlue;

            // Welcome Label
            String^ username = auth && auth->getCurrentUser() ? auth->getCurrentUser()->getUsername() : "Guest";
            lblWelcome->Text = "Welcome, " + username + "!";
            lblWelcome->Font = gcnew Drawing::Font("Times New Roman", 26, FontStyle::Bold);
            lblWelcome->Location = Point(80, 30);
            lblWelcome->AutoSize = true;

            // Logout Button
            btnLogout->Text = "Logout";
            btnLogout->Location = Point(1340, 30);
            btnLogout->Width = 120;
            btnLogout->Height = 40;
            styleButton(btnLogout);
            btnLogout->Click += gcnew EventHandler(this, &MainForm::btnLogout_Click);

            // Search Bar
            txtSearch->Name = "txtSearchBox";
            txtSearch->Location = Point(80, 80);
            txtSearch->Width = 470;
            txtSearch->Font = gcnew Drawing::Font("Segoe UI", 12);

            // Search Button
            btnSearch->Text = "Search";
            btnSearch->Location = Point(560, 75);
            btnSearch->Width = 120;
            btnSearch->Height = 38;
            styleButton(btnSearch);
            btnSearch->Click += gcnew EventHandler(this, &MainForm::btnSearchProduct_Click);

            // Product Grid (Left Side)
            productGrid->Location = Point(80, 130);
            productGrid->Size = Drawing::Size(600, 500);
            productGrid->ReadOnly = true;
            productGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            productGrid->MultiSelect = false;
            productGrid->AllowUserToAddRows = false;
            productGrid->RowTemplate->Height = 100; // Increase row height to accommodate images
            DataGridViewImageColumn^ imageColumn = gcnew DataGridViewImageColumn();
            imageColumn->HeaderText = "Image";
            imageColumn->Name = "Image";
            imageColumn->ImageLayout = DataGridViewImageCellLayout::Zoom; // Scale image to fit cell
            imageColumn->Width = 100;
            productGrid->Columns->Add(imageColumn);
            productGrid->Columns->Add("ID", "ID");
            productGrid->Columns->Add("Name", "Name");
            productGrid->Columns->Add("Price", "Price");
            productGrid->Columns->Add("Quantity", "Quantity");
            productGrid->Columns->Add("Category", "Category");
            productGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            styleGrid(productGrid);
            productGrid->CellClick += gcnew DataGridViewCellEventHandler(this, &MainForm::productGrid_CellClick);

            // Cart Grid (Right Side)
            cartGrid->Location = Point(860, 130);
            cartGrid->Size = Drawing::Size(600, 500);
            cartGrid->ReadOnly = true;
            cartGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            cartGrid->MultiSelect = false;
            cartGrid->ColumnCount = 3;
            cartGrid->Columns[0]->Name = "ID";
            cartGrid->Columns[1]->Name = "Name";
            cartGrid->Columns[2]->Name = "Quantity";
            cartGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            styleGrid(cartGrid);

            // Buttons for Product Grid
            btnViewProducts->Text = "View Products";
            btnViewProducts->Location = Point(80, 650);
            btnViewProducts->Height = 38;
            btnViewProducts->Width = 180;
            styleButton(btnViewProducts);
            btnViewProducts->Click += gcnew EventHandler(this, &MainForm::btnViewProducts_Click);

            btnCategories->Text = "Categories";
            btnCategories->Location = Point(280, 650);
            btnCategories->Height = 38;
            btnCategories->Width = 150;
            styleButton(btnCategories);
            btnCategories->Click += gcnew EventHandler(this, &MainForm::btnCategories_Click);

            comboCategories->Location = Point(440, 650);
            comboCategories->Width = 240;
            comboCategories->Height = 400;
            comboCategories->DropDownStyle = ComboBoxStyle::DropDownList;
            comboCategories->Font = gcnew Drawing::Font("Times New Roman", 14);

            // Add Quantity label
            Label^ quantityLabel = gcnew Label();
            quantityLabel->Text = "Quantity:";
            quantityLabel->Location = Point(80, 700);
            quantityLabel->Font = gcnew Drawing::Font("Times New Roman", 16, FontStyle::Bold);
            quantityLabel->Width = 120;
            quantityLabel->Height = 40;
            this->Controls->Add(quantityLabel);

            quantitySelector->Location = Point(240, 700);
            quantitySelector->Font = gcnew Drawing::Font("Times New Roman", 14);
            quantitySelector->Minimum = 1;
            quantitySelector->Maximum = 100;
            quantitySelector->Value = 1;
            quantitySelector->Width = 100;
            quantitySelector->Height = 90;

            btnAddToCart->Text = "Add to Cart";
            btnAddToCart->Location = Point(530, 700);
            btnAddToCart->Width = 150;
            btnAddToCart->Height = 38;
            styleButton(btnAddToCart);
            btnAddToCart->Click += gcnew EventHandler(this, &MainForm::btnAddToCart_Click);

            // Buttons for Cart Grid
            btnViewCart->Text = "View Cart";
            btnViewCart->Location = Point(860, 650);
            btnViewCart->Width = 150;
            btnViewCart->Height = 38;
            styleButton(btnViewCart);
            btnViewCart->Click += gcnew EventHandler(this, &MainForm::btnViewCart_Click);

            btnRemoveFromCart->Text = "Remove";
            btnRemoveFromCart->Location = Point(1090, 650);
            btnRemoveFromCart->Width = 150;
            btnRemoveFromCart->Height = 38;
            styleButton(btnRemoveFromCart);
            btnRemoveFromCart->Click += gcnew EventHandler(this, &MainForm::btnRemoveFromCart_Click);

            btnCheckout->Text = "Checkout";
            btnCheckout->Location = Point(1310, 650);
            btnCheckout->Width = 150;
            btnCheckout->Height = 38;
            styleButton(btnCheckout);
            btnCheckout->Click += gcnew EventHandler(this, &MainForm::btnCheckout_Click);

            btnApplyDiscount->Text = "Apply Discount";
            btnApplyDiscount->Location = Point(860, 700);
            btnApplyDiscount->Width = 280;
            btnApplyDiscount->Height = 40;
            styleButton(btnApplyDiscount);
            btnApplyDiscount->Click += gcnew EventHandler(this, &MainForm::btnApplyDiscount_Click);

            btnOrderHistory->Text = "Order History";
            btnOrderHistory->Location = Point(1180, 700);
            btnOrderHistory->Width = 280;
            btnOrderHistory->Height = 40;
            styleButton(btnOrderHistory);
            btnOrderHistory->Click += gcnew EventHandler(this, &MainForm::btnOrderHistory_Click);

            // Add Controls
            Controls->AddRange(gcnew array<Control^> {
                lblWelcome, btnLogout, txtSearch, btnSearch,
                    productGrid, cartGrid, btnViewProducts, btnCategories, comboCategories,
                    quantitySelector, btnAddToCart, btnViewCart, btnRemoveFromCart,
                    btnCheckout, btnApplyDiscount, btnOrderHistory
            });

            this->Load += gcnew EventHandler(this, &MainForm::MainForm_Load);
        }

        void MainForm_Load(Object^ sender, EventArgs^ e) {
            logger->logInfo("MainForm loaded");
        }

        void btnLogout_Click(Object^ sender, EventArgs^ e) {
            auth->logout();
            this->Close();
        }

        void btnViewProducts_Click(Object^ sender, EventArgs^ e) {
            Inventory^ inventory = gcnew Inventory();
            inventory->loadFromFile();
            auto products = inventory->searchProducts("");
            productGrid->Rows->Clear();
            for each(Product ^ p in products) {
                if (p != nullptr) {
                    Image^ productImage;
                    try {
                        productImage = Image::FromFile(p->getImagePath());
                    }
                    catch (Exception^) {
                        productImage = nullptr; // Handle missing/invalid images
                    }
                    productGrid->Rows->Add(productImage, p->getProductID(), p->getName(),
                        p->getPrice().ToString("F2"), p->getQuantity(), p->getCategory());
                }
            }
        }

        void btnCategories_Click(Object^ sender, EventArgs^ e) {
            comboCategories->Items->Clear();
            comboCategories->Items->AddRange(gcnew array<Object^> {
                "All", "Groceries", "Electronics", "Clothing & Accessories", "Home & Kitchen",
                    "Health & Beauty", "Sports & Outdoors", "Toys & Games",
                    "Books & Stationery", "Automotive", "Pet Supplies","Tobacco & Smoking Products"
            });
            comboCategories->SelectedIndex = 0;
            comboCategories->SelectedIndexChanged += gcnew EventHandler(this, &MainForm::comboCategories_SelectedIndexChanged);
        }

        void comboCategories_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
            String^ category = comboCategories->SelectedItem->ToString();
            Inventory^ inventory = gcnew Inventory();
            inventory->loadFromFile();
            array<Product^>^ products;
            if (category == "All")
                products = inventory->searchProducts("");
            else
                products = inventory->filterByCategory(category);
            productGrid->Rows->Clear();
            for each(Product ^ p in products) {
                if (p != nullptr) {
                    Image^ productImage;
                    try {
                        productImage = Image::FromFile(p->getImagePath());
                    }
                    catch (Exception^) {
                        productImage = nullptr; // Handle missing/invalid images
                    }
                    productGrid->Rows->Add(productImage, p->getProductID(), p->getName(),
                        p->getPrice().ToString("F2"), p->getQuantity(), p->getCategory());
                }
            }
        }

        void btnAddToCart_Click(Object^ sender, EventArgs^ e) {
            if (productGrid->SelectedRows->Count > 0) {
                auto row = productGrid->SelectedRows[0];
                int id = Convert::ToInt32(row->Cells[1]->Value); // Index 1 because 0 is the image
                String^ name = row->Cells[2]->Value->ToString();
                double price = Convert::ToDouble(row->Cells[3]->Value);
                int qtyInStock = Convert::ToInt32(row->Cells[4]->Value);
                int qtyToAdd = Decimal::ToInt32(quantitySelector->Value);
                String^ cat = row->Cells[5]->Value->ToString();

                if (qtyToAdd > qtyInStock) {
                    MessageBox::Show("Not enough stock available.");
                    return;
                }

                Product^ p = gcnew Product(id, name, price, qtyInStock, cat);
                cart->addItem(p, qtyToAdd);

                Inventory^ inventory = gcnew Inventory();
                inventory->loadFromFile();
                inventory->updateQuantity(id, -qtyToAdd);
                inventory->saveToFile();

                btnViewProducts_Click(sender, e);
                MessageBox::Show("Added to cart: " + name + " (Qty: " + qtyToAdd + ")");
            }
            else {
                MessageBox::Show("Please select a product to add.");
            }
        }

        void productGrid_CellClick(Object^ sender, DataGridViewCellEventArgs^ e) {
            if (e->RowIndex >= 0 && e->ColumnIndex == 0) { // Click on the image column
                productGrid->Rows[e->RowIndex]->Selected = true; // Select the row
                btnAddToCart_Click(sender, gcnew EventArgs()); // Trigger the Add to Cart action
            }
        }

        void btnViewCart_Click(Object^ sender, EventArgs^ e) {
            cartGrid->Rows->Clear();
            for each(CartItem ^ item in cart->getItems()) {
                Product^ p = item->getProduct();
                cartGrid->Rows->Add(p->getProductID(), p->getName(), item->getQuantity());
            }
        }

        void btnRemoveFromCart_Click(Object^ sender, EventArgs^ e) {
            if (cartGrid->SelectedRows->Count > 0) {
                int selectedID = Convert::ToInt32(cartGrid->SelectedRows[0]->Cells[0]->Value);
                String^ itemName = cartGrid->SelectedRows[0]->Cells[1]->Value->ToString();
                int currentQty = Convert::ToInt32(cartGrid->SelectedRows[0]->Cells[2]->Value);

                String^ input = Interaction::InputBox("Enter quantity to remove from " + itemName +
                    " (Max: " + currentQty + ")", "Remove Quantity", "1");

                try {
                    int qtyToRemove = Convert::ToInt32(input);
                    if (qtyToRemove <= 0 || qtyToRemove > currentQty) {
                        MessageBox::Show("Invalid quantity entered.", "Error");
                        return;
                    }

                    Inventory^ inventory = gcnew Inventory();
                    inventory->loadFromFile();
                    inventory->updateQuantity(selectedID, qtyToRemove);
                    inventory->saveToFile();

                    cart->updateQuantity(selectedID, qtyToRemove);
                    btnViewCart_Click(sender, e);
                    btnViewProducts_Click(sender, e);

                    MessageBox::Show("Removed " + qtyToRemove + " from " + itemName, "Success");
                }
                catch (...) {
                    MessageBox::Show("Please enter a valid number.");
                }
            }
            else {
                MessageBox::Show("Please select an item to remove.");
            }
        }

        void btnAddToWishlist_Click(Object^ sender, EventArgs^ e) {
            if (productGrid->SelectedRows->Count > 0) {
                auto row = productGrid->SelectedRows[0];
                int id = Convert::ToInt32(row->Cells[1]->Value);
                String^ name = row->Cells[2]->Value->ToString();
                double price = Convert::ToDouble(row->Cells[3]->Value);
                int qty = Convert::ToInt32(row->Cells[4]->Value);
                String^ category = row->Cells[5]->Value->ToString();

                Product^ product = gcnew Product(id, name, price, qty, category);
                wishlist->addToWishlist(product);
                wishlist->saveToFile();
                MessageBox::Show("Added to Wishlist: " + name);
                logger->logInfo("Added to Wishlist: " + name);
            }
            else {
                MessageBox::Show("Please select a product first.");
            }
        }

        void btnWishlist_Click(Object^ sender, EventArgs^ e) {
            WishlistForm^ wishlistForm = gcnew WishlistForm(wishlist, cart, logger);
            wishlistForm->ShowDialog();

            Inventory^ inventory = gcnew Inventory();
            inventory->loadFromFile();
            array<Product^>^ products = inventory->searchProducts("");
            productGrid->Rows->Clear();
            for each(Product ^ p in products) {
                if (p != nullptr) {
                    Image^ productImage;
                    try {
                        productImage = Image::FromFile(p->getImagePath());
                    }
                    catch (Exception^) {
                        productImage = nullptr;
                    }
                    productGrid->Rows->Add(productImage, p->getProductID(), p->getName(),
                        p->getPrice().ToString("F2"), p->getQuantity(), p->getCategory());
                }
            }
        }

        void btnApplyDiscount_Click(Object^ sender, EventArgs^ e) {
            String^ code = Interaction::InputBox("Enter discount code:", "Apply Discount", "");
            if (cart->applyDiscount(code)) {
                MessageBox::Show("Discount applied! You'll see it at checkout.", "Success");
            }
            else {
                MessageBox::Show("Invalid code. Try again.", "Error");
            }
        }

        void btnCheckout_Click(Object^ sender, EventArgs^ e) {
            auto items = cart->getItems();
            if (items->Length == 0) {
                MessageBox::Show("Cart is empty!", "Checkout", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            String^ receipt = "----- Checkout Summary -----\n\n";
            for each(CartItem ^ item in items) {
                Product^ p = item->getProduct();
                receipt += p->getName() + " x" + item->getQuantity() +
                    " = $" + item->getSubtotal().ToString("F2") + "\n";
            }

            double total = cart->calculateTotal();
            receipt += "\n-----------------------------\n";
            receipt += "Total: $" + total.ToString("F2") + "\n";
            receipt += "\nThank you for your purchase!";

            MessageBox::Show(receipt, "Order Placed!", MessageBoxButtons::OK, MessageBoxIcon::Information);
            int userID = auth->getCurrentUser()->getUserID();
            int orderID = orderHistory->getNextOrderID();
            Order^ newOrder = gcnew Order(orderID, userID, items, total);
            orderHistory->addOrder(newOrder);
            orderHistory->saveToFile();

            cart->clearCart();
            cartGrid->Rows->Clear();
        }

        void btnOrderHistory_Click(Object^ sender, EventArgs^ e) {
            if (auth->getCurrentUser() == nullptr) {
                MessageBox::Show("User not logged in.");
                return;
            }

            int userID = auth->getCurrentUser()->getUserID();
            array<Order^>^ orders = orderHistory->getOrders(userID);

            if (orders->Length == 0) {
                MessageBox::Show("No past orders found.");
                return;
            }

            String^ history = "----- Your Orders -----\n\n";
            for each(Order ^ order in orders) {
                if (order == nullptr) continue;
                history += "Order ID: " + order->getOrderID() +
                    "\nDate: " + order->getOrderDate() +
                    "\nTotal: $" + order->getTotal().ToString("F2") + "\nItems:\n";
                for each(CartItem ^ item in order->getItems()) {
                    Product^ p = item->getProduct();
                    history += " - " + p->getName() + " x" + item->getQuantity() +
                        " ($" + item->getSubtotal().ToString("F2") + ")\n";
                }
                history += "-----------------------------\n\n";
            }

            MessageBox::Show(history, "Order History", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnSearchProduct_Click(Object^ sender, EventArgs^ e) {
            String^ keyword = txtSearch->Text->Trim();
            if (String::IsNullOrEmpty(keyword)) {
                MessageBox::Show("Please enter a product name.");
                return;
            }

            Inventory^ inventory = gcnew Inventory();
            inventory->loadFromFile();
            array<Product^>^ products = inventory->searchProducts(keyword);

            productGrid->Rows->Clear();
            for each(Product ^ p in products) {
                if (p != nullptr) {
                    Image^ productImage;
                    try {
                        productImage = Image::FromFile(p->getImagePath());
                    }
                    catch (Exception^) {
                        productImage = nullptr;
                    }
                    productGrid->Rows->Add(productImage, p->getProductID(), p->getName(),
                        p->getPrice().ToString("F2"), p->getQuantity(), p->getCategory());
                }
            }

            if (products->Length == 0)
                MessageBox::Show("No products found with the name: " + keyword);
        }
    };
}