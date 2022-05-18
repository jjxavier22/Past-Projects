//Jiss Xavier


#include "rpn.h"

int main() {

	//Provided below are test cases used to ensure the program works as outlined

	string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"}; 
	//string test[] = {"5", "3", "+", "6", "2", "/", "*", "3", "5", "*", "+"}; 
	//string test[] = {"1", "2", "3", "+", "4", "5", "6", "*", "/", "7", ">", "+", "8", "9", "10", "<", "-", "-", "+", "/", "*"}; 
	//string test[] = {"10", "5", "-1.5", "+", "2.5", "3.0", "**", "-", "+"}; 
	//string test[] = {"2", "3", "/", ">"};
	//string test[] = {"0", "0", "**"};
	//string test[] = {"-10", "0.5", "**"};
	//string test[] = {"1", "2", "+", "-"};
	//string test[] = {"4.2", "1.6", "-", "<", ">"};
	//string test[] = {"4.2", "1.6", "-", "<", ">", "/"};
	//string test[] = {"4.2", "1.6", "+", "0", "/"};
	//string test[] = {"12", "5.0", "3","+"};


	int n = 9;
	//int n = 11;
	//int n = 21;
	//int n = 9;
	//int n = 4;
	//int n = 3;
	//int n = 3;
	//int n = 4;
	//int n = 5;
	//int n = 6;
	//int n = 5;
	//int n = 4;

	double result = rpn(test, n);
	cout << "The final answer is: " << result << endl;
}
