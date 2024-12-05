#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define endl '\n'

void Home(string);
void showMenu(string);
void showBill(string);

class Bill
{
public:
    string itemName;
    double price;
    Bill *next;

    Bill(string itemName, double price)
    {
        this->itemName = itemName;
        this->price = price;
        next = nullptr;
    }
};

class customer
{
public:
    string name, mobileNumber;
    customer(string name, string mobileNumber)
    {
        this->name = name;
        this->mobileNumber = mobileNumber;
    }
};
class Items
{
public:
    string itemName;
    double price;
};

Bill *headbill = nullptr;
Bill *tailbill = headbill;

void addToBill(map<int, Items> &itemList, int choice)
{

    Bill *temp = new Bill(itemList[choice].itemName, itemList[choice].price);

    if (headbill == NULL)
    {
        headbill = temp;
        tailbill = headbill;
    }
    else
    {
        tailbill->next = temp;
        tailbill = tailbill->next;
    }
}

void Home(string mobileNumber)
{
    system("clear");
    ifstream fin("Customer.txt");
    string line, name;
    while (getline(fin, line))
    {
        int pos = line.find(',');
        string mob = line.substr(0, pos);
        if (mob == mobileNumber)
        {
            name = line.substr(pos + 1);
            break;
        }
    }
    cout << " WELCOME " << name << endl;
    cout << "-----------------------\n" << endl;
    cout << "1. MENU " << endl;
    cout << "2. CHECKOUT YOUR ORDERS" << endl;
    cout << "-----------------------\n" << endl;

    cout << "SELECT (1 | 2) : ";

    int select;
    cin >> select;

    switch (select)
    {
    case 1:
        showMenu(mobileNumber);
        break;
    case 2:
        showBill(mobileNumber);
        break;
    default:
        cout << " Invalid Choice !" << endl;
        Home(mobileNumber);
        break;
    }
}

void loadMenuItems(string option, string mobileNumber)
{
    system("clear");
    map<int, Items> itemList;
    ifstream fin("Menu.txt");
    string itemCategory;
    while (!fin.eof())
    {

        getline(fin, itemCategory);
        if (itemCategory == option)
        {
            string line;
            int slno = 0;
            while (getline(fin, line))
            {

                if (line.empty())
                {
                    break;
                }
                int pos = line.find(',');

                Items item; // temporary object

                item.itemName = line.substr(0, pos);
                item.price = stod(line.substr(pos + 1));

                itemList[++slno] = item; // menu stack
            }
            slno = 0;
        }
    }
    cout<<"\n\n";
    cout << " ----- ITEM ----- " << "       " << " --- PRICE --- " << endl;
    for (auto val : itemList)
    {
        cout << val.first << " . " << val.second.itemName << "          " << "$" << val.second.price << endl;
    }

    cout << " ENTER YOUR CHOICE :";

    int choice;
    cin >> choice;
    // cout<<choice<<endl;
    // cout<<itemList[choice].itemName <<"  " <<itemList[choice].price<<endl;

    addToBill(itemList, choice);

    cout<<"\n"<<endl;

    cout << " ----- ITEMS IN YOUR BILL ------" << endl;
    cout<<"\n";
    Bill *temp = headbill;
    while (temp != nullptr)
    {
        cout << temp->itemName << "   " << "$" << temp->price << endl;
        temp = temp->next;
    }
    cout<<"\n\n";
    cout << " ITEM ADDED , DO YOU WANT TO ADD MORE ITEM FROM THIS CATEGORY ? (Y|N) or C to check your cart : ";

    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
        loadMenuItems(option, mobileNumber);
    else if (ch == 'C' || ch == 'c')
        showBill(mobileNumber);
    else
        showMenu(mobileNumber);
}

void showBill(string mobileNumber)
{
    system("clear");
    Bill *bill = headbill;
    double total = 0;
    if(headbill == nullptr){
        cout<<"NO ITEMS ADDED FOR CHECKOUT !"<<endl;
        char ch;   
        cout<<"GO TO HOME (Y|N) : ";
        cin >> ch;
        if(ch == 'Y' || ch == 'y'){
            Home(mobileNumber);
        }else return;
    }
    while (bill != nullptr)
    {
        cout << bill->itemName << "   " << "$" << bill->price << endl;
        total += bill->price;
        bill = bill->next;
    }
    cout<<"----------------------------- \n"<<endl;
    cout << "Total Bill             $" << total << endl;
    cout<<"----------------------------- \n"<<endl;
    cout << " CHECKOUT (Y|N) : ";
    char ch;
    cin >> ch;

    if (ch == 'Y' || ch == 'y')
    {
        cout << "\n THANK YOU FOR ORDERING , HAVE A GREAT DAY ! \n" << endl;
    }
    return;
}

void showMenu(string mobileNumber)
{
    system("clear");

    cout << "-----MENU----" << endl;
    cout << "1. HOT BEVRAGES " << endl;
    cout << "2. COLD BEVRAGES " << endl;
    cout << "3. BACK TO HOME " << endl;
    cout << "4. CHECKOUT " << endl;

    cout<<"\n ----------------------------- \n"<<endl;

    cout << "ENTER YOUT CHOICE : " ;

    int select;
    cin >> select;
    string option = "";
    switch (select)
    {
    case 1:
        option = "HOT BEVRAGES";
        break;
    case 2:
        option = "COLD BEVRAGES";
        break;
    case 3:
        Home(mobileNumber);
        break;
    case 4: 
        showBill(mobileNumber);
        break;
    default:
        cout << "Invalid Choice !";
        showMenu(mobileNumber);
    }
    
    loadMenuItems(option, mobileNumber);
}

int main()
{
    system("clear");
    string mobileNumber;
    cout << "----- WELCOME -----" << endl;
    cout << "ENTER YOUR MOBILE NUMBER : ";
    cin >> mobileNumber;

    ifstream fin("Customer.txt");
    string line;
    bool exists = false;

    while (getline(fin, line))
    {
        int pos = line.find(',');
        string mob = line.substr(0, pos);
        if (mob == mobileNumber)
        {
            exists = true;
        }
    }

    if (exists)
        Home(mobileNumber);
    else
    {
        string name;
        cout << "ENTER YOUR NAME : ";
        cin >> name;
        ofstream fout("Customer.txt", ios::app);
        fout << mobileNumber << "," << name << "\n";
        fout.close();
        Home(mobileNumber);
    }

    return 0;
}