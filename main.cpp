//DONE BY GROUP 5
//MEMEBERS : ADELINE , RAHUL BIJU , SWAROOP , CAREN , SNEHA


//Note : The number of seats available resets everytime the code is ran using ./a.out .
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
//#include <termios.h>
#include <unistd.h>

using namespace std;

class FlightDetails {

	public:

	string AirIndia[10] ={ "A012" , "A175" , "A570" , "A876", "A350" , "A164" , "A561" , "A165" , "A527" , "A408"};
	string s_d[10] = {"COK-DEL" , "MAA-BLR" , "COK-MAA" , "BOM-CCU" , "TRV-IXJ" , "DEL-COK" , "BLR-MAA" , "MAA-COK" , "CCU-BOM" , "IXJ-TRV"};
	int price_range[10] =  {25000, 10000 , 15000 , 20000 , 30000 , 25000 , 10000 , 15000 , 20000 ,30000 };
	int seats[10] = {149,149,149,149,149,149,149,149,149,149};

};

class Airline_Services {

	public:
	string Flightname , source , destination;
	long int seats_booked = 0, flightIndex=0,price;

};

class customer : public Airline_Services {

	public:

	string name;
	int age , ph_num , id;
	char gender;
	
	public:
	FlightDetails plane;
	int i;
	
	void personalInfo() {
	
		cout<<"\nEnter your name : ";
		cin>>name;
		cout<<"Enter your age : ";
		cin>>age;
		cout<<"Enter your gender (F/M) : ";
		cin>>gender;
		cout<<"Enter your Phone number : ";
		cin>>ph_num;
	
	}
	
	void Requestinfo(string username) {
		ofstream outfile("DoNotOpen.txt", ios::app);
		if (!outfile) {
			cout << "Error opening file." << endl;
			return;
		}

		cout <<"The ongoing flights of AirIndia are : \n";

		for(i=0;i<10;i++) {
			cout<<i+1<<". "<<plane.AirIndia[i]<<"\t"<<plane.s_d[i]<<"\t"<<plane.price_range[i]<<endl;;
		}
		cout<<"\nChoose your flightnumber : ";
		cin>>flightIndex;

		flightIndex-=1;
		Flightname = plane.AirIndia[flightIndex];
		source = plane.s_d[flightIndex].substr(0,3);
		destination = plane.s_d[flightIndex].substr(4,3);
		cout<<"\nNumber of seats available for "<<Flightname<< " : "<<plane.seats[flightIndex];
		cout<<"\nTotal number of seats you would like to book : ";
		cin>>seats_booked;
		if (seats_booked > plane.seats[flightIndex]) {
			cout<<"Excess amount of seats booked! please try again."<<endl;
			return;
		}

		plane.seats[flightIndex] -= seats_booked;
		price = plane.price_range[flightIndex]*seats_booked;

		outfile<<username<<"-Flightname : "<<Flightname<<", From : "<<source<<" To : "<<destination<<" , Total Price : "<<price<<" , seats booked : "<<seats_booked<<endl;
		outfile.close();
	}
};

class security{
	public:
	char username[10] , password[10];
	bool hasAcc = false;
	int i ,len=0;
	string mailaddress ,tp , matchingpassword ,getusernameMatch , details;
	customer cust;
	FlightDetails plane;

