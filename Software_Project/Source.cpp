#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

//This is the latest we got
using namespace std;
#define SUCCESS 1;
#define FAIL 0;

class Item {
private:
	/* Each item object has price , tax , total price , type (0 for drink and 1 for food),
	stockState ( 0 for out of stock and 1 for available , itemID & itemname */
	float price, tax = ((price * 14) / 100), totalPrice = price + tax;
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
	/* Operator Overloaded to compare between two item objects */
	bool operator == (Item item1)
	{
		if ( (item1.get_itemID() == itemID) && ((item1.get_itemname()) == itemname) \
			&& (item1.get_price() == price) && (item1.get_stockState() == stockState)\
			&& (item1.get_type() == type) )
		{
			
			return 1;
		}
		else
		{
			return 0;
		}
	}

};

class Menu {
public:
	/* The Menu class will be a vector of pointers to Item class objects */
	vector<Item*> MainMenu;

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
			if ((MainMenu[i]->get_itemID()) == itemId)
			{
				MainMenu.erase(MainMenu.begin() + i);
			}
		}
	}

};



class Account
{
private:
	string password;
	Admin AdminAccount;
public:
	bool newAdminAccount(Admin myAdminAcc, string myPassword)
	{
		if (myPassword == password)
		{
			AdminAccount = myAdminAcc;
			password = myPassword;
			return SUCCESS;
		}
		else
		{
			return FAIL;
		}
	}

	bool deleteAccount(int myID, string myPassword, Admin* myAdmin)
	{
		if (myPassword == password)
		{
			delete myAdmin;
			return SUCCESS;
		}
		else
		{
			return FAIL;
		}
	}

	bool changePassword(int myID, string myOldPassword, string myNewPassword)
	{
		if (myOldPassword == password)
		{
			myOldPassword = myNewPassword;
			return SUCCESS;
		}
		else
		{
			return FAIL;
		}
	}

	void viewAccountDetails(int myID, string  myPassword, Admin* myAdmin)
	{
		if (myAdmin->getID() == myID)
		{
			password = myPassword;
		}
	}

	bool login(int myID, string myPassword, Admin* myadmin)
	{
		myadmin->set_login();
		return SUCCESS;
	}
		
	bool logout(Admin* myadmin)
	{	
		myadmin->reset_login();
		return SUCCESS;
	}
};


/*Payment class and its inheritance, Order*/

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

	virtual bool checkCharge(string cardID, float price, float charge) = 0;
};


class Credit : public Payment
{
public:
	bool checkCardValidity(string cardID, string pw)
	{
		/*The card info will contain id no., password, balance(Charge)*/
		//cout << "hiii, I'm in" << endl;
		ifstream readBalance("visa.txt");
		string card_id;
		string card_pw;
		float card_balance;

		while (readBalance >> card_id >> card_pw >> card_balance)
		{
			//cout << "I'm in 1" << endl;
			if ((cardID == card_id) && (pw == card_pw))
			{
				//cout << "I'm in" << endl;
				return 1;
			}

			if (!((cardID == card_id) && (pw == card_pw)))
			{
				return 0;
			}
		}


	}

	bool checkCharge(string cardID, float price, float charge)
	{

		/* An object must be instantiated from credit class to get its price using the getPrice function to use the price in this current function
		like so :
		Credit my_payment;
		price = my_payment.getPrice();
		*/
		ifstream readBalance("visa.txt");
		string card_id;
		string card_pw;
		float card_balance;

		while (readBalance >> card_id >> card_pw >> card_balance)
		{
			if (cardID == card_id)
			{
				if (card_balance >= price)
				{
					return true;
				}

				else if (card_balance < price)
				{
					return false;
				}
			}


		}

	}
};

class Cash : public Payment
{

	bool checkCharge(float price, float charge)
	{
		if (charge >= price)
		{
			return true;
		}

		else if (charge < price)
		{
			return false;
		}
	}

};

