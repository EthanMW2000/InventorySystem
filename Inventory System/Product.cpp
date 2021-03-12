/*
@author Ethan Wells
@filename Product.cpp

File contains all the definitions of the member functions of class Product.
*/

#include "Product.h"

//Default constructor
Product::Product()
{
	itemName = "NoName";
	itemID = 0;
	itemQty = 0;
	itemPrice = 0.00;
}

/*
Constructor with parameters that are assigned to itemName, itemID, and itemQty.
@param name to be assigned to private itemName.
@param ID to be assigned to private itemID.
@param qty to be assigned to private itemQty.
@param priceType to be assigned to private itemType.
*/
Product::Product(string name, int ID, int qty, double price, string priceType)
{
	itemName = name;
	itemID = ID;
	itemQty = qty;
	itemPrice = price;
	itemType = priceType;
}

//Sets parameter name to private itemName.
void Product::SetItemName(string name)
{
	itemName = name;
}

//Sets parameter ID to private itemID.
void Product::SetItemID(int ID)
{
	itemID = ID;
}

//Sets parameter qty to private itemQty.
void Product::SetItemQty(int qty)
{
	itemQty = qty;
}

//Sets parameter price to private itemPrice.
void Product::SetItemPrice(double price)
{
	itemPrice = price;
}

//sets parameter priceType to private itemType
void Product::SetItemType(string priceType)
{
	itemType = priceType;
}

//Returns itemName
string Product::GetItemName()
{
	return itemName;
}

//Returns itemID
int Product::GetItemID()
{
	return itemID;
}

//Returns itemQty
int Product::GetItemQty()
{
	return itemQty;
}

//Returns itemPrice
double Product::GetItemPrice()
{
	return itemPrice;
}

//Returns itemType
string Product::GetItemType()
{
	return itemType;
}

//Adds parameter quantity_to_add to private itemQty.
void Product::AddItemQty(int qty_to_add)
{
	itemQty += qty_to_add;
}

//Adds parameter qty_to_subtract to private itemQty.
void Product::SubtractItemQty(int qty_to_subtract)
{
	itemQty -= qty_to_subtract;
}