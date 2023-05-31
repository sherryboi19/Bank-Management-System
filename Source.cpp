//........BANK MANAGMENT SYSTEM.......

#include<iostream> //Heafer Files included in program for input output stream
#include<string>   //Heafer Files included in program for storing string data
#include<fstream>  //Heafer Files included in program for file handling
#include<iomanip>  //Heafer Files included in program for manipulation
using namespace std;

//....FUNCTIONS PROTOTYPES....

void menu();//function for main menu.
void get_choice();//function for getting choice
void write_account();//function for writing account in file
void show_account(int);//function to display an account
void modify_account(int);//function to modify data of an account
void delete_account(int);//function to delete data of a file
void view_list();//function to display all account details
void bal_inquiery(int);//function to display specific account detail
void deposit_withdraw(int, int);//function to deposit or withdraw ammount
void transection(int, int, float);//function to transfer ammount

//....STRUCT...
struct account
{
	int account_num;
	string name;
	string city;
	string state;
	int zip;
	string phone_num;
	float balance;
	string date;
};
//...MAIN FUNCTION...
void main()
{
	menu();
}
//...FUNCTION TO DISPLAY MENU SCREEN...
void menu()
{
	system("cls");
	cout << "\n\n\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << endl << endl;
	cout << "\t\t\t\tMAIN MENU";
	cout << "\n\n\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << endl << endl;
	cout << "\t  [1]. Enter new records into the file.\n\n";
	cout << "\t  [2]. Search for a particular customer's record and display it.\n\n";
	cout << "\t  [3]. Search for a particular customer's record and delete it.\n\n";
	cout << "\t  [4]. Search for a particular customer's record and change it.\n\n";
	cout << "\t  [5]. View all customer's list.\n\n";
	cout << "\t  [6]. Balance Inquiry.\n\n";
	cout << "\t  [7]. Deposit Amount.\n\n";
	cout << "\t  [8]. Withdraw Amount.\n\n";
	cout << "\t  [9]. Transfer Amount to other Account.\n\n";
	cout << "\t [10]. Exit from Program.\n\n";
	get_choice();//FUNCTION CALL
}
//...GETTING CHOICE FUNCTION FOR SPECIFIC ACTIONS...
void get_choice()
{
	int choice;
	int ac_num, sender, reciever;
	float ammount;
	cout << "\t\tEnter Choice [1-10] : ";
	cin >> choice;
	while (choice < 1 || choice>10)
	{
		cout << "\n\n\t\tInvalid ! " << endl;
		cout << "\n\t\tEnter Choice [1-10] :";
		cin >> choice;
	}

	switch (choice)
	{
	case 1:
		write_account();//FUNCTION CALL
		break;
	case 2:
		cout << "\n\n\tEnter Account Number : ";
		cin >> ac_num;
		show_account(ac_num);//FUNCTION CALL
		break;
	case 3:
		cout << "\n\n\tEnter Account Number : ";
		cin >> ac_num;
		delete_account(ac_num);//FUNCTION CALL
		break;
	case 4:
		cout << "\n\n\tEnter Account Number : ";
		cin >> ac_num;
		modify_account(ac_num);//FUNCTION CALL
		break;
	case 5:
		view_list();//FUNCTION CALL
		break;
	case 6:
		cout << "\n\n\tEnter Account Number : ";
		cin >> ac_num;
		bal_inquiery(ac_num);//FUNCTION CALL
		break;
	case 7:
		cout << "\n\n\tEnter Account Number : ";
		cin >> ac_num;
		deposit_withdraw(ac_num, 1);//FUNCTION CALL
		break;
	case 8:
		cout << "\n\n\tEnter Account Number : ";
		cin >> ac_num;
		deposit_withdraw(ac_num, 2);//FUNCTION CALL
		break;
	case 9:
		cout << "\n\n\tEnter Account Number of Sender : ";
		cin >> sender;
		cout << "\n\n\tEnter Account Number of Reciever : ";
		cin >> reciever;
		cout << "\n\n\tEnter Ammount to be Transfered : ";
		cin >> ammount;
		while (ammount <= 0)
		{
			cout << "\nInvalid Ammount\n";
			cout << "Again Enter Amount to be Deposited : ";
			cin >> ammount;
		}
		transection(sender,reciever,ammount);//FUNCTION CALL
		break;
	case 10:
		cout << "\n\n\t.....Thanks For Using our System....." << endl;
		exit(0);//EXIT FUNCTION
		break;
	default:
		cout << "Error";
	}
}
//...FUNCTION FOR CREATING ACCOUNT...
void write_account()
{
	system("cls");
	int account_number;
	account ac;
	bool flag = false;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);//OPENING INPUT FILE TO GET DATA FROM FILE
	outFile.open("account.dat", ios::app | ios::binary);//OPENING OUTPUT FILE TO ADD DATA IN FILE
	//CHECKING IF ACCOUT ALREADY EXISIS
	cout << "\nEnter Account Number : ";
	cin >> account_number;
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	//SEARCH FROM FILE
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.account_num == account_number)
		{
			cout << "\n\n\t...ACCOUNT ALREADY EXISTS..." << endl << endl;
			flag = true;
		}
	}
	inFile.close();//CLOSING INPUT FILE
	if (flag == false)
	{
		//TAKING INPUT FROM USER
		ac.account_num = account_number;
		cout << "\nEnter Account Holder's Name :";
		cin.ignore();
		getline(cin, ac.name);
		cout << "\nEnter Name of the City : ";
		getline(cin, ac.city);
		cout << "\nEnter Name of the State : ";
		getline(cin, ac.state);
		cout << "\nEnter ZIP Code : ";
		cin >> ac.zip;
		cout << "\nEnter Phone Number (+92XXXXXXXXXX) : ";
		cin.ignore();
		getline(cin, ac.phone_num);
		cout << "\nEnter Account Balance : ";
		cin >> ac.balance;
		cout << "\nEnter Last Payment Date (DD/MM/YYYY): ";
		cin.ignore();
		getline(cin, ac.date);
		cout << "\n\n\t\tACCOUNT CREATED..\n";
		outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));//WRITING FILE
		outFile.close();//CLOSING OUTPUT FILE
	}
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}
//...FUNCTION TO SHOW ACCOUNT DETAILS...
void show_account(int n)
{
	system("cls");
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);//OPENING INPUT FILE TO GET DATA FROM FILE
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\tBALANCE DETAILS\n";
	//SEARCH FROM FILE
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.account_num == n)
		{
			cout << "Account Number : " << ac.account_num << endl;
			cout << "Account Holder's Name :" << ac.name << endl;
			cout << "Name of the City : " << ac.city << endl;
			cout << "Name of the State : " << ac.state << endl;
			cout << "ZIP Code : " << ac.zip << endl;
			cout << "Phone Number : " << ac.phone_num << endl;
			cout << "Account Balance : " << ac.balance << endl;
			cout << "Last Payment Date : " << ac.date << endl;
			flag = true;
		}
	}
	inFile.close();//CLOSING INPUT FILE
	if (flag == false)
	{
		cout << "\n\n\t\tAccount Not Found !";
	}
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}
//...FUNCTION FOR DELETING ACCOUNT...
void delete_account(int n)
{
	system("cls");
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);//OPENING INPUT FILE TO READ DATA
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);//OPENING TEMPORARY FILE TO DUPLICATE DATA
	inFile.seekg(0, ios::beg);//MOVE POSITION TO BEGINING
	//CHECKING FILE AND TAKE DATA FROM INPUT FILE AND STORE TO OUTPUT FILE
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.account_num != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();//CLOSING INPUT FILE
	outFile.close();//CLOSING OUTPUT FILE
	remove("account.dat");//REMOVING PREVIOUS FILE
	rename("Temp.dat", "account.dat");//RENAMING TEMPORARY FILE TO CURRENTLY USING FILE
	cout << "\n\n\t\tACCOUNT DELETED ..";
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}
//...FUNCTION TO MODIFY RECORD...
void modify_account(int n)
{
	system("cls");
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);//OPENING FILE IN BOTH MODES
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));//READ FILE TO SEARCH
		if (ac.account_num == n)
		{
			cout << "Account Number : " << ac.account_num << endl;
			cout << "Account Holder's Name :" << ac.name << endl;
			cout << "Name of the City : " << ac.city << endl;
			cout << "Name of the State : " << ac.state << endl;
			cout << "ZIP Code : " << ac.zip << endl;
			cout << "Phone Number : " << ac.phone_num << endl;
			cout << "Account Balance : " << ac.balance << endl;
			cout << "Last Payment Date : " << ac.date << endl;

			cout << "\n\nEnter The New Details of account" << endl;
			cout << "\nAccount Number : " << ac.account_num << endl;
			//MODIFYING DATA
			cout << "\nEnter Account Holder's Name :";
			cin.ignore();
			getline(cin, ac.name);
			cout << "\nEnter Name of the City : ";
			getline(cin, ac.city);
			cout << "\nEnter Name of the State : ";
			getline(cin, ac.state);
			cout << "\nEnter ZIP Code : ";
			cin >> ac.zip;
			cout << "\nEnter Phone Number (+92XXXXXXXXXX) : ";
			cin.ignore();
			getline(cin, ac.phone_num);
			cout << "\nEnter Account Balance : ";
			cin >> ac.balance;
			cout << "\nEnter Last Payment Date (DD/MM/YYYY): ";
			cin.ignore();
			getline(cin, ac.date);
			int pos = (-1)*static_cast<int>(sizeof(account));//GET POSITION BACK TO SIZE OF ONE STRUCT
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));//WRITING NEW DATA
			cout << "\n\n\t\tACCOUNT UPDATED..";
			found = true;
		}
	}
	File.close();//CLOSING FILE
	if (found == false)
	{
		cout << "\n\n\t\tAccount Not Found !";
	}
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}
//...FUNCTION TO VIEW ALL ACCOUNTS...
void view_list()
{
	system("cls");
	account ac;
	cout << "\n\n\n\t\t\t\t\t\t\t==============================================================";
	cout << "\n\t\t\t\t\t\t\t\t     -----------------------------------";
	cout << "\n\n\t\t\t\t\t\t\t\t\t        ~ VIEW RECORDS ~  \n\n";
	cout << "\t\t\t\t\t\t\t\t     ------------------------------------";
	cout << "\n\t\t\t\t\t\t\t==============================================================\n\n\n\n";
	
	cout << right << setw(12) << fixed;
	cout << "Account No" << " ||";
	cout << right << setw(21) << fixed;
	cout << "Name ||";
	cout << right << setw(18) << fixed;
	cout << "City ||";
	cout << right << setw(24) << fixed;
	cout << "State ||";
	cout << right << setw(20) << fixed;
	cout << "Zip Code ||";
	cout << right << setw(20) << fixed;
	cout << "Telephone Number ||";
	cout << right << setw(19) << fixed;
	cout << "  Account Balance  ||";
	cout << right << setw(20) << fixed;
	cout << "   Last Payment Date ||\n\n";
	ifstream inFile;
	inFile.open("account.dat",ios::binary);//OPENING INPUT FILE

	if (!inFile)
	{
		cout << "\n\n\t\t\t\t\t\t Sorry, we can't open the the file because File does not exit !!!!!\n";
	}
	//DISPLAYING ACCOUNT LIST
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))&&!inFile.eof())
	{
		cout << right << setw(12) << fixed;
		cout << ac.account_num << " ||";
		cout << right << setw(18) << fixed;
		cout << ac.name << " ||";
		cout << right << setw(15) << fixed;
		cout << ac.city << " ||";
		cout << right << setw(20) << fixed;
		cout << ac.state << "  ||";
		cout << right << setw(16) << fixed;
		cout << ac.zip << "  ||";
		cout << right << setw(18) << fixed;
		cout << ac.phone_num << " ||";
		cout << right << setw(17) << fixed;
		cout << ac.balance << " ||";
		cout << right << setw(20) << fixed;
		cout << ac.date << " ||\n\n";

	}
	inFile.close();//CLOSING INPUT FILE
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}
//...FUNCTION FOR BALANCE INQUIERY...
void bal_inquiery(int n)
{
	system("cls");
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);//OPENING INPUT FILE
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	//SEARCH ACCOUNT
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.account_num == n)
		{
			//DISPLAYING OUTPUT
			cout << right << setw(12) << fixed;
			cout << "Account No" << " ||";
			cout << right << setw(21) << fixed;
			cout << "Name ||";
			cout << right << setw(18) << fixed;
			cout << "City ||";
			cout << right << setw(24) << fixed;
			cout << "State ||";
			cout << right << setw(20) << fixed;
			cout << "Zip Code ||";
			cout << right << setw(20) << fixed;
			cout << "Telephone Number ||";
			cout << right << setw(19) << fixed;
			cout << "  Account Balance  ||";
			cout << right << setw(20) << fixed;
			cout << "   Last Payment Date ||\n\n";
			cout << right << setw(12) << fixed;
			cout << ac.account_num << " ||";
			cout << right << setw(18) << fixed;
			cout << ac.name << " ||";
			cout << right << setw(15) << fixed;
			cout << ac.city << " ||";
			cout << right << setw(20) << fixed;
			cout << ac.state << "  ||";
			cout << right << setw(16) << fixed;
			cout << ac.zip << "  ||";
			cout << right << setw(18) << fixed;
			cout << ac.phone_num << " ||";
			cout << right << setw(17) << fixed;
			cout << ac.balance << " ||";
			cout << right << setw(20) << fixed;
			cout << ac.date << " ||\n\n";

			flag = true;
		}
	}
	inFile.close();//CLOSING INPUT FILE
	if (flag == false)
	{
		cout << "\n\n\t\tAccount Not Found !";
	}
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}
//...FUNCTION TO DEPOSIT OR WITHDRAW AMMOUNT FROM ACCOUNT...
void deposit_withdraw(int n, int option)
{
	system("cls");
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);//OPENING FILE IN BOTH MODES
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)//READING UPTILL END OF FILE
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));//SEARCHING ACCOUNT
		if (ac.account_num == n)
		{
			cout << "Account Number : " << ac.account_num << endl;
			cout << "Account Holder's Name :" << ac.name << endl;
			cout << "Name of the City : " << ac.city << endl;
			cout << "Name of the State : " << ac.state << endl;
			cout << "ZIP Code : " << ac.zip << endl;
			cout << "Phone Number : " << ac.phone_num << endl;
			cout << "Account Balance : " << ac.balance << endl;
			cout << "Last Payment Date : " << ac.date << endl;
			if (option == 1)//FOR DEPOSIT
							{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter Amount to be Deposited";
				cin >> amt;
				while (amt <= 0)
				{
					cout << "\nInvalid Ammount\n";
					cout << "Again Enter Amount to be Deposited : ";
					cin >> amt;
				}
				ac.balance += amt;
				cout << "\nEnter Last Payment Date (DD/MM/YYYY): ";
				cin.ignore();
				getline(cin, ac.date);
			}
			if (option == 2)//FOR WITHDRAWAL
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter Amount to be Withdraw";
				cin >> amt;
				int bal = ac.balance - amt;
				if (bal < 0)
				{
					cout << "\nInsufficience Balance" << endl;
				}
				else
				{
					ac.balance -= amt;
					cout << "\nEnter Last Payment Date (DD/MM/YYYY): ";
					cin.ignore();
					getline(cin, ac.date);
				}
			}
			int pos = (-1)*static_cast<int>(sizeof(ac));//GET POSITION OF POINTER
			File.seekp(pos, ios::cur);//MOVE POSITION FROM CURRENT POSITION
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));//WRITE MODIFIED DATA
			cout << "\n\n\t\tACCOUNT UPDATED..";
			found = true;
		}
	}
	File.close();
	if (found == false)
	{
		cout << "\n\n\t\tAccount Not Found !";
	}
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}
//...FUNCTION FOR TRANSFERING AMMOUNT BETWEEN TWO ACCOUNTS...
void transection(int sender, int reciever, float amt)
{
	system("cls");
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);//OPENING FILE IN BOTH MODES
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!inFile.eof()
		)//READING UPTILL END OF FILE
	{
		inFile.read(reinterpret_cast<char *> (&ac), sizeof(account));//READING FILE TO SEARCH 
		if (ac.account_num == sender)
		{
			//CHANGING ACCOUT OF SENDER
			int bal = ac.balance - amt;
			if (bal < 0)
			{
				cout << "\n\n\t\tInsufficience Balance!!" << endl;
			}
			else
			{
				outFile.open("account.dat", ios::binary);
				ac.balance -= amt;
				int pos = (-1)*static_cast<int>(sizeof(ac));
				outFile.seekp(pos, ios::cur);
				outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
				outFile.close();
			}
		}
		if (ac.account_num == reciever)
		{
			//CHANGING ACCOUNT OF RECIEVER
			outFile.open("account.dat", ios::binary);
			ac.balance += amt;
			int pos = (-1)*static_cast<int>(sizeof(ac));
			outFile.seekp(pos, ios::cur);
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
			outFile.close();
		}
	}
	inFile.close();
	cout << endl << endl;
	system("pause");
	menu();//FUNCTION CALL
	get_choice();//FUNCTION CALL
}