/*Order class*/
class Order
{
private:
	bool orderType;
	float orderPrice = 0.0;
	float totalPrice = orderPrice + 0.14 * orderPrice;
	vector <Item> itemSelectedVect;
	int numberOfItem;
public:

	//this function add item and number of items chosen from this specific item
	void addToOrder(Item newItem, int selectedItemNumber = 1)
	{
		for (int i = 0; i < selectedItemNumber; i++)
		{
			itemSelectedVect.push_back(newItem);
		}
	}

	void removeFromOrder(Item toBeRemovedItem, int selectedItemNumber)
	{
		/*vector<Item>::iterator it;
		it = find(itemSelectedVect.begin(), itemSelectedVect.end(), toBeRemovedItem);
		if (it != itemSelectedVect.end())
		{
			index = it - itemSelectedVect.begin();
		}
		for (int i = 0; i < itemSelectedVect.size(); i++)
		{
			itemSelectedVect.erase(itemSelectedVect.begin()+index);
		}*/
		/*ptrdiff_t pos = find(itemSelectedVect.begin(), itemSelectedVect.end(), toBeRemovedItem) - itemSelectedVect.begin();
		for (int i = 0; i < itemSelectedVect.size(); i++)
		{
			itemSelectedVect.erase(itemSelectedVect.begin() + pos);
		}*/
		// PLEASE Return to the main function for a more detailed explanation if I was asleep , and delete this comment once you  read it
		// msh 3yzyn nesalem el  proj keda XD
		for (int i = 0; i < (itemSelectedVect.size()); i++)
		{
		
			if (itemSelectedVect[i] == toBeRemovedItem)
			{
				itemSelectedVect.erase(itemSelectedVect.begin() + i);
			}
			
		}
	}

	float confirmOrder()
	{
		for (int i = 0; i < itemSelectedVect.size(); i++)
		{
			orderPrice += (itemSelectedVect[i]).get_price();
		}
		return totalPrice;
	}
};

/*Table Class*/
class Table
{
private:
	bool stat;
public:
	vector<bool> tables_status;
	void tableReservation()
	{
		//here I'm pushing (initializing) table_status for six tables
		//1 for available ------ 0 for reserved
		//vector<bool> tables_status;
		//t1_status
		tables_status.push_back(1);

		//t2_status
		tables_status.push_back(0);

		//t3_status
		tables_status.push_back(1);

		//t4_status
		tables_status.push_back(1);

		//t5_status
		tables_status.push_back(0);

		//t6_status
		tables_status.push_back(0);
	}

	//this is a constructor that will initialize the table status
	Table()
	{

		tableReservation();

		/*for (int i = 0; i < tables_status.size(); i++)
		{
			cout << "Table " << i + 1 << " status is:" << tables_status[i] << endl;
		}*/

	}

	bool reserveTable(int table_no)
	{
		bool table_stat = tables_status.at(table_no - 1);

		//cout << table_no << " " << tables_status[table_no - 1] << endl;

		//here we need to check if the table is already reserved
		if (table_stat == 0)
		{
			//cout << "Am I in?" << endl;

			return 0; //reservation failed choose another table
		}

		else if (table_stat == 1)
		{
			//here we will change the value of the table status in the vector
			tables_status[table_no - 1] = 0;
			//cout << "changing the table stat from " << !tables_status[table_no - 1] << " to " << tables_status[table_no - 1] << endl;
			return 1; //table reserved
		}
	}
};


class User
{
protected:
	string name, address, city, number;
	int age, id;
	bool is_logged_in;
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
	virtual void set_login() = 0;
	virtual void reset_login() = 0;
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

/*system class*/
class System
{
public:
	vector <Order*> AllOrdersVect;
	Order customizedOrder;
	Menu integratedMenu;
	Table tablesArr;
	
