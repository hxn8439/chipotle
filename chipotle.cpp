//Hamilton Nguyen 1000538439 problem 3 07/06/2019

#include<iostream>
#include<fstream>

using namespace std;

string ToLowerCase(string w)
{
	for (int i=0; i<w.size(); i++)
	{
		w[i] = tolower(w[i]);
	}
	
	return w;
}

ifstream f("DeliveryPeople.txt"); //Opening this file having names of delivery people

class delivery //Parent class delivery
{
	private:
		string fname, lname, fullname;

	protected:
		static double TotalMake;

	public:

		string first_name,last_name,NewName;

	void CreateDelivery(double totalPrice)//This function gets name of delivery person from file
	{
		// placeOrder() function is being called
		f>>fname;
		f>>lname;
		cout<<"\nOkay, "<<fname<<" will be delivering your order. Thank You";
	}
	void apply()//This function adds a delivery person in file deliverypersons.txt. Called by main function
	{
		ofstream written("DeliveryPeople.txt",ios::app);
		cout<<"\nEnter your name in full: ";
		cin>>first_name>>last_name;
		NewName = first_name +" " +last_name;
		written<<endl<<NewName;
		cout<<"Newest delivery person: "<<first_name<<endl;
		written.close();	
	}

};

//Initializing static member variable of delivery class with 0
double delivery::TotalMake = 0;

class customer: public delivery //Derived class customer
{
	private:
		string chipotle, pick1, pick2, pick3, option;
		double price;
	
	public:
		double orderTotal;
	
	double placeOrder() //this function handles the place orders of chipotle
	{
		cout<<"\n*****Place your order*****";
		cout<<"\nBurrito or Bowl?\n";
		cin >> chipotle;

		if(ToLowerCase(chipotle) == "burrito")
		{	
			orderTotal = 6.75;
		}
		
		if(ToLowerCase(chipotle) == "bowl")
		{	
			orderTotal = 3.20;
		}
		
		cout<<"Price will be: $"<<orderTotal;		
		cout<<"\n\nPick: Tofu, Steak, Chicken\n";
		cin.ignore();
		getline(cin,pick1);
		int num, num1;
		string word1, word2;
		num = pick1.find(",");
		num1 = pick1.length();
		word1 = pick1.substr(0,num);
		word2 = pick1.substr(num+2, num1);
		
		if(ToLowerCase(word1) != "none" || ToLowerCase(word1) == "tofu" || ToLowerCase(word1) == "steak" || ToLowerCase(word1) == "chicken")
		orderTotal += 1.99; //add $1.99 to orderTotal
	
		if(ToLowerCase(word2)!= "none" || ToLowerCase(word2) == "tofu" || ToLowerCase(word2) == "steak" || ToLowerCase(word2) == "chicken")
		orderTotal += 4.99; //add $4.99 to orderTotal
	
		cout<<"\nPick: Cilantro-Lime Brown, Cilantro-Lime White\n";
		getline(cin,pick2);
		
		if(pick2 != "none" || pick2 != "cilantro-lime brown" || pick2 != "cilantro-lime white")
		orderTotal += 1.50;//add $1.50 to orderTotal
		
		cout<<"\nPick: Queso, Sour Cream, Fresh Tomato Salsa\n";
		getline(cin,pick3);
		if(pick3 != "none" || pick3 != "queso" || pick3 != "sour cream" || pick3 != "fresh tomato salsa")
		orderTotal += 6.00;//add $6.00 to orderTotal
		orderTotal += (orderTotal*0.10);//Including 10% delivery charge
		
		cout<<"\nConfirm order (yes or no)\n";
		cout<<chipotle<<": ";
		
		if(word1 != "none")
		{	
			cout<<word1<<", ";
		}
		
		if(word2 != "none")
		{	
			cout<<word2<<", ";
		}	
		
		if(pick2 != "none")
		{
			cout<<pick2<<", ";
		}
		
		if(pick3 != "none")
		{
			cout<<pick3;
		}
		
		cout<<endl;
		cin>>option;
		
		if(option == "no")
		{
			return TotalMake;
		}
		
		CreateDelivery(orderTotal);
		TotalMake = TotalMake + orderTotal;
		return TotalMake;	
	}
	
	double getorderTotal()
	{
		return orderTotal;
	}
};

int main()
{
	int option = 0;
	double TotalMake = 23.353;
	
	ofstream o("GrandTotal.txt", ios::app);//Text file that stores grand total
	customer c;
	cout<<"\n~~Ronnie's Delivery Service~~\n";

	while(option != 3)
	{
		cout<<"\n--------------------------------------------\n";
		cout<<"\nPick from the following menu: ";
		cout<<"\n1. Customer";
		cout<<"\n2. Apply";
		cout<<"\n3. Exit";
		cout<<"\nEnter option: ";
		cin>>option;

		switch(option) //switch cases for options when ask for user input
		{
			case 1: c.placeOrder();
			break;
			
			case 2: c.apply();
			break;
			
			case 3: cout<<"\nExiting...\n";
			cout<<"Total Made: $"<<TotalMake<<endl;
			
			//Outputting value of TotalMake to file "GrandTotal.txt"
			o<<TotalMake;
			o<<"\n";
			o.close();
			exit(0);
			break;
			
			default: cout<< "please choose between 1-3"<<endl;
		}
	}
	
	f.close(); //close file from delivery people
	return 0;
}

