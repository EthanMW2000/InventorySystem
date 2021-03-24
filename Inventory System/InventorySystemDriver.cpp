/*
@author Ethan Wells
@filename InvetorySystemDriver.cpp

File runs the inventory system and allows the user to:
Search for a product
Update a product's details
Create a new product
Delete a product
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include<algorithm>
#include<chrono>
#include "Product.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::setw;

void LoadProductList(vector<Product>& products, ifstream& systemInventory);
void OutputProductList(vector<Product> products);
void SearchProductList(vector<Product> products);
void PrintProduct(vector<Product> products, int index);
void PrintProductList(vector<Product> products);
bool ProductExists(vector<Product> products, string ID);
void UpdateProduct(vector<Product>& products);
void UpdateProductName(vector<Product>& products, int productPosition);
void UpdateProductID(vector<Product>& products, int productPosition);
void UpdateProductQty(vector<Product>& products, int productPosition);
void UpdateProductPrice(vector<Product>& products, int productPosition);
void UpdateProductType(vector<Product>& products, int productPosition);
void NewProduct(vector<Product>& products);
void DeleteProduct(vector<Product>& products);

int main()
{
	int menuNavigation;
	bool usingMenu = true;

	vector<Product> products;
	ifstream systemInventory;

	systemInventory.open("inventory.txt");
	if (systemInventory.is_open())
		LoadProductList(products, systemInventory);
	else
		cout << "Unable to open file." << endl;

	OutputProductList(products);

	while (usingMenu)
	{
		LoadProductList(products, systemInventory);

		cout << "(1) Search Product" << endl
			<< "(2) Update Product Details" << endl
			<< "(3) Create a New Product" << endl
			<< "(4) Delete Product" << endl
			<< "(5) Exit Program" << endl << endl;

		cout << "Make a Selection: ";

		cin >> menuNavigation;
		cout << endl;

		if (menuNavigation == 1)
		{
			SearchProductList(products);
		}
		else if (menuNavigation == 2)
		{
			UpdateProduct(products);
		}
		else if (menuNavigation == 3)
		{
			NewProduct(products);
		}
		else if (menuNavigation == 4)
		{
			DeleteProduct(products);
		}
		else if (menuNavigation == 5)
		{
			return 0;
		}
		else
		{
			cout << "Invalid selection try again." << endl << endl;
		}
	}

	return 0;
}

//Fills a vector to hold product list from inventory.txt
void LoadProductList(vector<Product>& products, ifstream &systemInventory)
{
	string name;
	string ID;
	int qty;
	double price;
	string priceType;

	while (systemInventory >> name >> ID >> qty >> price >> priceType)
	{
		products.emplace_back(name, ID, qty, price, priceType);
	}

	systemInventory.close();

	std::sort(products.begin(), products.end());
}

//Outputs product list to inventory.txt
void OutputProductList(vector<Product> products)
{
	ofstream updateSystemInvetory;
	updateSystemInvetory.open("inventory.txt");

	if (updateSystemInvetory.is_open())
	{
		for (int i = 0; i < products.size(); i++)
		{
			updateSystemInvetory << products[i].GetItemName() << " "
				<< products[i].GetItemID() << " "
				<< products[i].GetItemQty() << " "
				<< products[i].GetItemPrice() << " "
				<< products[i].GetItemType() << " " << endl;
		}
	}
	else
		cout << "Unable to open file." << endl;

	updateSystemInvetory.close();

}

//Search loop for menu
void SearchProductList(vector<Product> products)
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	string ID;
	string choice;

	bool correctChoice = false;

	cout << "Enter a product name or id: ";
	cin >> ID;

	auto time1 = std::chrono::high_resolution_clock::now(); //used to time search length

	if (ProductExists(products, ID))
	{
		auto time2 = std::chrono::high_resolution_clock::now(); //used to time search length
		duration<double, std::milli> finalTime = time2 - time1; //determine search length time
		cout << "This search took " << finalTime.count() << " ms" << endl; //output search length time


		cout << "(1) Search Again" << endl
			<< "(2) Back" << endl << endl;

		cout << "Make a selection: ";

		while (correctChoice == false)
		{
			cin >> choice;
			cout << endl;

			if (choice == "1")
			{
				SearchProductList(products);
				correctChoice = true;
			}
			else if (choice == "2")
			{
				correctChoice = true;
				return;
			}
			else
			{
				cout << "Invalid selection try again." << endl << endl;
				cout << "(1) Search Again" << endl
					<< "(2) Back" << endl << endl;
				cout << "Make a selection: ";
			}
		}
	}
	else
	{
		cout << "This product ID does not exist. " << endl;

		cout << "(1) Search Again" << endl
			<< "(2) Back" << endl << endl;

		cout << "Make a selection: ";
		
		while (correctChoice == false)
		{
			cin >> choice;
			cout << endl;

			if (choice == "1")
			{
				SearchProductList(products);
				correctChoice = true;
			}
			else if (choice == "2")
			{
				correctChoice = true;
				return;
			}
			else
			{
				cout << "Invalid selection try again." << endl << endl;
				cout << "(1) Search Again" << endl
					<< "(2) Back" << endl << endl;
				cout << "Make a selection: ";
			}
		}
	}
}

//Outputs product details
void PrintProduct(vector<Product> products, int productPosition)
{
	cout << setw(10)
		<< products[productPosition].GetItemName() << setw(20)
		<< products[productPosition].GetItemID() << setw(10)
		<< products[productPosition].GetItemQty() << setw(10)
		<< products[productPosition].GetItemPrice() << setw(10)
		<< products[productPosition].GetItemType() << endl;
}

//Outputs entire product list
void PrintProductList(vector<Product> products)
{
	for (int i = 0; i < products.size(); i++)
	{
		cout << products[i].GetItemName() << setw(10)
			<< products[i].GetItemID() << setw(10)
			<< products[i].GetItemQty() << setw(10)
			<< products[i].GetItemPrice() << setw(10)
			<< products[i].GetItemType() << endl;
	}
}

//Determines whether a searched product exists in the product list.
bool ProductExists(vector<Product> products, string ID)
{
	bool productExists = false;
	for (int i = 0; i < products.size(); i++)
	{
		if (products[i].GetItemID() == ID || products[i].SearchName(ID))
		{
			PrintProduct(products, i);
			cout << endl;
			productExists = true;
		}
	}
	if (productExists)
		return true;
	else
		return false;
}

//Update product loop for menu
void UpdateProduct(vector<Product>& products)
{
	string product;
	int selection;
	int productPosition;
	bool correctChoice = false;
	bool productFound = false;

	cout << "Search the exact product to update: ";

	cin >> product;

	for (int i = 0; i < products.size(); i++)
	{
		if (products[i].GetItemName() == product || products[i].GetItemID() == product)
		{
			productFound = true;
			productPosition = i;
			PrintProduct(products, i);
			cout << endl << endl;
			break;
		}
	}

	
	if (productFound == true)//Start menu for update product if product is found.
	{
		cout << "Select product detail to update: " << endl
			<< "(1) Update Product Name" << endl
			<< "(2) Update Product ID" << endl
			<< "(3) Update Product Quantity" << endl
			<< "(4) Update Product Price" << endl
			<< "(5) Update Product Type" << endl
			<< "(6) Back" << endl << endl;

		cout << "Make a selection: ";

		while (correctChoice == false)
		{
			cin >> selection;

			if (selection == 1)
			{
				UpdateProductName(products, productPosition);
				correctChoice = true;
			}
			else if (selection == 2)
			{
				UpdateProductID(products, productPosition);
				correctChoice = true;
			}
			else if (selection == 3)
			{
				UpdateProductQty(products, productPosition);
				correctChoice = true;
			}
			else if (selection == 4)
			{
				UpdateProductPrice(products, productPosition);
				correctChoice = true;
			}
			else if (selection == 5)
			{
				UpdateProductType(products, productPosition);
				correctChoice = true;
			}
			else if (selection == 6)
			{
				return;
			}
			else
			{
				cout << "Invalid selection try again." << endl << endl;
				cout << "(1) Update Product Name" << endl
					<< "(2) Update Product ID" << endl
					<< "(3) Update Product Quantity" << endl
					<< "(4) Update Product Price" << endl
					<< "(5) Update Product Type" << endl
					<< "(6) Back" << endl << endl;
				cout << "Make a selection: ";
			}
		}

		if (selection > 0 && selection < 6)
			OutputProductList(products);
	}
	else
	{
		cout << "This product ID does not exist. " << endl;

		cout << "(1) Search Again" << endl
			<< "(2) Back" << endl << endl;

		cout << "Make a selection: ";

		while (correctChoice == false)
		{
			cin >> selection;
			cout << endl;

			if (selection == 1)
			{
				UpdateProduct(products);
				correctChoice = true;
			}
			else if (selection == 2)
			{
				correctChoice = true;
				return;
			}
			else
			{
				cout << "Invalid selection try again." << endl << endl;
				cout << "(1) Search Again" << endl
					<< "(2) Back" << endl << endl;
				cout << "Make a selection: ";
			}
		}
	}

	correctChoice = false;

	cout << "(1) Search Again" << endl
		<< "(2) Back" << endl << endl;

	cout << "Make a selection: ";
	
	while (correctChoice == false)
	{
		cin >> selection;

		if (selection == 1)
		{
			UpdateProduct(products);
			correctChoice = true;
		}
		else if (selection == 2)
		{
			return;
		}
		else
		{
			cout << "Invalid selection try again." << endl << endl;
			cout << "(1) Search Again" << endl
				<< "(2) Back" << endl << endl;
			cout << "Make a selection: ";
		}
	}
}

//Update product name for product found in UpdateProduct.
void UpdateProductName(vector<Product>& products, int productPosition)
{
	string newName;

	cout << "Choose a new product name: ";
	cin >> newName;

	cout << endl;
	products[productPosition].SetItemName(newName);

	cout << "Product name changed successfully." << endl;
	PrintProduct(products, productPosition);
	cout << endl;
}

//Update product ID for product found in UpdateProduct.
void UpdateProductID(vector<Product>& products, int productPosition)
{
	string newID;

	cout << "Choose a new product ID: ";
	cin >> newID;

	cout << endl;
	products[productPosition].SetItemID(newID);

	cout << "Product ID changed successfully." << endl;
	PrintProduct(products, productPosition);
	cout << endl;
}

//Update product quantity for product found in UpdateProduct.
void UpdateProductQty(vector<Product>& products, int productPosition)
{
	int newQty;

	cout << "Choose a new product quantity: ";
	cin >> newQty;

	cout << endl;
	products[productPosition].SetItemQty(newQty);

	cout << "Product quantity changed successfully." << endl;
	PrintProduct(products, productPosition);
	cout << endl;
}

//Update product price for product found in UpdateProduct.
void UpdateProductPrice(vector<Product>& products, int productPosition)
{
	double newPrice;

	cout << "Choose a new product ID: ";
	cin >> newPrice;

	cout << endl;
	products[productPosition].SetItemPrice(newPrice);

	cout << "Product price changed successfully." << endl;
	PrintProduct(products, productPosition);
	cout << endl;
}

//Update product type for product found in UpdateProduct.
void UpdateProductType(vector<Product>& products, int productPosition)
{
	int selection;
	bool correctChoice = false;

	cout << "Choose a new product Type: " << endl
		<< "(1) Quantity" << endl
		<< "(2) Weight" << endl
		<< "(3) None" << endl << endl;

	cout << "Make a selection: ";
	
	//Menu choice selection for new product type.
	while (correctChoice == false)
	{
		cin >> selection;

		if (selection == 1)
		{
			products[productPosition].SetItemType("Quantity");
			correctChoice = true;
		}
		else if (selection == 2)
		{
			products[productPosition].SetItemType("Weight");
			correctChoice = true;
		}
		else if (selection == 3)
		{
			products[productPosition].SetItemType("None");
			correctChoice = true;
		}
		else
		{
			cout << "Invalid selection try again." << endl << endl;
			cout << "Choose a new product Type: " << endl
				<< "(1) Quantity" << endl
				<< "(2) Weight" << endl
				<< "(3) None" << endl << endl;

			cout << "Make a selection: ";
		}
	}

	cout << endl;
	cout << "Product type changed successfully." << endl;
	PrintProduct(products, productPosition);
	cout << endl;
}

//Create a new product through user input.
void NewProduct(vector<Product>& products)
{
	string name;
	string ID;
	int qty;
	double price;
	string priceType;

	int selection;
	bool correctChoice = false;

	cout << "Set name for new product using '.' as spaces: ";
	cin >> name;

	cout << "Set ID for new product: ";
	cin >> ID;

	cout << "Set quantity for new product: ";
	cin >> qty;

	cout << "Set price for new product: ";
	cin >> price;

	cout << "Set price type for new product: " << endl
		<< "(1) Quantity" << endl
		<< "(2) Weight" << endl
		<< "(3) None" << endl << endl
		<< "Make a selection: ";

	while (correctChoice == false)
	{
		cin >> selection;
		cout << endl;

		if (selection == 1)
		{
			priceType = "Quantity";
			correctChoice = true;
		}
		else if (selection == 2)
		{
			priceType = "Weight";
			correctChoice = true;
		}
		else if (selection == 3)
		{
			priceType = "None";
			correctChoice = true;
		}
		else
		{
			cout << "Invalid selection try again." << endl << endl
				<< "(1) Quantity" << endl
				<< "(2) Weight" << endl
				<< "(3) None" << endl << endl;
			cout << "Make a selection: ";
		}
	}
	correctChoice = false;

	Product newProduct(name, ID, qty, price, priceType);
	products.push_back(newProduct);
	cout << "Product successfully created." << endl << endl;

	cout << "Would you like to create another product: " << endl << endl
		<< "(1) Yes" << endl
		<< "(2) No" << endl << endl
		<< "Make a selection: ";

	while (correctChoice == false)
	{
		cin >> selection;
		cout << endl;

		if (selection == 1)
		{
			NewProduct(products);
			correctChoice = true;
		}
		else if (selection == 2)
		{
			correctChoice = true;
		}
		else
		{
			cout << "Invalid selection try again." << endl << endl
				<< "(1) Yes" << endl
				<< "(2) No" << endl << endl;
			cout << "Make a selection: ";
		}
	}

	std::sort(products.begin(), products.end());

	OutputProductList(products);
}

//Deletes a searched product
void DeleteProduct(vector<Product>& products)
{
	int selection;
	int position;
	string product;
	bool productFound = false;
	bool correctChoice = false;

	cout << "Search the exact product to delete: ";
	cin >> product;

	for (int i = 0; i < products.size(); i++)
	{
		if (products[i].GetItemName() == product || products[i].GetItemID() == product)
		{
			productFound = true;
			position = i;
			PrintProduct(products, i);
			cout << endl << endl;
			break;
		}
	}

	if (productFound == true)//Start menu for delete product if product is found.
	{
		cout << "Are you sure you want to delete the product? " << endl
			<< "(1) Yes" << endl
			<< "(2) No" << endl << endl;

		cout << "Make a selection: ";

		while (correctChoice == false)
		{
			cin >> selection;
			cout << endl;

			if (selection == 1)
			{
				products.erase(products.begin() + position);

				cout << "Product successfully deleted." << endl << endl;

				correctChoice = true;
				OutputProductList(products);
			}
			else if (selection == 2)
			{
				return;
			}
			else
			{
				cout << "Invalid selection try again." << endl << endl;
				cout << "Are you sure you want to delete the product? " << endl
					<< "(1) Yes" << endl
					<< "(2) No" << endl << endl;
				cout << "Make a selection: ";
			}
		}
	}
	else
	{
		cout << "This product ID does not exist. " << endl;

		cout << "(1) Search Again" << endl
			<< "(2) Back" << endl << endl;

		cout << "Make a selection: ";

		while (correctChoice == false)
		{
			cin >> selection;
			cout << endl;

			if (selection == 1)
			{
				DeleteProduct(products);
				correctChoice = true;
			}
			else if (selection == 2)
			{
				correctChoice = true;
				return;
			}
			else
			{
				cout << "Invalid selection try again." << endl << endl;
				cout << "(1) Search Again" << endl
					<< "(2) Back" << endl << endl;
				cout << "Make a selection: ";
			}
		}
	}

}