	void makeOrder(Item item)
	{
		customizedOrder.addToOrder(item);
	}
	void viewMenu(Menu myMenu)
	{
		for (int i = 0; i < myMenu.MainMenu.size(); i++)
		{
			cout << myMenu.MainMenu[i] << endl;
		}
	}
	void makePayment(Credit mypay)
	{
		/* Here we need extra parameters such as price and card details */
	}
	string checkPersonalOrderStatus(int orderNum)
	{
		/* Some Code */
	}
	void checkAvailableTables()
	{
		/*some code*/
	}
};


class Admin : public User
{
private:
	string jobType;
	bool workStatus, active;
	float rate;

public:
	void setWorkStatus(bool mystatus)
	{
		workStatus = mystatus;
	}
	bool getWorkStatus()
	{
		return workStatus;
	}
	void editMenu(Item *myItem, Menu *myMenu)
	{
		myMenu->addItem(myItem);
	}
	bool setStatus()
	{
		active = 1;
	}
	void checkAllOrderStatus(System MainSystemObject)
	{
		for (int i = 0; i < MainSystemObject.AllOrdersVect.size(); i++)
		{
			//cout << (MainSystemObject.AllOrdersVect)[i].itemsselected[/*loop here to print every item of every order :)*/];
		}
		// Still Under Construction
	}
	void set_login()
	{
		is_logged_in = 1;
	}
	void reset_login()
	{
		is_logged_in = 0;
	}
	bool view_loginStatus()
	{
		return is_logged_in;
	}
};
void bankSimulation()
{
	/*initializing some credit card info*/
	ofstream balance("visa.txt", ios::app);
	string card1_No = "4024007141525864";
	string card1_pw = "dina";
	float card1_balance = 100;

	string card2_No = "4532295627154748";
	string card2_pw = "dinadina";
	float card2_balance = 1;

	string card3_No = "4929230781795532";
	string card3_pw = "dinadinadina";
	float card3_balance = 200;

	balance << card1_No << " " << card1_pw << " " << card1_balance << endl;
	//cout << card1_No << " " << card1_pw << endl;

	balance << card2_No << " " << card2_pw << " " << card2_balance << endl;
	//cout << card2_No << " " << card2_pw << endl;

	balance << card3_No << " " << card3_pw << " " << card3_balance << endl;
	//cout << card3_No << " " << card3_pw << endl;
	balance.close();
}

/*void tableReservation()
{
	//initializing some table reserved and available
	ofstream my_table("tables.txt", ios::app);
	//1 for available ------ 0 for reserved
	string table1 = "table_1";
	bool t1_status = 1;

	string table2 = "table_2";
	bool t2_status = 0;

	string table3 = "table_3";
	bool t3_status = 0;

	string table4 = "table_4";
	bool t4_status = 1;

	string table5 = "table_5";
	bool t5_status = 1;

	string table6 = "table_6";
	bool t6_status = 0;

	my_table << table1 << " " << t1_status << endl;

	my_table << table2 << " " << t2_status << endl;

	my_table << table3 << " " << t3_status << endl;

	my_table << table4 << " " << t4_status << endl;

	my_table << table5 << " " << t5_status << endl;

	my_table << table6 << " " << t6_status << endl;

	my_table.close();
}*/


int main() {

	/*Item item1;
	item1.setItem(0, 0, 0, 12, "Amr");
	Item item2;
	item2.setItem(0, 0, 0, 10, "Dina");
	if (item1 == item1)
	{
		cout << "Succeeded";
	}
	else
	{
		cout << "Fail";
	}*/
	//bankSimulation(); //This only initialized one time to fill the credit card info, or you could either remove ios::app to overwrite the file


	/*Test case
	Table dina;
	bool my_result = dina.reserveTable(2);
	cout << "your result is :" << my_result << endl;*/

	/*test case
	Credit my_payment;
	float price = my_payment.getPrice();
	string card1 = "4024007141525864";
	string pw1 = "dina";
	bool result;
	result = my_payment.checkCardValidity(card1, pw1);
	cout << "My result is " << result << endl;*/

	return 0;
}