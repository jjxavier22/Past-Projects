//Jiss Xavier

mod character_stream;
use character_stream::*;

mod token;
use token::*;
use std::env;
use std::io::Read;
use std::fs::File;


fn main() {
	scanner();

	//Code from Professor

	/*let tt = TokenType::OPERATOR;
	let token = Token::new("+".to_string(), tt, 2, 30);
	println!("text: {}", token.get_text());
	println!("token type: {}", token.get_type().as_str());
	println!("line numer: {}", token.get_line_number());
	println!("char position: {}", token.get_char_pos());*/
}

//https://turreta.com/2019/09/13/rust-how-to-check-if-a-string-is-numeric/
//function to check if the string is numeric
fn is_string_numeric(str: String) -> bool {
    for c in str.chars() {
        if !c.is_numeric() {
            return false;
        }
    }
    return true;
}

fn scanner() {
	//https://doc.rust-lang.org/book/ch12-01-accepting-command-line-arguments.html
	let args: Vec<String> = env::args().collect();

	//https://doc.rust-lang.org/std/fs/struct.File.html
	//reading off the command line
	let mut input_file = File::open(args[1].clone()).unwrap();
   	let mut contents = String::new();
   	input_file.read_to_string(&mut contents).unwrap();

	let mut character_stream = CharStream::new(&contents);
	//vector of tokens
	let mut token_vector = Vec::new();

	//stores the term being read in a string
	let mut temp = String::new();

//code to identify tokens from the source code

	//iterates through all the characters
	while character_stream.more_available(0) {

		//ensures there is a character ahead
		if character_stream.peek_ahead_char(1) != None {

			//checks if the character is alphanumeric
			if character_stream.peek_ahead_char(0).unwrap().is_alphanumeric() {
				//println!("{} is alphanumeric and has been popped", character_stream.peek_ahead_char(0).unwrap());
				temp.push(character_stream.get_next_char().unwrap());
				//println!("{} is what the string looks like.", temp);
			}
			
			//Checks for a negative sign rather than a subtraction operator
			else if character_stream.peek_ahead_char(0).unwrap() == '-' && character_stream.peek_ahead_char(1).unwrap().is_numeric(){
				temp.push(character_stream.get_next_char().unwrap());
			}

			else if (character_stream.peek_ahead_char(0).unwrap() == '<' && character_stream.peek_ahead_char(1).unwrap() == '=') ||
				(character_stream.peek_ahead_char(0).unwrap() == '>' && character_stream.peek_ahead_char(1).unwrap() == '=') ||
				(character_stream.peek_ahead_char(0).unwrap() == '=' && character_stream.peek_ahead_char(1).unwrap() == '=') ||
				(character_stream.peek_ahead_char(0).unwrap() == '!' && character_stream.peek_ahead_char(1).unwrap() == '=') {
					//checks to see if a term has been read
					if !temp.is_empty() {

						//tokenizes as an IntConstant and stores it in the vector of tokens
						if is_string_numeric(temp.clone()){
							println!("'{}' is an IntConstant on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::INTCONSTANT, character_stream.get_line_number()));
						}
						//tokenizes as a FloatConstant and stores it in the vector of tokens
						else if temp.contains(".") {
							println!("'{}' is a FloatConstant on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::FLOATCONSTANT, character_stream.get_line_number()));
						} 
						//tokenizes as a keyword and stores it in the vector of tokens
						else if temp == "unsigned" || temp == "char" || temp == "short" || temp == "int" || temp == "long" || 
						temp == "float" || temp == "double" || temp == "while" || temp == "if" || temp == "return" ||
						temp == "void" ||  temp == "main" {
							println!("'{}' is a keyword on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::KEYWORD, character_stream.get_line_number()));
						}
						
						//tokenizes as an identifier after making sure it is valid and stores it in the vector of tokens
						else {
							if !temp.chars().nth(0).unwrap().is_alphabetic() {
								println!("Error: Invalid identifier name '{}', identifier names can not begin with a number", temp);
								break;
							}
							else if temp.chars().all(char::is_alphanumeric) || temp.contains("_") {
								println!("'{}' is an identifier on line {}", temp.clone(), character_stream.get_line_number());
								token_vector.push(Token::new(temp.clone(),TokenType::VARIABLE, character_stream.get_line_number()));
							}
							
						}
						temp.clear();
					}
					temp.push(character_stream.get_next_char().unwrap());
					temp.push(character_stream.get_next_char().unwrap());
					println!("'{}' is an operator on line {}", temp, character_stream.get_line_number());
					token_vector.push(Token::new(temp.clone(),TokenType::OPERATOR, character_stream.get_line_number()));
					temp.clear();
				}
			
			//checks for operators
			else if character_stream.peek_ahead_char(0).unwrap() == '(' || character_stream.peek_ahead_char(0).unwrap() == ')' ||
				character_stream.peek_ahead_char(0).unwrap() == ',' || character_stream.peek_ahead_char(0).unwrap() == '{' ||
				character_stream.peek_ahead_char(0).unwrap() == '}' || character_stream.peek_ahead_char(0).unwrap() == '=' ||
				character_stream.peek_ahead_char(0).unwrap() == '<' || character_stream.peek_ahead_char(0).unwrap() == '>' ||
				character_stream.peek_ahead_char(0).unwrap() == '+' || character_stream.peek_ahead_char(0).unwrap() == '-' || 
				character_stream.peek_ahead_char(0).unwrap() == '*' || character_stream.peek_ahead_char(0).unwrap() == '/' || 
				character_stream.peek_ahead_char(0).unwrap() == ';'{
					
					//checks to see if a term has been read
					if !temp.is_empty() {

						//tokenizes as an IntConstant and stores it in the vector of tokens
						if is_string_numeric(temp.clone()){
							println!("'{}' is an IntConstant on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::INTCONSTANT, character_stream.get_line_number()));
						}
						//tokenizes as a FloatConstant and stores it in the vector of tokens
						else if temp.contains(".") {
							println!("'{}' is a FloatConstant on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::FLOATCONSTANT, character_stream.get_line_number()));
						} 
						//tokenizes as a keyword and stores it in the vector of tokens
						else if temp == "unsigned" || temp == "char" || temp == "short" || temp == "int" || temp == "long" || 
						temp == "float" || temp == "double" || temp == "while" || temp == "if" || temp == "return" ||
						temp == "void" ||  temp == "main" {
							println!("'{}' is a keyword on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::KEYWORD, character_stream.get_line_number()));
						}
						
						//tokenizes as an identifier after making sure it is valid and stores it in the vector of tokens
						else {
							if !temp.chars().nth(0).unwrap().is_alphabetic() {
								println!("Error: Invalid identifier name '{}', identifier names can not begin with a number", temp);
								break;
							}
							else if temp.chars().all(char::is_alphanumeric) || temp.contains("_") {
								println!("'{}' is an identifier on line {}", temp.clone(), character_stream.get_line_number());
								token_vector.push(Token::new(temp.clone(),TokenType::VARIABLE, character_stream.get_line_number()));
							}
							
						}
						temp.clear();
					}
					println!("'{}' is an operator on line {}", character_stream.peek_ahead_char(0).unwrap(), character_stream.get_line_number());
					token_vector.push(Token::new(character_stream.peek_ahead_char(0).unwrap().to_string(),TokenType::OPERATOR, character_stream.get_line_number()));
					character_stream.get_next_char();


			}

			//checks for white space
			else if character_stream.peek_ahead_char(0).unwrap() == '\n' || character_stream.peek_ahead_char(0).unwrap() == '\t' || 
				character_stream.peek_ahead_char(0).unwrap() == ' ' {
				//println!("{} is white space and has been popped", character_stream.peek_ahead_char(0).unwrap());
				character_stream.get_next_char();
				if !temp.is_empty() {
					//println!("{} is what the string looks like before clearing it.", temp.clone());
					if is_string_numeric(temp.clone()){
						println!("'{}' is an IntConstant on line {}", temp.clone(), character_stream.get_line_number());
						token_vector.push(Token::new(temp.clone(),TokenType::INTCONSTANT, character_stream.get_line_number()));
					}
					else if temp.contains(".") {
						println!("'{}' is a FloatConstant on line {}", temp.clone(), character_stream.get_line_number());
						token_vector.push(Token::new(temp.clone(),TokenType::FLOATCONSTANT, character_stream.get_line_number()));
					} 
					else if temp == "unsigned" || temp == "char" || temp == "short" || temp == "int" || temp == "long" || 
						temp == "float" || temp == "double" || temp == "while" || temp == "if" || temp == "return" ||
						temp == "void" ||  temp == "main" {
							println!("'{}' is a keyword on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::KEYWORD, character_stream.get_line_number()));
						}
						
					else {
						if !temp.chars().nth(0).unwrap().is_alphabetic() {
							println!("Error: Invalid identifier name '{}', identifier names can not begin with a number", temp);
							break;
						}
						else if temp.chars().all(char::is_alphanumeric) || temp.contains("_") {
							println!("'{}' is an identifier on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::VARIABLE, character_stream.get_line_number()));
						}
						
					}
					temp.clear();
				}
			}

			//supports identifier names written using '_' (Ex. syntax_parser)
			else if character_stream.peek_ahead_char(0).unwrap() == '_' {
				temp.push(character_stream.get_next_char().unwrap());
			}

			//supports float number (Ex. syntax_parser)
			else if character_stream.peek_ahead_char(0).unwrap() == '.' && character_stream.peek_ahead_char(1).unwrap().is_numeric() {
				temp.push(character_stream.get_next_char().unwrap());
			}

			else {
				println!("Syntax Error at character: {} on line {}", character_stream.peek_ahead_char(0).unwrap(), character_stream.get_line_number());
				break;
			}
		}
		else {

			//checks the last character of the file 
			if character_stream.peek_ahead_char(0).unwrap() == '}' {
				if !temp.is_empty() {
					//println!("{} is what the string looks like before clearing it.", temp.clone());
					if is_string_numeric(temp.clone()){
						println!("'{}' is an IntConstant on line {}", temp.clone(), character_stream.get_line_number());
						token_vector.push(Token::new(temp.clone(),TokenType::INTCONSTANT, character_stream.get_line_number()));
					}
					else if temp.contains(".") {
						println!("'{}' is a FloatConstant on line {}", temp.clone(), character_stream.get_line_number());
						token_vector.push(Token::new(temp.clone(),TokenType::FLOATCONSTANT, character_stream.get_line_number()));
					} 
					else if temp == "unsigned" || temp == "char" || temp == "short" || temp == "int" || temp == "long" || 
						temp == "float" || temp == "double" || temp == "while" || temp == "if" || temp == "return" ||
						temp == "void" ||  temp == "main" {
							println!("'{}' is a keyword on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::KEYWORD, character_stream.get_line_number()));
						}
						
					else {
						if !temp.chars().nth(0).unwrap().is_alphabetic() {
							println!("Error: Invalid identifier '{}', identifier names can not begin with a number", temp);
							break;
						}
						else if temp.chars().all(char::is_alphanumeric) || temp.contains("_") {
							println!("'{}' is an identifier on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::VARIABLE, character_stream.get_line_number()));
						}
						
					}
					temp.clear();
				}
					println!("'{}' is an operator on line {}", character_stream.peek_ahead_char(0).unwrap(), character_stream.get_line_number());
					token_vector.push(Token::new(character_stream.peek_ahead_char(0).unwrap().to_string(),TokenType::OPERATOR, character_stream.get_line_number()));
					character_stream.get_next_char();
					//push onto vector of Tokens

			}

			//ignores if the last character is white space
			else if character_stream.peek_ahead_char(0).unwrap() == ' ' || character_stream.peek_ahead_char(0).unwrap() == '\n' || 
				character_stream.peek_ahead_char(0).unwrap() == '\t' {
				character_stream.get_next_char();
				if !temp.is_empty() {
					//println!("{} is what the string looks like before clearing it.", temp.clone());
					if is_string_numeric(temp.clone()){
						println!("'{}' is an IntConstant on line {}", temp.clone(), character_stream.get_line_number());
						token_vector.push(Token::new(temp.clone(),TokenType::INTCONSTANT, character_stream.get_line_number()));
					}
					else if temp.contains(".") {
						println!("'{}' is a FloatConstant on line {}", temp.clone(), character_stream.get_line_number());
						token_vector.push(Token::new(temp.clone(),TokenType::FLOATCONSTANT, character_stream.get_line_number()));
					} 
					else if temp == "unsigned" || temp == "char" || temp == "short" || temp == "int" || temp == "long" || 
						temp == "float" || temp == "double" || temp == "while" || temp == "if" || temp == "return" ||
						temp == "void" ||  temp == "main" {
							println!("'{}' is a keyword on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::KEYWORD, character_stream.get_line_number()));
						}
						
					else {
						if !temp.chars().nth(0).unwrap().is_alphabetic() {
							println!("Error: Invalid identifier name '{}', identifier names can not begin with a number", temp);
							break;
						}
						else if temp.chars().all(char::is_alphanumeric) || temp.contains("_") {
							println!("'{}' is an identifier on line {}", temp.clone(), character_stream.get_line_number());
							token_vector.push(Token::new(temp.clone(),TokenType::VARIABLE, character_stream.get_line_number()));
						}
						
					}
					temp.clear();
				}
			}

			//throws an error if last value isn't one of the ones listed above
			else {
				println!("Error: Can't end the code with {}", character_stream.peek_ahead_char(0).unwrap());
				break;
			}

			break;
		}

	}
	
}
