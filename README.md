# InventorySystem
Grocery store inventory system that allows the user to:

Search for a product in the inventory
Update product details of a product in the inventory
Create a new product
Delete a product from the inventory

The inventory system is loaded from the inventory.txt file into a vector of objects.
The vector of objects is then sorted by product name and outputted into the inventory.txt file.
Once these operations are complete the program displays a menu, which allows the user to edit the inventory from the program.

Search operations are done by a linear search by either product name or id.
A search by product name is not case sensitive, and will also display all products and their details with inputted string.

Updating a products details does requires a case sensitive product search, and must be the exact product to allow for the updating.
Also, updating a product will output the updated inventory to the inventory.txt file. 

Creating a new product will prompt the user to input: name, id, quantity, price, and price type.
Also, creating a new product will output the new inventory to the inventory.txt file.

Deleting a product will erase the product from the inventory and output the new inventory to the inventory.txt.

Thank you for reading!
