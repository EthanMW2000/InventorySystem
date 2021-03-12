/*
@author Ethan Wells
@filename Product.h

File is the header file for the Product class
*/

#ifndef PRODUCT_H
#define PRODUCT_H
#include<iostream>

using std::string;

class Product
{
public:
	Product();
	Product(string name, int ID, int qty, double price, string priceType);

	void SetItemName(string name);
	void SetItemID(int ID);
	void SetItemQty(int qty);
	void SetItemPrice(double price);
	void SetItemType(string priceType);

	string GetItemName();
	int GetItemID();
	int GetItemQty();
	double GetItemPrice();
	string GetItemType();

	void AddItemQty(int qty_to_add);
	void SubtractItemQty(int qty_to_subtract);

private:
	string itemName;
	int itemID;
	int itemQty;
	double itemPrice;
	string itemType;

};

#endif /* PRODUCT_H */