#include<iostream>
#include<fstream>

const int MAX_LEN_ROLE = 14;
const int MAX_LEN_COMMAND = 6;
const int TO_LOWER_CASE_CHANGE = 'a' - 'A';
const int TO_UPPER_CASE_CHANGE = 'A' - 'a';
const int TO_CHAR = '0';
const int TO_INTEGER = -'0';

bool isLowerCase(char c);
bool isUpperCase(char c);
int findTextLen(const char* text);
char* toLower(char* userInput);

void addNewMovieToDataBase(char* title, int year, char* genre, char* director, char* cast);


bool isLowerCase(char c) {
	return c >= 'a' && c <= 'z';
}

bool isUpperCase(char c) {
	return c >= 'A' && c <= 'Z';
}

int findTextLen(const char* text) {
	if (text == nullptr) {
		return -1;
	}

	int counter = 0;

	while (*text) {
		++counter;
		++text;
	}

	return counter;
}

char* toLower(char* userInput) {
	int textLen = findTextLen(userInput);

	for (size_t i = 0; i < textLen; ++i) {
		if (isUpperCase(userInput[i])) {
			userInput[i] += TO_LOWER_CASE_CHANGE;
		}
	}

	return userInput;
}

void addNewMovieToDataBase(char* title, int year, char* genre, char* director, char* cast) {

}

int main() {
	std::cout << "Hello and welcome to my IMDB!\nFirstly, you need to enter your role (user or administrator): ";
	char role[MAX_LEN_ROLE];
	std::cin.getline(role, MAX_LEN_ROLE);

	std::cout << "Now, as an " << toLower(role) << " you can choose one the the options below" << std::endl;
	std::cout << "by typing the digit in front of your chosen option : " << std::endl;

	char command[MAX_LEN_COMMAND];

	if (toLower(role) == "user") {
		
		std::cout << "1. Find movie by genre" << std::endl;
		std::cout << "2. Find movie by title" << std::endl;
		std::cout << "3. View all movies" << std::endl;
		std::cout << "4. Sort movies by title" << std::endl;
		std::cout << "5. Sort movies by rating" << std::endl;
		std::cout << "6. Rate a movie" << std::endl;
		std::cout << "7. Filter movies by rating" << std::endl;
		std::cout << "If you want to exit the program, press - \"CLOSE\"!" << std::endl;


	}
	else if (toLower(role) == "adminitrator") {
		std::cout << "1. Add a new movie" << std::endl;
		std::cout << "2. Find movie by genre" << std::endl;
		std::cout << "3. Find movie by title" << std::endl;
		std::cout << "4. View all movies" << std::endl;
		std::cout << "5. Change movie data" << std::endl;
		std::cout << "6. Delete movie" << std::endl;
		std::cout << "7. Sort movies by rating" << std::endl;
		std::cout << "8. Filter movies by rating" << std::endl;
		std::cout << "If you want to exit the program, press - \"CLOSE\"!" << std::endl;

	}
	else {
		std::cerr << "Invalid input - you have entered and invalid role! Please try again!" << std::endl;
		return 1;
	}

	return 0;
}