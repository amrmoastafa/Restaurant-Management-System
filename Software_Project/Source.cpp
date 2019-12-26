#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Item {
private:
	/* Each item object has price , tax , total price , type (0 for drink and 1 for food),
	stockState ( 0 for out of stock and 1 for available , itemID & itemname */
	float price,tax = ((price * 14) / 100) , totalPrice = price + tax;
	bool type, stockState;
	int itemID;
	string itemname;

public:
	/* A function to set the attributes of items , it take input itemtype , price , stockstate , itemit, itemname */
	void setItem(bool itemType, float itemPrice, bool itemStockState, int ItemID, string itemName)
	{
		type = itemType;
		price = itemPrice;
		stockState = itemStockState;
		itemID = ItemID;
		itemname = itemName;
	}
	/* The following are functions to view the item details */
	float get_price()
	{
		return price;
	}
	bool get_type()
	{
		return type;
	}
	bool get_stockState()
	{
		return stockState;
	}
	float get_totalPrice()
	{
		return totalPrice;
	}
	int get_itemID()
	{
		return itemID;
	}
	string get_itemname() 
	{
		return itemname;
	}
};

class Menu {
private:
	/* The Menu class will be a vector of pointers to Item class objects */
	vector<Item*> MainMenu;

public:
	/* the addItem method can be used to add an item to the vectors by passing the Item object address */
	void addItem(Item* myItem)
	{
		MainMenu.push_back(myItem);
	}
	/* Deleting an item will be done by sending the required item ID to the function deleteItem */
	void deleteItem(int itemId)
	{
		/* A loop iterating over the vector elements */
		for (unsigned int i = 0; i < MainMenu.size(); i++)
		{	
			/* the item will be deleted if its ID is the same as the (required item to be deleted) ID,
				, the arrow operator is used to access the attribute(ID) of the current iterated object */
			if (  (MainMenu[i]->get_itemID()) == itemId )
			{
				MainMenu.erase(MainMenu.begin() + i);
			}
		}
	}

};

class User
{
private:
	string name, address, city, number;
	int age, id;
public:
	/*User Class Code Goes Here*/
	void setName(string myName)
	{
		name = myName;
	}
	void setAge(int myAge)
	{
		age = myAge;
	}
	void setAddress(string myAdddress)
	{
		address = myAdddress;
	}
	void setCity(string myCity)
	{
		city = myCity;
	}
	void setNumber(string myNumber)
	{
		number = myNumber;
	}
	void setID(int myID)
	{
		id = myID;
	}
	/* The get functions should start here */
	string getName()
	{
		return name;
	}	
	
	int getAge()
	{
		return age;
	}

		string getAddress()
	{
		return address;
	}

	string getCity()
	{
		return city;
	}

	string getNumber()
	{
		return number;
	}

	int getID()
	{
		return id;
	}




























};

class Admin : private User
{
	/* Admin class code */

















};

class Account
{
private:
	string password;
	Admin AdminAccount;
public:
	bool newAdminAccount(Admin myAdminAcc, string myPassword)
	{
		/*NEED  to check whether the name is unique or not
        we'll put the names in a vector, and loop over them, right?*/
	}
};


/*Payment class and its inheritance*/

class Payment 
{

private:
	float price;
	bool paymentStatus;

public:
	void setPaymentStatus(bool ps) 
	{
		paymentStatus = ps;
	}

	bool  getPaymentStatus() 
	{
		return paymentStatus;
	}


	float getPrice() 
	{
		return price;
	}

	virtual bool checkCharge(float price,float charge) = 0;
};


class Credit : private Payment
{
public:
	bool checkCardValidity(string cardID, string pw)
	{

	}

	bool checkCharge(float price, float charge) 
	{
		ifstream readBalance("visa.txt");

		/*The card info will contain id no., password, balance(Charge)*/
		
		/* An object must be instantiated from credit class to get its price using the getPrice function to use the price in this current function
		like so :
		Credit my_payment;
		price = my_payment.getPrice();
		*/
		
		if (charge >= price)
		{
			return true;
		}

		else if (charge < price)
		{
			return false;
		}
	}

	bool checkCardValidity()
	{

	}

};


class Cash : private Payment
{


};

void bankSimulation()
{
	/*initializing some credit card info*/
	ofstream balance("visa.txt",ios::app);
	string card1_No = "4024007141525864";
	string card1_pw = "dina";
	int card1_balance = 100;

	string card2_No = "4532295627154748";
	string card2_pw = "dinadina";
	int card2_balance = 1;

	string card3_No = "4929230781795532";
	string card3_pw = "dinadinadina";
	int card3_balance = 200;

	balance << card1_No << " " << card1_pw << " " << card1_balance << endl;
	cout << card1_No << " " << card1_pw << endl;

	balance << card2_No << " " << card2_pw << " " << card2_balance << endl;
	cout << card2_No << " " << card2_pw << endl;
	
	balance << card3_No << " " << card3_pw << " " << card3_balance << endl;
	cout << card3_No << " " << card3_pw << endl;
	balance.close();
}


int main() {
	bankSimulation();
	return 0;
}