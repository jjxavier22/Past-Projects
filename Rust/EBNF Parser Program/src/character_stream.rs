//Jiss Xavier


use std::fs::File;
use std::io;
use std::convert::TryFrom;
use std::io::prelude::*;

#[derive(Debug)]


pub struct CharStream {
	read_in_contents: String, 
	index: i32,
	line_number: i32,
	contents : Vec<String>
}

impl CharStream {

	pub fn new(input: &str) -> CharStream {
		CharStream{
			read_in_contents : input.to_string(),
			index : 0,
			line_number: 1,
			contents: Vec::new()
		}
	}
	
	// Returns true if more characters are available, false otherwise.
	pub fn more_available(&self, k: i32) -> bool {
		if self.index + k >= self.read_in_contents.len().try_into().unwrap(){
			//println!("No more characters available to parse.");
			false
		}
		else{
			true
		}
	}

	pub fn get_line_number(&self) -> i32 {
		self.line_number
	}


	// Returns the next character without consuming it.
	// Returns None if no more characters are available. 
	pub fn peek_next_char(&self) -> Option<char> {
		if self.more_available(1) == true {
			//println!("This is the next character: {}", self.read_in_contents.chars().nth((self.index + 1) as usize).unwrap());
			Some(self.read_in_contents.chars().nth((self.index + 1) as usize).unwrap())
		} 
		else {
			None
		}	
	}

	
	
	// Returns the kth character ahead in the stream without consuming it.
	// peek_ahead_char(0) returns the same character as peek_next_char().
	// Returns None if no more characters are available at the position.
	// The input k cannot be negative.
	pub fn peek_ahead_char(&self, k: i32) -> Option<char> {
		if self.more_available(k) == true {
			//println!("This is the result {} character ahead: {}", k, self.read_in_contents.chars().nth((self.index + k) as usize).unwrap());
			Some(self.read_in_contents.chars().nth((self.index + k) as usize).unwrap())
		} 
		else {
			None
		}
	}

	
	// Returns the next character and consumes it.
	// Returns None if no more characters are available.
	pub fn get_next_char(&mut self) -> Option<char> {
		if self.more_available(0) == true {
			//println!("Consuming the character: {}", self.read_in_contents.chars().nth((self.index) as usize).unwrap());
			if self.read_in_contents.chars().nth((self.index) as usize).unwrap() == '\n'{
				self.line_number = self.line_number +1;
			}
			self.index = self.index + 1;
			Some(self.read_in_contents.chars().nth((self.index-1) as usize).unwrap())
		} 
		else {
			//println!("Reached the end of the file! ");
			None
		}
	}
}