	int addData() {
		ofstream outfile("Secret.txt", ios::app);
		ofstream anotheroutfile("Details.txt", ios::app);
		ifstream infile("Secret.txt");
		ifstream anotherinfile("Details.txt");

		if (!outfile) {
			cout << "Error opening file." << endl;
			return 2;
		}
		if (!anotheroutfile) {
			cout << "Error opening file." << endl;
			return 2;
		}
		if (!anotherinfile) {
			cout << "Error opening file." << endl;
			return 2;
		}
		if (!infile) {
		cout << "Error opening file." << endl;
		return 2;
		}

			//sign up
		cout<<"\t Sign Up\n";
		cout<<"\nEnter your username : ";
		cin>>username;
		while(getline(infile, tp)){ 

			for(i =0 ; i<tp.length()+1 ; i++) {
				if (tp[i] == '-') {
					len = i;
				}
			}
			getusernameMatch = tp.substr(0 , len);
			
			if (getusernameMatch == username) {
				cout<<"\nYou already have an account!";
				hasAcc = true;
				break;
			}
		}
		if (hasAcc) {
			matchingpassword = tp.substr(len+1 , tp.length() - (len+1));
			struct termios old_settings, new_settings;
			tcgetattr(STDIN_FILENO, &old_settings);
			new_settings = old_settings;
			new_settings.c_lflag &= ~(ICANON | ECHO);
			tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
			cout<<"\nEnter your password : ";
			cin>>password;
			tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
			if (password == matchingpassword) {
				cout <<"\nLogin Sucessfully! Please confirm your details :"<<endl;
				printbill('p');

			}
			else {
				cout<<"\nIncorrect password!!!";
				return 2;
			}
			
		}
		else {
			struct termios old_settings, new_settings;
			tcgetattr(STDIN_FILENO, &old_settings);
			new_settings = old_settings;
			new_settings.c_lflag &= ~(ICANON | ECHO);
			tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
			cout<<"\nCreate a password : ";
			cin>>password;
			tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
			cout<<"\nEnter your Email Address : ";
			cin>>mailaddress;
			cust.personalInfo();
			outfile<<username << "-" <<password<<endl;
			anotheroutfile<<username<<"_Email :"<<mailaddress<<" , Name :"<<cust.name<<" , Age : "<<cust.age<<" , Gender(f/m) : "<<cust.gender<<" , Phone number : "<<cust.ph_num<<endl;

		}
		outfile.close();
		anotheroutfile.close();	
		infile.close();
		anotherinfile.close();

		return 0;
	}
	//case 1 function;
	void addFlightData() {
		cust.Requestinfo(username);
	}
	//case 2 function;
	void editBooking() {
		ifstream detailsinfile("Details.txt");

		int choice ;
		bool found = false , isnumber = false;
		string newstr , anothernewstr;

		if (!detailsinfile) {
        	cout << "Error opening file." << endl;
        	return;
    	}

		cout<<"\nWhat would you like to edit? \n1.Email \n2.Phone number "<<endl;
		cin>>choice;
        switch (choice) {
            case 1:
                cout<<"Enter your new email : ";
                cin>>mailaddress;
                break;
            case 2:
                cout<<"Enter your new phone number : ";
				isnumber = true;
                cin>>cust.ph_num;
                break;
            default:
                cout<<"Invalid choice! "<<endl;
                break;
        }

		ofstream anothertempFile("temp3.txt");

		while(getline(detailsinfile, tp)){ 
			for(i =0 ; i<tp.length()+1 ; i++) {
				if (tp[i] == '_') {
					len = i;
				}
			}
			getusernameMatch = tp.substr(0 , len);
			
			for(i =0 ; i<tp.length()+1 ; i++) {
				if (isnumber) {
					if (tp[i] == 'n' && tp[i+1] == 'u') {
						len = i+8;
					}
				}
				else {
					if (tp[i] == 'E' && tp[i+1] == 'm') {
						len = i+6;
					}
					if (tp[i] == 'N' && tp[i+1] == 'a') {
						choice = i;
					}
				}
				
			}
			if (username == getusernameMatch) {
				found = true;
				if (isnumber) {
					newstr = tp.substr(0 , len);
					anothertempFile<<newstr<<cust.ph_num<<endl;
				}
				else {
					newstr = tp.substr(0,len);
					anothernewstr = tp.substr(choice , tp.length() - (choice +1));
					anothertempFile<<newstr<<mailaddress<<" , "<<anothernewstr;
				}	
				continue;
			}
			anothertempFile<<tp<<endl;
		}

		detailsinfile.close();
		anothertempFile.close();
		if (!found) {
			cout << "Details not found." << endl;
			remove("temp3.txt");
		} else {
			remove("Details.txt");
			rename("temp3.txt", "Details.txt");
			cout << "Details Edited Successfully!" << endl;
		}
	}

	//case 3 function;
	void searchBooking() {
		string name;
		int limit;
		cout<<"Enter your name to search your booking info : ";
		cin>>name;
		ifstream detailsinfile("Details.txt");

		while(getline(detailsinfile, tp)){ 
			for(i =0 ; i<tp.length()+1 ; i++) {
				if (tp[i] == 'N' && tp[i+1] == 'a') {
					len = i+6;
				}
				if (tp[i] == 'A' && tp[i+1] == 'g') {
					limit = i-4;
				}
			}
			cust.name = tp.substr(len , tp.length() - (len) - limit +1);
			
			if (cust.name == name) {
				for(i =0 ; i<tp.length()+1 ; i++) {
					if (tp[i] == '_') {
						len = i;
					}
				}
				getusernameMatch = tp.substr(0 , len);
				for (i=0 ; i <getusernameMatch.length()+1 ; i++) {
					username[i] = getusernameMatch[i];
				}
				cout<<"Found user with name "<<name;
				printbill('a');
				break;
			}
		}

		detailsinfile.close();

	}

