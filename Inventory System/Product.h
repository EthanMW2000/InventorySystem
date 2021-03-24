/*
@author Ethan Wells
@filename Product.h

File is the header file for the Product class
*/

#ifndef PRODUCT_H
#define PRODUCT_H
#include<iostream>
#include<algorithm>

using std::string;

class Product
{
public:
	Product();
	Product(string name, string ID, int qty, double price, string priceType);

	void SetItemName(string name);
	void SetItemID(string ID);
	void SetItemQty(int qty);
	void SetItemPrice(double price);
	void SetItemType(string priceType);

	string GetItemName();
	string GetItemID();
	int GetItemQty();
	double GetItemPrice();
	string GetItemType();

	void AddItemQty(int qty_to_add);
	void SubtractItemQty(int qty_to_subtract);

	bool operator<(const Product& products) const;

	bool operator==(const Product& products) const;

	bool SearchName(string ID);
	bool IgnoreCase(string ID);

private:
	string itemName;
	string itemID;
	int itemQty;
	double itemPrice;
	string itemType;

};

#endif /* PRODUCT_H */