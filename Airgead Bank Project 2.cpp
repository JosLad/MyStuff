#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
using namespace std;
//Joshua Ladue Project 2
//CS210
// 4/2/23

class Bank {//bank class
private://private variables
	double i1;
	double m1;
	double n1;
	double a1;
	int y1;

public: //public functions for getters/setters
	void setInvestment(double i) {
		i1 = i;
	}
	double getInvestment() {
		return i1;
	}

	void setMonthlyPayment(double m) {
		m1 = m;
	}

	double getMonthlyPayment() {
		return m1;
	}

	void setInterest(double n) {
		n1 = n;
	}
	double getInterest() {
		return n1;
	}

	void setInterestNumber(double a) {
		a1 = a;
	}
	double getInterestNumber() {
		return a1;
	}

	void setYear(int y) {
		y1 = y;
	}
	int getYear() {
		return y1;
	}

	void printDetails(int yearIndex, double balance, double interestEarnedThisYear) {//prints the results of the calculations

		int yearPrint = yearIndex + 1;//year starts at 1, so it needs to move up by one.
		cout << fixed << setprecision(2) << yearPrint << "       " << balance << "        " << interestEarnedThisYear << "\n";
	}



	void mainMenu() { // the end where the program asks the user if they want to restart
		cout << "Would you like to restart?\n";
		cout << "y/n\n";
		char a = getMenuChoice();//calls the choice

		if (a == 'y') {
			cout << "Restarting \n";
			getParams();//if yes, it restarts and gets more user numbers
		}
		else if (a == 'n') {//if no, closes the program
			cout << "closing \n";
			exit(0);
		}
	}

	void getParams() {// the main choice function for the user
		double i;
		double m;
		double n;
		int y;
		int l = 1;

		while (l == 1) {// exception checks for inputs on all of the numbers, this one is for the initial investment.
			try {
				cout << "First investment.\n";
				cin >> i;
				if (cin.fail()) { // if the input is wrong, it will throw an excption and loop back to get another input
					l = 1;
					throw ios_base::failure("Invalid investment number");
				}
				else {//if it is correct, it moves on
					l = 0;
				}
			}

			catch (ios_base::failure) { //the catch that removes the incorrect input and loops back for another input
				cout << "Please try again.\n\n";
				cin.clear();
				cin.ignore();
			}
		}
		l = 1; //reinitializes l for more catch looping
		//everything under here in this function is just repeats of different exception checks for all of the inputs, so pretty much the same thing repeated
		while (l == 1) {
			try {
				cout << "Now the monthly payments.\n";
				cin >> m;
				if (cin.fail()) {
					l = 1;
					throw ios_base::failure("Invalid investment number");
				}
				else {
					l = 0;
				}
			}
			catch (ios_base::failure) {
				cout << "Please try again.\n\n";
				cin.clear();
				cin.ignore();
			}
		}
		l = 1;
		while (l == 1) {
			try {
				cout << "Now the interest rate.\n";
				cin >> n;
				if (cin.fail()) {
					l = 1;
					throw ios_base::failure("Invalid investment number");
				}
				else {
					l = 0;
				}
			}
			catch (ios_base::failure) {
				cout << "Please try again.\n\n";
				cin.clear();
				cin.ignore();
			}
		}
		l = 1;
		while (l == 1) {
			try {
				cout << "Lastly the amount of years.\n";
				cin >> y;
				if (cin.fail()) {
					l = 1;
					throw ios_base::failure("Invalid investment number");
				}
				else {
					l = 0;
				}
			}
			catch (ios_base::failure) {
				cout << "Please try again.\n\n";
				cin.clear();
				cin.ignore();
			}
		}
		l = 1;

		setInvestment(i);//sets investment
		setMonthlyPayment(m);//sets monthly payments
		setInterest(n);//sets the interest rate
		setYear(y);//sets the amount of years to calculate

	}

	char getMenuChoice() { //varifies the validity of the restart answers
		int choiceLoop = 1;
		char menuAnswer;
		while (choiceLoop == 1) {//loops to varify the input
			cin >> menuAnswer;
			if (!menuAnswer == 'y' or !menuAnswer == 'n') {
				choiceLoop = 1;
			}
			else {
				cout << "Please try again\n";
				choiceLoop = 0;
			}
		}

		return menuAnswer;

	}

	double calculateBalanceWithoutMonthlyDeposit(double initialInvestment, double interestRate, int numberOfYears) {//calculates the final balance without any monthly payments
		double newAmount = initialInvestment;
		double newInterest = interestRate / 100; //converts to decimal
		int i = 0; //loop variable

		for (i; i < numberOfYears; i++) { //uses the formula for compound interest
			double newAmount1 = newAmount;
			newAmount = pow((1 + newInterest / 12), 12) * newAmount;
			newAmount = round(newAmount * 100.0) / 100.0; //rounds to 2 decimal places
			double InterestNumber = newAmount - newAmount1; //amount generated from interest
			printDetails(i, newAmount, InterestNumber);//prints the details of each year investments
		}
		return (newAmount);//returns the final amount
	}
	double BalanceWithMonthlyDeposit(double initialInvestment, double monthlyDeposit, double interestRate, int numberOfYears) {//balance with monthly payments
		double newAmount = initialInvestment;
		double newInterest = interestRate / 100;//converts to decimal

		int i = 0;//loop variable

		for (i; i < numberOfYears; i++) {//uses the compound interest formula with monthly deposits to calculate the final total
			newAmount = newAmount;
			double newAmount1 = newAmount;
			double newAmount2 = newAmount * pow((1 + newInterest / 12), 12) + monthlyDeposit * (pow(1 + newInterest / 12, 12) - 1) / (newInterest / 12);
			newAmount = round(newAmount2 * 100.0) / 100.0;
			double InterestNumber = newAmount - newAmount1 - (monthlyDeposit * 12);//calculates the amount generated from interest. Harder to find with the monthly payments, but I got it
			printDetails(i, newAmount, InterestNumber);// prints the details of each year

		}
		return (newAmount);//returns the final amount


	}
};

int main() { //the main function of the program
	Bank bank;//bank class

	cout << "Input your starting funds, monthly payments, interest rate(in decimals), and the number of years to invest in.\n";//prompts user

	double i;//variables
	double m;
	double n;
	int y;
	int l = 1;

	bank.getParams();//calls the first user inputs

	int bankLoop = 1;//loop variable

	while (bankLoop == 1) {//loop for the functionality of the program
		cout << "\nBalance without monthly deposits: \nYears	Total	  Money from interest\n";
		bank.calculateBalanceWithoutMonthlyDeposit(bank.getInvestment(), bank.getInterest(), bank.getYear());//calcualtes and shows the balance without deposits
		cout << "\n";//formatting
		cout << "Balance with monthly deposits: \nYears	Total	  Money from interest\n";
		bank.BalanceWithMonthlyDeposit(bank.getInvestment(), bank.getMonthlyPayment(), bank.getInterest(), bank.getYear());// calcualtes and shows the balance with deposits
		cout << "\n";//formatting
		cin.clear();//clears the inputs so it can run again if restarted
		cin.ignore();
		bank.mainMenu();//prompts the user to restart or not
	}

	return (0);//end
}