	//case 4 function;
	void deleteBooking() {
		ifstream infile("DoNotOpen.txt");
		ifstream secretinfile("Secret.txt");
		ifstream detailsinfile("Details.txt");

		int choice;
		string  flightname , anotherflight;
    	if (!infile) {
        	cout << "Error opening file." << endl;
        	return;
    	}
		if (!secretinfile) {
        	cout << "Error opening file." << endl;
        	return;
    	}
		if (!detailsinfile) {
        	cout << "Error opening file." << endl;
        	return;
    	}

		cout<<"Enter flight number to cancel booking : "<<endl;
		for(i=0;i<10;i++) {
			cout<<i+1<<". "<<plane.AirIndia[i]<<endl;;
		}
		cin>>choice;
		flightname = plane.AirIndia[choice-1];
		bool found = false;
		ofstream tempFile("temp.txt");
		ofstream newtempFile("temp2.txt");
		ofstream anothertempFile("temp3.txt");

		while(getline(infile, tp)){ 
			for(i =0 ; i<tp.length()+1 ; i++) {
				if (tp[i] == 'A') {
					len = i;
				}
			}
			anotherflight = tp.substr(len , 4);
			for(i =0 ; i<tp.length()+1 ; i++) {
				if (tp[i] == '-') {
					len = i;
				}
			}
			getusernameMatch = tp.substr(0 , len);

			if (flightname == anotherflight && getusernameMatch == username) {
				found = true;
				continue;
			}
			tempFile<<tp<<endl;
		}
		while(getline(secretinfile, tp)){ 
			for(i =0 ; i<tp.length()+1 ; i++) {
				if (tp[i] == '-') {
					len = i;
				}
			}
			getusernameMatch = tp.substr(0 , len);
			if (username == getusernameMatch) {
				continue;
			}
			newtempFile<<tp<<endl;
		}
		while(getline(detailsinfile, tp)){ 
			for(i =0 ; i<tp.length()+1 ; i++) {
				if (tp[i] == '_') {
					len = i;
				}
			}
			getusernameMatch = tp.substr(0 , len);
			if (username == getusernameMatch) {
				continue;
			}
			anothertempFile<<tp<<endl;
		}

		infile.close();
		secretinfile.close();
		detailsinfile.close();
		tempFile.close();
		anothertempFile.close();
		newtempFile.close();
		if (!found) {
			cout << "Booking not found." << endl;
			remove("temp.txt");
			remove("temp2.txt");
			remove("temp3.txt");

		} else {
			remove("DoNotOpen.txt");
			remove("Secret.txt");
			remove("Details.txt");

			rename("temp.txt", "DoNotOpen.txt");
			rename("temp2.txt", "Secret.txt");
			rename("temp3.txt", "Details.txt");
			cout << "Booking Cancelled Successfully!" << endl;
		}
	}

	//case 5 functions;
	void printbill(char infotype) {
		ifstream anotherinfile("Details.txt");
		ifstream infile("DoNotOpen.txt");
		if (!infile) {
		cout << "Error opening file." << endl;
		return;
		}
		if (!anotherinfile) {
		cout << "Error opening file." << endl;
		return;
		}

		if (infotype == 'p') { // prints only personal info
			while(getline(anotherinfile, tp)){ 
				for(i =0 ; i<tp.length()+1 ; i++) {
					if (tp[i] == '_') {
						len = i;
					}
				}
				getusernameMatch = tp.substr(0 , len);
				if (username == getusernameMatch) {
					break;
				}

			}
			cout<<"aaaa";
			details = tp.substr(len+1 , tp.length() - (len+2));
			cout<<details<<endl;
		}
		else if (infotype == 'a') { // prints all info
			printbill('p');
			while(getline(infile, tp)){ 
				for(i =0 ; i<tp.length()+1 ; i++) {
					if (tp[i] == '-') {
						len = i;
					}
				}
				getusernameMatch = tp.substr(0 , len);
				if (username == getusernameMatch) {
					break;
				}
			}
			details = tp.substr(len+1 , tp.length() - (len+2));
			cout<<details<<endl;
		}
		infile.close();
		anotherinfile.close();
	}

};

int main() {

	security safe;
	char option = 'n';
	int choice , returned;

	do{
		returned = safe.addData();
		if (returned == 0) {
			cout<<"\n\tFlight Management for AirIndia\n";
			cout<<"\n1.Book Flights \n2.Edit Booking \n3.Search Booking \n4.Cancel Booking \n5.Display Lastest Booking \n6.Exit \n";
			cout<<"Enter your choice : ";
			cin>>choice;
			switch (choice)
			{
			case 1:
				safe.addFlightData();
				break;
			case 2:
				safe.editBooking();
				break;
			case 3:
				safe.searchBooking();
				break;
			case 4:
				safe.deleteBooking();
				break;
			case 5:
				safe.printbill('a');
				break;
			case 6:
				cout<<"\nLogout Successful."<<endl;
				exit(0);
				break;

			default:
				cout<<"\nThe choice you have entered is incorrect. Please enter a valid option\n";
				break;
			}
		}
		cout<<"\nDo you want to continue? (y/n) : ";
		cin>>option;
	}while(option == 'y');

	
	return 0;

}
