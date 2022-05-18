//Jiss Xavier


#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <cmath>
using namespace std;

//function to check whether you are looking at an operator
bool checkOperator(string input1){
	if(strcmp(input1.c_str(), "+") == 0){
        return true;
    }
	if(strcmp(input1.c_str(), "-") == 0){
        return true;
    }
	if(strcmp(input1.c_str(), "*") == 0){
        return true;
    }
	if(strcmp(input1.c_str(), "/") == 0){
        return true;
    }
	if(strcmp(input1.c_str(), "**") == 0){
        return true;
    }
	if(strcmp(input1.c_str(), "<") == 0){
        return true;
    }
	if(strcmp(input1.c_str(), ">") == 0){
        return true;
    }
	else{
		return false;
	}
}

//function that does the RPN computation using the stack values
double computation(string input1, double operand1, double operand2){
	if(strcmp(input1.c_str(), "+") == 0){
        return operand1 + operand2;
    }
	if(strcmp(input1.c_str(), "-") == 0){
        return operand1 - operand2;
    }
	if(strcmp(input1.c_str(), "*") == 0){
        return operand1 * operand2;
    }
	if(strcmp(input1.c_str(), "/") == 0){
		//catches divison by 0 error
		if(operand2 == 0){
			cerr << "Invalid Expression (Division by 0 Error) \n";
			exit(1);
		}
        return operand1 / operand2;
    }
	if(strcmp(input1.c_str(), "**") == 0){
		//catches 0^0 undefined expression
		if(operand1 == 0 && operand2 == 0){
			cerr << "Invalid Expression (0^0 Undefined Error) \n";
			exit(1);
		}
		//catches exponents resulting in imaginary numbers
		else if (operand1 < 0 && operand2 < 1) {
			cerr << "Invalid Expression (Error Due to Imaginary Result) \n";
			exit(1);
		}
		else {
			return pow(operand1, operand2);
		}
    }
	else{
		return INT_MAX;
	}
}

//function used to print the optional output
void printOptionalResult(string output){
	int length = output.length();
	int tabCount = 0;
	for (int i = 0; i < length; i++) {
		
		//enters new line in the places needed
		if(output[i] == ' '){
			output[i] = '\n';
		}

		//enters new line and determines where indentation is needed
		if (output[i] == '+' || output[i] == '-' || output[i] == '*' || output[i] == '/' || output[i] == '<' || output[i] == '>' || (output[i] == '*' && output[i+1] == '*')){
			output.insert(i+1, "\n");
			length++;
			tabCount++;
		}

		//reduces the indentation for a ')'
		if(output[i] == ')'){
			tabCount--;
			output[i-1] = ')';
			output[i] = ' ';
		}

		//increases indentation as needed
		else if(output[i] == '\n'){
			for(int j= 0; j < tabCount; j++){
				output.insert(i+1, "\t");
				length++;
			}
		}

	}
	//prints the calculated optional output
	cout << output << endl;  
}

double rpn(string *strs, int n) {

	double result = 0.0;
	stack<double> doubleStack;
	//stack used for the optional output
	stack<string> stringStack;

	for(int i=0; i < n; i++){
		//cout<< strs[i] << '\n';
		//cout << "Is it an operator? " << checkOperator(strs[i]) << "\n\n\n";

		//We are looking at an operator, so we will attempt to make a computation
		if(checkOperator(strs[i]) == 1){

			//Checks for flooring
			if(strcmp(strs[i].c_str(), "<") == 0){

				//ensures valid input for computation
				if(doubleStack.size() <= 0){
					cerr << "Please enter a valid expression in Reverse Polish Notation." << endl;
					exit(1);
				}

				//pops the value needed and floors it
				double operand1 = doubleStack.top();
				string operand1String = stringStack.top();
				stringStack.pop();
        		doubleStack.pop();
				double result = floor(operand1);
				string stringResult = "(" + strs[i] + " " + operand1String + " )";
				
				//pushes the results back on to the stack
				doubleStack.push(result);
				stringStack.push(stringResult);

			}
			//Checks for ceiling
			else if(strcmp(strs[i].c_str(), ">") == 0){

				//ensures valid input for computation
				if(doubleStack.size() <= 0){
					cerr << "Please enter a valid expression in Reverse Polish Notation." << endl;
					exit(1);
				}

				//pops the value needed and ceils it
				double operand1 = doubleStack.top();
				string operand1String = stringStack.top();
        		doubleStack.pop();
				stringStack.pop();
				double result = ceil(operand1);
				string stringResult = "(" + strs[i] + " " + operand1String + " )";
				
				//pushes the results back on to the stack
				doubleStack.push(result);
				stringStack.push(stringResult);

			}
			//Normal Computation
			else {

				//Checks for Valid Reverse Polish Notation
				if(doubleStack.size() <= 1){
					cerr << "Please enter a valid expression in Reverse Polish Notation." << endl;
					exit(1);
				}

				//pops the values needed and finds the calculation
				double operand2 = doubleStack.top();
				string operand2String = stringStack.top();
         		doubleStack.pop();
				stringStack.pop();
        		double operand1 = doubleStack.top();
				string operand1String = stringStack.top();
        		doubleStack.pop();
				stringStack.pop();
				string stringResult = "(" + strs[i] + operand1String + " " + operand2String + " " + ")";
				double result = computation(strs[i], operand1, operand2);
         		
				//The results are pushed back on to the stack
				doubleStack.push(result);
				stringStack.push(stringResult);
			}
		}
		else {
			//checks to see if the input provided to the function is valid
			try {
				double operand = stod(strs[i]);
				doubleStack.push(operand);
				stringStack.push(strs[i]);
			}
			catch (...)  {
        		cerr << "The input is invalid \n";
				exit(1);
    		}

		}
	}

	// Calculate the result here
	// You may add extra functions if needed
	
	//Provides warning when too many numbers and too few operators are provided.
	if(doubleStack.size() > 1){
		cout << "Warning: Excessive Numbers were provided." << endl;
	}

	//Asks for user input to determine whether the optional output should be displayed
	string userInput = "";
	cout << "Please enter '-l' to display optional output (Enter any other key or value to skip): ";
	cin >> userInput;

	if(strcmp(userInput.c_str(), "-l") == 0){
		printOptionalResult(stringStack.top());
		result = doubleStack.top();
		return result;
	}
	else {
		result = doubleStack.top();
		return result;
	}
		
}


