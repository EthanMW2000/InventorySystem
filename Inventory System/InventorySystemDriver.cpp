/*
@author Ethan Wells
@filename InvetorySystemDriver.cpp

File runs the inventory system.
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include "Product.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::setw;

void LoadProductList(vector<Product> &products, ifstream &systemInventory);
void OutputProductList(vector<Product> &products);
void PrintProductList(vector<Product> products);

int main()
{
	vector<Product> products;

	ifstream systemInventory;

	systemInventory.open("inventory.txt");
	if (systemInventory.is_open())
		LoadProductList(products, systemInventory);
	else
		cout << "Unable to open file." << endl;

	PrintProductList(products);

	OutputProductList(products);

	return 0;
}

void LoadProductList(vector<Product> &products, ifstream &systemInventory)
{
	string name;
	int ID;
	int qty;
	double price;
	string priceType;

	while (!systemInventory.eof())
	{
		systemInventory >> name >> ID >> qty >> price >> priceType;

		products.emplace_back(name, ID, qty, price, priceType);
	}

	systemInventory.close();
}

void OutputProductList(vector<Product> &products)
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

void PrintProductList(vector<Product> products)
{
	for (int i = 0; i < products.size(); i++)
	{
		cout << setw(10)
			<< products[i].GetItemName() << setw(10)
			<< products[i].GetItemID() << setw(10)
			<< products[i].GetItemQty() << setw(10)
			<< products[i].GetItemPrice() << setw(10)
			<< products[i].GetItemType() << endl;
	}
}