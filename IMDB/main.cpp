/*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Nadya Radeva
* @idnumber 1MI0600454
* @compiler VC
*
* <This file consists of all functions including main.>
*
*/

#include<iostream>
#include<fstream>

const int MAX_LEN_TEXT_FILE_NAME = 20;
const int MAX_LEN_ROLE = 15;
const int MAX_LEN_COMMAND = 7;
const int MAX_LEN_OPTION = 9;
const int TO_LOWER_CASE_CHANGE = 'a' - 'A';
const int TO_UPPER_CASE_CHANGE = 'A' - 'a';
const int TO_CHAR = '0';
const int TO_INTEGER = -'0';
const int DISTANCE_BETWEEN_MOVIE_PARAMETERS = 3; // " | "
const char* DELIMITER = " | ";
const int MAX_NUMBER_OF_DELIMITERS = 6;
const double DEFAULT_RATING = 5.0;
const int MAX_LEN_GENRE = 400;
const int MAX_LEN_MOVIE_TITLES = 1000;
const int MAX_LEN_MOVIE_DIRECTOR = 500;
const int MAX_LEN_MOVIE_CAST = 4000;
const double MIN_RATING = 0.0;
const double MAX_RATING = 10.0;
const int MAX_LEN_RATING = 4;
const int MAX_LEN_LINE = MAX_LEN_GENRE + MAX_LEN_GENRE + MAX_LEN_MOVIE_DIRECTOR + MAX_LEN_MOVIE_CAST + 2 + 10 + 5; // MAX_LEN_MOVIE_TITLES + MAX_LEN_MOVIE_DIRECTOR + MAX_LEN_MOVIE_CAST + RATING (MAX - 2 digits) + 10 spaces + 5 lines

//Base Functions
//Simple checks
bool isLetter(char ch);
bool isDigit(char ch);
bool isLowerCase(char ch);
bool isUpperCase(char ch);
char toLowerCaseChar(char ch);
char toUpperCaseChar(char ch);

int findTextLen(const char* text);
int countDigitsInNumber(int number);
int reverseYear(int year);

//Functions that handle the release year and turn it into char string
int countDigitsInNumber(int year);
int reverseYear(int year);
char* yearToChar(int year);
char* yearToChar(int year);

//Text modifications and more complicated checks
char* toLower(const char* userInput);
char* toUpper(char* userInput);
char* modifyInputText(const char* inputText);
bool isTitleMatch(const char* str, const char* subStr);

//Functions handling the rating
char* turnIntegerRatingToChar(int rating);
char* turnDoubleRatingToChar(double rating);

//String arrays base functions
int myStrCmp(const char* str1, const char* str2);
char* myStrStr(const char* str1, const char* str2);

//Function that replaces the current title of a movie with a new one (in line)
bool updateTitleInLine(char* line, const char* oldTitle, const char* newTitle);
//Function that replaces the current release year of movie with a new one (in line)
bool updateReleaseYearInLine(char* line, int newReleaseYear);
//Function that replaces the current genre of a movie with a new one (in line)
bool updateGenreInLine(char* line, const char* newGenre);
//Function that replaces the current director of a movie with a new one (in line)
bool updateDirectorInLine(char* line, const char* newDirector);
//Function that replaces the current director of a movie with a new one (in line)
bool updateMovieCastInLine(char* line, const char* newCast);
//Function that replaces the current rating of a movie with a new one (in line)
bool updateRatingInLine(char* line, double newRating);
//Function that counts how many lines there are in the text file and how many movies there are in the database
int countLinesInFile(const char* fileName);
//Function that copies the contents of a string into another one
void myStrCpy(const char* source, char* dest);

//Main Functions
//Function that adds a new movie to the database
int addNewMovieToDataBase(const char* title, int year, const char* genre, const char* director, const char* cast, const char* fileName);
//Function that finds movie by a genre inputted by the user/admin
int findMovieByGenre(const char* genre, const char* fileName);
//Function that finds movie by a title inputted by the user/admin
int findMovieByTitle(const char* title, const char* fileName);
//Function that shows all movies in the database
int showAllMoviesInDatabase(const char* fileName);
//Function that updates the title of a chosen movie
bool updateMovieTitle(const char* oldTitle, const char* newTitle, const char* fileName);
//Function that updates the release year of a chosen movie
bool updateReleaseYear(const char* title, int newReleaseYear, const char* fileName);
//Function that updates the genre of a chosen movie
bool updateMovieGenre(const char* title, const char* newGenre, const char* fileName);
//Function that updates the director of a chosen movie
bool updateMovieDirector(const char* title, const char* newDirector, const char* fileName);
//Function that updates the cast of a chosen movie
bool updateMovieCast(const char* title, const char* newCast, const char* fileName);
//Function that updates the rating of a chosen movie
void copyNewRating(const char* ratingStr, char* line, int startPos, int newLen);
bool updateMovieRating(const char* title, double newRating, const char* fileName);
//Sort movies by title
char** readMoviesFromFile(const char* fileName, int& movieCount);
void sortMoviesByTitle(char** movies, int movieCount);
//Sort movies by rating
double extractRating(const char* movieData);
void sortMoviesByRating(char** movies, int movieCount);
//Filter movies rating given by the user
void printMoviesByRating(std::ifstream& file, double userRating);
void filterMoviesByRating(const char* filename, double userRating);
//Delete movie
std::ofstream createTempFile();
bool deleteMovie(std::ifstream& inFile, std::ofstream& outFile, const char* title);
bool replaceOriginalFile(const char* originalFileName, const char* tempFileName);
int deleteMovieByTitle(const char* title, const char* fileName);
//Rate movies
int findMovieIndex(const char* movieTitle, const char* fileName);
void appendRating(const char* ratingsFile, int movieIndex, int newRating);
double calculateAverageRating(const char* ratingsFile, int movieIndex);
int findRatingStartPos(char* line);
bool updateAverageRatingInLine(char* line, double newRating);
bool updateAverageMovieRating(const char* title, double newRating, const char* fileName);
bool findMovieTitleLine(const char* title, const char* fileName, char* line);
void rateMovie(const char* movieTitle, int newRating, const char* fileName, const char* ratingsFile);

//Function that checks if a character is a letter
bool isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

//Function that checks if a character is a digit
bool isDigit(char ch) {
	return (ch >= '0' && ch <= '9');
}

//Function that checks if a letter is lower case
bool isLowerCase(char ch) {
	return ch >= 'a' && ch <= 'z';
}

//Function that checks if a letter is upper case
bool isUpperCase(char ch) {
	return ch >= 'A' && ch <= 'Z';
}

//Function that turns a single character lower case
char toLowerCaseChar(char ch) {
	return (ch >= 'A' && ch <= 'Z') ? ch + TO_LOWER_CASE_CHANGE : ch;
}

//Function that turns a single character upper case
char toUpperCaseChar(char ch) {
	return (ch >= 'a' && ch <= 'z') ? ch + TO_UPPER_CASE_CHANGE : ch;
}

//Function that finds the length of the lines in the text file
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

//Functions that handle the release year and turn it into a char array. It is used for the rate changing segments.
//This function counts the digits in the release year
int countDigitsInNumber(int number) {
	int digitsCounter = 0;

	while (number != 0) {
		int temp = number % 10;
		number /= 10;
		digitsCounter++;
	}

	return digitsCounter;
}

//This function reverses the release year
int reverseYear(int year) {
	int reversed = 0;
	while (year > 0) {
		int digit = year % 10;
		reversed = reversed * 10 + digit;
		year /= 10;
	}
	return reversed;
}

//This function takes the reversed year and turns it a string array with the right order of numbers
char* yearToChar(int year) {
	int digits = countDigitsInNumber(year);
	char* yearStr = new char[digits + 1];
	int reversedYear = reverseYear(year);

	for (size_t i = 0; i < digits; ++i) {
		yearStr[i] = reversedYear % 10 + TO_CHAR;
		reversedYear /= 10;
	}
	yearStr[digits] = '\0';

	return yearStr;
}

//Function that takes the rating and it turns it into a string array
char* turnIntegerRatingToChar(int rating) {
	int numDigits = (rating >= 0 && rating <= 9) ? 1 : 2;
	char* ratingStr = new char[numDigits + 1];

	if (rating >= 0 && rating <= 9) {
		ratingStr[0] = rating + TO_CHAR;
		ratingStr[1] = '\0';
	}
	else {
		ratingStr[0] = (rating / 10) + TO_CHAR;
		ratingStr[1] = (rating % 10) + TO_CHAR;
		ratingStr[2] = '\0';
	}

	return ratingStr;
}

//Function that takes the rating but with decimal numbers and turns it into a string array
//with a decimal point in between the integer and the decimal part.
char* turnDoubleRatingToChar(double rating) {
	char* ratingStr = new char[MAX_LEN_RATING + 1];

	int integerPart = (int)rating;
	int decimalPart = (int)((rating - integerPart) * 10);

	if (integerPart < 10) {
		ratingStr[0] = integerPart + TO_CHAR;
	}
	else {
		ratingStr[0] = '1';
	}

	ratingStr[1] = '.';
	ratingStr[2] = decimalPart + TO_CHAR;
	ratingStr[3] = '\0';

	return ratingStr;
}

//Function that turns all letters in a string array lower case
char* toLower(const char* userInput) {
	int textLen = findTextLen(userInput);
	char* newText = new char[textLen + 1];

	for (size_t i = 0; i < textLen; ++i) {
		newText[i] = toLowerCaseChar(userInput[i]);
	}

	newText[textLen] = '\0';

	return newText;
}

//Function that turns all letters in a string array upper case
char* toUpper(char* userInput) {
	int textLen = findTextLen(userInput);

	for (size_t i = 0; i < textLen; ++i) {
		userInput[i] = toUpperCaseChar(userInput[i]);
	}

	return userInput;
}

//Function that changes the first letter of the genre, inputed by the user, by turning it in upper case
char* modifyInputText(const char* inputText) {
	int inputTextLen = findTextLen(inputText);
	char* modifiedText = new char[inputTextLen + 1];
	bool inWord = false;

	for (size_t i = 0; i < inputTextLen; ++i) {
		if (isLetter(inputText[i])) {
			if (!inWord) {
				if (isLowerCase(inputText[i])) {
					modifiedText[i] = inputText[i] + TO_UPPER_CASE_CHANGE;
				}
				else {
					modifiedText[i] = inputText[i];
				}
				inWord = true;
			}
			else {
				modifiedText[i] = inputText[i];
			}
		}
		else {
			inWord = false;
			modifiedText[i] = inputText[i];
		}
	}

	modifiedText[inputTextLen] = '\0';
	return modifiedText;
}

//Function checking if the user input matches a part of the title
bool isTitleMatch(const char* str, const char* subStr) {
	if (!str || !subStr) {
		return false;
	}

	int strLen = findTextLen(str);
	int subStrLen = findTextLen(subStr);

	int startPos = 0;
	while (str[startPos] != '|' && str[startPos] != '\0') {
		startPos++;
	}

	for (size_t i = startPos; i <= strLen - subStrLen; ++i) {
		bool isMatchFound = true;
		for (size_t j = 0; j < subStrLen; ++j) {
			if (toLowerCaseChar(str[i + j]) != toLowerCaseChar(subStr[j])) {
				isMatchFound = false;
				break;
			}
		}
		if (isMatchFound) {
			return true;
		}
	}

	return false;
}

bool isGenreMatch(const char* line, const char* genre) {
	if (!line || !genre) {
		return false;
	}

	int firstDelimiter = 0, secondDelimiter = 0;
}

//Function that checks if two string arrays are identical
int myStrCmp(const char* str1, const char* str2) {
	if (!str1 || !str2) {
		return 128;
	}
	while ((*str1) == (*str2) && (*str1)) {
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

//Function that checks if a string array is a substring of another string array by 
//returning a pointer to the beginning of the substring in str1
char* myStrStr(const char* str1, const char* str2) {
	if (!*str2) {
		return (char*)str1;
	}

	while (*str1) {
		const char* h = str1;
		const char* n = str2;

		while (*h && *n && (toLowerCaseChar(*h) == toLowerCaseChar(*n))) {
			h++;
			n++;
		}

		if (!*n) {
			return (char*)str1;
		}

		str1++;
	}

	return nullptr;
}

//Functions that opens our movies text file
std::ifstream readMyFile(const char* fileName) {
	std::ifstream myFile(fileName);
	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return std::ifstream();
	}

	return myFile;
}

//Function that opens the ratings text file
std::ifstream readMyRatings() {
	std::ifstream myRatingsFile("Ratings.txt");
	if (!myRatingsFile.is_open()) {
		std::cerr << "Ratings.txt couldn't be opened!" << std::endl;
		return std::ifstream();
	}

	return myRatingsFile;
}

//Function that counts how many lines there are in our text file (movie database)
int countLinesInFile(const char* fileName) {
	std::ifstream myFile = readMyFile(fileName);

	int lineCount = 0;
	char lines[MAX_LEN_LINE + 1];

	while (myFile.getline(lines, MAX_LEN_LINE)) {
		++lineCount;
	}

	myFile.close();
	return lineCount;
}

//Function that copies the contents of a string in another
void myStrCpy(const char* source, char* dest) {
	if (!source || !dest) {
		return;
	}

	while (*source) {
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}

//Function that creates a temporary file where the movies are copied
std::ofstream createTempFile() {
	std::ofstream tempFile("temp.txt");
	if (!tempFile.is_open()) {
		std::cerr << "Temporary file couldn't be created!" << std::endl;
		return std::ofstream();
	}
	return tempFile;
}

//Add new movie to the database
int addNewMovieToDataBase(const char* title, int year, const char* genre, const char* director, const char* cast, const char* fileName) {
	std::ofstream myFile(fileName, std::ios::app);

	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	myFile << title << " | " << year << " | " << genre << " | " << director << " | " << cast << " | " << DEFAULT_RATING << "/10" << std::endl;

	myFile.close();

	std::cout << "\"" << title << "\" has been successfully added to the movie database!" << std::endl;

	return 0;
}

//Find movie by genre
int findMovieByGenre(const char* genre, const char* fileName) {
	std::ifstream myFile(fileName);

	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	char line[MAX_LEN_LINE + 1];
	bool found = false;

	char* modifiedGenre = modifyInputText(genre);

	std::cout << "Movies in the genre '" << genre << "': " << std::endl;
	while (myFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, modifiedGenre)) {
			std::cout << line << std::endl;
			found = true;
		}
	}

	if (!found) {
		std::cout << "No movies found in the genre \"" << genre << "\"!" << std::endl;
	}

	delete[] modifiedGenre;
	myFile.close();
	return 0;
}

//Find movie by title
int findMovieByTitle(const char* title, const char* fileName) {
	std::ifstream myFile(fileName);

	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	char line[MAX_LEN_LINE + 1];
	bool found = false;

	std::cout << "Movies with the title '" << title << "': " << std::endl;
	while (myFile.getline(line, MAX_LEN_LINE)) {
		if (isTitleMatch(line, title)) {
			std::cout << line << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "No movies found with the title '" << title << "'!" << std::endl;
	}

	myFile.close();
	return 0;
}

//Show all movies on screen
int showAllMoviesInDatabase(const char* fileName) {
	std::ifstream myFile = readMyFile(fileName);

	char line[MAX_LEN_LINE + 1];

	while (myFile.getline(line, MAX_LEN_LINE)) {
		std::cout << line << std::endl;
	}

	myFile.close();
	return 0;
}

//Change movie title
// Function to update the title in a line
bool updateTitleInLine(char* line, const char* oldTitle, const char* newTitle) {
	const char* pos = myStrStr(line, oldTitle);
	if (pos == nullptr) {
		return false;
	}

	int oldLen = findTextLen(oldTitle);
	int newLen = findTextLen(newTitle);

	int diff = newLen - oldLen;
	if (diff > 0) {
		for (size_t i = MAX_LEN_LINE - 1; i >= (pos - line + oldLen); --i) {
			line[i + diff] = line[i];
		}
	}
	else if (diff < 0) {
		for (size_t i = (pos - line + oldLen); i < MAX_LEN_LINE; ++i) {
			line[i + diff] = line[i];
		}
	}

	for (size_t i = 0; i < newLen; ++i) {
		line[pos - line + i] = newTitle[i];
	}

	return true;
}

//Function that updates the title in the movie database text file
bool updateMovieTitle(const char* oldTitle, const char* newTitle, const char* fileName) {
	std::ifstream inFile = readMyFile(fileName);

	std::ofstream outFile = createTempFile();

	bool titleUpdated = false;
	char line[MAX_LEN_LINE + 1];

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, oldTitle)) {
			updateTitleInLine(line, oldTitle, newTitle);
			titleUpdated = true;
		}
		outFile << line << std::endl;
	}
	inFile.close();
	outFile.close();

	if (titleUpdated) {
		std::ifstream tempFile("temp.txt");
		std::ofstream originalFile(fileName, std::ios::trunc);

		if (!tempFile.is_open() || !originalFile.is_open()) {
			std::cerr << fileName << " couldn't be replaced!" << std::endl;
			return false;
		}

		while (tempFile.getline(line, MAX_LEN_LINE)) {
			originalFile << line << std::endl;
		}

		tempFile.close();
		originalFile.close();
	}

	return titleUpdated;
}

//Change release year of movie
//Function to update the title in a line
bool updateReleaseYearInLine(char* line, int newReleaseYear) {
	const char* firstDelimiter = myStrStr(line, DELIMITER);
	if (!firstDelimiter) {
		return false;
	}

	const char* secondDelimiter = myStrStr(firstDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!secondDelimiter) {
		return false;
	}

	const char* releaseYearStart = firstDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS;
	int oldLen = secondDelimiter - releaseYearStart;
	int newLen = countDigitsInNumber(newReleaseYear);

	int diff = newLen - oldLen;

	if (diff > 0) {
		for (size_t i = MAX_LEN_LINE - 1; i >= (secondDelimiter - line); --i) {
			line[i + diff] = line[i];
		}
	}
	else if (diff < 0) {
		for (size_t i = (secondDelimiter - line); i < MAX_LEN_LINE; ++i) {
			line[i + diff] = line[i];
		}
	}

	char* newReleaseYearStr = yearToChar(newReleaseYear);
	for (size_t i = 0; i < newLen; ++i) {
		line[releaseYearStart - line + i] = newReleaseYearStr[i];
	}

	delete[] newReleaseYearStr;

	return true;
}

//Function that updates the release year in the movies database text file
bool updateReleaseYear(const char* title, int newReleaseYear, const char* fileName) {
	std::ifstream inFile = readMyFile(fileName);

	std::ofstream outFile = createTempFile();

	bool releaseYearUpdated = false;
	char line[MAX_LEN_LINE + 1];
	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			if (updateReleaseYearInLine(line, newReleaseYear)) {
				releaseYearUpdated = true;
			}
		}
		outFile << line << std::endl;
	}

	inFile.close();
	outFile.close();

	if (releaseYearUpdated) {
		std::ifstream tempFile("temp.txt");
		std::ofstream originalFile(fileName, std::ios::trunc);
		if (!tempFile.is_open() || !originalFile.is_open()) {
			std::cerr << fileName << " couldn't be replaced!" << std::endl;
			return false;
		}
		while (tempFile.getline(line, MAX_LEN_LINE)) {
			originalFile << line << std::endl;
		}
		tempFile.close();
		originalFile.close();
	}

	return releaseYearUpdated;
}

//Change movie genre
//Function to update the title in a line
bool updateGenreInLine(char* line, const char* newGenre) {
	const char* firstDelimiter = myStrStr(line, DELIMITER);
	if (!firstDelimiter) {
		return false;
	}

	const char* secondDelimeter = myStrStr(firstDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!secondDelimeter) {
		return false;
	}

	const char* thirdDelimiter = myStrStr(secondDelimeter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!thirdDelimiter) {
		return false;
	}

	const char* genreStart = secondDelimeter + DISTANCE_BETWEEN_MOVIE_PARAMETERS;
	int oldLen = thirdDelimiter - genreStart;
	int newLen = findTextLen(newGenre);

	int diff = newLen - oldLen;
	if (diff > 0) {
		for (size_t i = MAX_LEN_LINE - 1; i >= (thirdDelimiter - line); --i) {
			line[i + diff] = line[i];
		}
	}
	else if (diff < 0) {
		for (size_t i = (thirdDelimiter - line); i < MAX_LEN_LINE; ++i) {
			line[i + diff] = line[i];
		}
	}

	for (size_t i = 0; i < newLen; ++i) {
		line[genreStart - line + i] = newGenre[i];
	}

	return true;
}

//Function tha updates the movie genre in the movie database text file
bool updateMovieGenre(const char* title, const char* newGenre, const char* fileName) {
	std::ifstream inFile = readMyFile(fileName);
	std::ofstream outFile = createTempFile();

	bool genreUpdated = false;
	char line[MAX_LEN_LINE + 1];

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			if (updateGenreInLine(line, newGenre)) {
				genreUpdated = true;
			}
		}

		outFile << line << std::endl;
	}

	inFile.close();
	outFile.close();

	if (genreUpdated) {
		std::ifstream tempFile("temp.txt");
		std::ofstream originalFile(fileName, std::ios::trunc);
		if (!tempFile.is_open() || !originalFile.is_open()) {
			std::cerr << fileName << " couldn't be replaced!" << std::endl;
			return false;
		}
		while (tempFile.getline(line, MAX_LEN_LINE)) {
			originalFile << line << std::endl;
		}
		tempFile.close();
		originalFile.close();
	}

	return genreUpdated;
}

//Change movie director
bool updateDirectorInLine(char* line, const char* newDirector) {
	const char* firstDelimiter = myStrStr(line, DELIMITER);
	if (!firstDelimiter) {
		return false;
	}

	const char* secondDelimeter = myStrStr(firstDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!secondDelimeter) {
		return false;
	}

	const char* thirdDelimiter = myStrStr(secondDelimeter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!thirdDelimiter) {
		return false;
	}

	const char* fourthDelimiter = myStrStr(thirdDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!fourthDelimiter) {
		return false;
	}

	const char* directorStart = thirdDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS;
	int oldLen = fourthDelimiter - directorStart;
	int newLen = findTextLen(newDirector);

	int diff = newLen - oldLen;
	if (diff > 0) {
		for (size_t i = MAX_LEN_LINE - 1; i >= (fourthDelimiter - line); --i) {
			line[i + diff] = line[i];
		}
	}
	else if (diff < 0) {
		for (size_t i = (fourthDelimiter - line); i < MAX_LEN_LINE; ++i) {
			line[i + diff] = line[i];
		}
	}

	for (size_t i = 0; i < newLen; ++i) {
		line[directorStart - line + i] = newDirector[i];
	}

	return true;
}

//Function that updates the movie director in the movie database text file
bool updateMovieDirector(const char* title, const char* newDirector, const char* fileName) {
	std::ifstream inFile = readMyFile(fileName);

	std::ofstream outFile = createTempFile();

	bool directorUpdated = false;
	char line[MAX_LEN_LINE + 1];

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			if (updateDirectorInLine(line, newDirector)) {
				directorUpdated = true;
			}
		}

		outFile << line << std::endl;
	}

	inFile.close();
	outFile.close();

	if (directorUpdated) {
		std::ifstream tempFile("temp.txt");
		std::ofstream originalFile(fileName, std::ios::trunc);

		if (!tempFile.is_open() || !originalFile.is_open()) {
			std::cerr << fileName << " couldn't be replaced!" << std::endl;
			return false;
		}

		while (tempFile.getline(line, MAX_LEN_LINE)) {
			originalFile << line << std::endl;
		}

		tempFile.close();
		originalFile.close();
	}

	return directorUpdated;
}

//Change movie cast
bool updateMovieCastInLine(char* line, const char* newCast) {
	const char* firstDelimiter = myStrStr(line, DELIMITER);
	if (!firstDelimiter) {
		return false;
	}
	const char* secondDelimiter = myStrStr(firstDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!secondDelimiter) {
		return false;
	}
	const char* thirdDelimiter = myStrStr(secondDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!thirdDelimiter) {
		return false;
	}
	const char* fourthDelimiter = myStrStr(thirdDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!fourthDelimiter) {
		return false;
	}
	const char* fifthDelimiter = myStrStr(fourthDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, DELIMITER);
	if (!fifthDelimiter) {
		return false;
	}

	const char* castStart = fourthDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS;
	int oldLen = fifthDelimiter - castStart;
	int newLen = findTextLen(newCast);

	int diff = newLen - oldLen;
	if (diff > 0) {
		for (size_t i = MAX_LEN_LINE - 1; i >= (fifthDelimiter - line); --i) {
			line[i + diff] = line[i];
		}
	}
	else if (diff < 0) {
		for (size_t i = (fifthDelimiter - line); i < MAX_LEN_LINE; ++i) {
			line[i + diff] = line[i];
		}
	}
	for (size_t i = 0; i < newLen; ++i) {
		line[castStart - line + i] = newCast[i];
	}
	return true;
}

//Function that changes the movie cast in the movie database text file
bool updateMovieCast(const char* title, const char* newCast, const char* fileName) {
	std::ifstream inFile = readMyFile(fileName);
	std::ofstream outFile = createTempFile();

	bool castUpdated = false;
	char line[MAX_LEN_LINE + 1];

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			if (updateMovieCastInLine(line, newCast)) {
				castUpdated = true;
			}
		}
		outFile << line << std::endl;
	}

	inFile.close();
	outFile.close();

	if (castUpdated) {
		std::ifstream tempFile("temp.txt");
		std::ofstream originalFile(fileName, std::ios::trunc);

		if (!tempFile.is_open() || !originalFile.is_open()) {
			std::cerr << fileName << " couldn't be replaced!" << std::endl;
			return false;
		}

		while (tempFile.getline(line, MAX_LEN_LINE)) {
			originalFile << line << std::endl;
		}
		tempFile.close();
		originalFile.close();
	}

	return castUpdated;
}

//Change movie rating
void copyNewRating(const char* ratingStr, char* line, int startPos, int newLen) {
	for (size_t i = 0; i < newLen; ++i) {
		line[startPos + i] = ratingStr[i];
	}
}

//Function that changes the rating in the current line
bool updateRatingInLine(char* line, double newRating) {
	const char* delimiters[MAX_NUMBER_OF_DELIMITERS];
	delimiters[0] = myStrStr(line, DELIMITER);
	for (size_t i = 1; i < MAX_NUMBER_OF_DELIMITERS && delimiters[i - 1]; ++i) {
		delimiters[i] = myStrStr(delimiters[i - 1] + DISTANCE_BETWEEN_MOVIE_PARAMETERS, (i == MAX_NUMBER_OF_DELIMITERS - 1) ? "/10" : DELIMITER);
	}
	if (!delimiters[MAX_NUMBER_OF_DELIMITERS - 1]) {
		return false;
	}

	const char* ratingStart = delimiters[MAX_NUMBER_OF_DELIMITERS - 2] + DISTANCE_BETWEEN_MOVIE_PARAMETERS;
	int oldLen = delimiters[MAX_NUMBER_OF_DELIMITERS - 1] - ratingStart;

	char ratingStr[MAX_LEN_RATING + 1];
	int integerPart = static_cast<int>(newRating);
	int decimalPart = static_cast<int>((newRating - integerPart) * 10);
	int index = 0;

	int temp = integerPart;
	do {
		ratingStr[index++] = (temp % 10) + TO_CHAR;
		temp /= 10;
	} while (temp > 0);
	for (int i = 0; i < index / 2; ++i) {
		char tmp = ratingStr[i];
		ratingStr[i] = ratingStr[index - 1 - i];
		ratingStr[index - 1 - i] = tmp;
	}

	ratingStr[index++] = '.';
	ratingStr[index++] = decimalPart + '0';
	ratingStr[index] = '\0';

	int newLen = index;

	int diff = newLen - oldLen;
	if (diff != 0) {
		for (size_t i = MAX_LEN_LINE - 1; i >= (delimiters[MAX_NUMBER_OF_DELIMITERS - 1] - line); --i) {
			if (i + diff < MAX_LEN_LINE) line[i + diff] = line[i];
		}
	}

	copyNewRating(ratingStr, line, ratingStart - line, newLen);

	int endPos = ratingStart - line + newLen;
	line[endPos] = '/';
	line[endPos + 1] = '1';
	line[endPos + 2] = '0';
	line[endPos + 3] = '\0';

	return true;
}

//Function that changes the rating in the movie database text file
bool updateMovieRating(const char* title, double newRating, const char* fileName) {
	std::ifstream inFile = readMyFile(fileName);
	std::ofstream outFile = createTempFile();

	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		return false;
	}

	bool ratingUpdated = false;
	char line[MAX_LEN_LINE + 1];
	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (!ratingUpdated && myStrStr(line, title)) {
			ratingUpdated = updateRatingInLine(line, newRating);
		}
		outFile << line << std::endl;
	}

	inFile.close();
	outFile.close();

	if (ratingUpdated) {
		std::ifstream tempFile("temp.txt");
		std::ofstream originalFile(fileName, std::ios::trunc);
		if (!tempFile.is_open() || !originalFile.is_open()) {
			std::cerr << fileName << " couldn't be replaced!" << std::endl;
			return false;
		}
		while (tempFile.getline(line, MAX_LEN_LINE)) {
			originalFile << line << std::endl;
		}
	}
	return ratingUpdated;
}

//Sort movies by title
char** readMoviesFromFile(const char* fileName, int& movieCount) {
	if (movieCount == 0) {
		std::cerr << "No movies found in the file!" << std::endl;
		return nullptr;
	}

	std::ifstream myFile = readMyFile(fileName);

	char** movies = new char* [movieCount];
	for (size_t i = 0; i < movieCount; ++i) {
		movies[i] = new char[MAX_LEN_LINE];
	}

	int index = 0;
	while (index < movieCount && myFile.getline(movies[index], MAX_LEN_LINE)) {
		++index;
	}

	if (index < movieCount) {
		std::cerr << "File had fewer movies than expected. Only " << index << " movies were read." << std::endl;
	}

	myFile.close();

	return movies;
}

//This function sorts the movies by using selection sort
void sortMoviesByTitle(char** movies, int movieCount) {
	for (size_t i = 0; i < movieCount - 1; ++i) {
		int minIndex = i;

		for (size_t j = i + 1; j < movieCount; ++j) {
			const char* title1 = movies[minIndex];
			const char* title2 = movies[j];

			int compareResult = myStrCmp(title1, title2);
			if (compareResult > 0) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			char* temp = movies[i];
			movies[i] = movies[minIndex];
			movies[minIndex] = temp;
		}
	}
}

void printMovies(char** movies, int movieCount) {
	for (size_t i = 0; i < movieCount; ++i) {
		std::cout << movies[i] << std::endl;
	}
}

void freeMovies(char** movies, int movieCount) {
	for (size_t i = 0; i < movieCount; ++i) {
		delete[] movies[i];
	}
	delete[] movies;
}

//Sort movies by rating
double extractRating(const char* movieData) {
	int len = findTextLen(movieData);
	int ratingStart = -1;

	for (int i = len - 1; i >= 0; --i) {
		if (movieData[i] == ' ') {
			ratingStart = i + 1;
			break;
		}
	}

	if (ratingStart == -1) {
		return -1.0;
	}

	while (ratingStart < len && !isDigit(movieData[ratingStart]) && movieData[ratingStart] != '.') {
		++ratingStart;
	}

	if (ratingStart >= len || (!isDigit(movieData[ratingStart]) && movieData[ratingStart] != '.')) {
		return -1.0; 
	}

	double rating = 0.0;
	double fractionalPart = 0.0;
	double divisor = 10.0;
	bool isFractional = false;

	for (int i = ratingStart; i < len; ++i) {
		if (isDigit(movieData[i])) {
			if (isFractional) {
				fractionalPart += (movieData[i] + TO_INTEGER) / divisor;
				divisor *= 10.0;
			}
			else {
				rating = rating * 10 + (movieData[i] + TO_INTEGER);
			}
		}
		else if (movieData[i] == '.') {
			if (isFractional) break; 
			isFractional = true;
		}
		else if (movieData[i] == '/') {
			break;
		}
		else {
			return -1.0;
		}
	}

	return rating + fractionalPart;
}

//Sort movies by their ratings using selection sort
void sortMoviesByRating(char** movies, int movieCount) {
	for (size_t i = 0; i < movieCount - 1; ++i) {
		int minIndex = i;
		double minRating = extractRating(movies[i]);

		for (size_t j = i + 1; j < movieCount; ++j) {
			double currentRating = extractRating(movies[j]);
			if (currentRating < minRating) {
				minIndex = j;
				minRating = currentRating;
			}
		}

		if (minIndex != i) {
			char* tempMovie = movies[i];
			movies[i] = movies[minIndex];
			movies[minIndex] = tempMovie;
		}
	}
}

//Filter movies by rating
void printMoviesByRating(std::ifstream& file, double userRating) {
	char line[MAX_LEN_LINE + 1];
	bool foundMovies = false;

	while (file.getline(line, MAX_LEN_LINE)) {
		double movieRating = extractRating(line);
		if (movieRating >= userRating) {
			std::cout << line << std::endl;
			foundMovies = true;
		}
	}

	if (!foundMovies) {
		std::cout << "No movies found with a rating >= " << userRating << "." << std::endl;
	}
}

void filterMoviesByRating(const char* filename, double userRating) {
	std::ifstream myFile = readMyFile(filename);

	printMoviesByRating(myFile, userRating);

	myFile.close();
}

//Delete movie
bool deleteMovie(std::ifstream& inFile, std::ofstream& outFile, const char* title) {
	char line[MAX_LEN_LINE + 1];
	bool found = false;

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			found = true;
			continue;
		}
		outFile << line << std::endl;
	}

	return found;
}

bool replaceOriginalFile(const char* originalFileName, const char* tempFileName) {
	std::ifstream tempFile(tempFileName);
	if (!tempFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		return false;
	}

	std::ofstream originalFile(originalFileName, std::ios::trunc);
	if (!originalFile.is_open()) {
		std::cerr << "The original file couldn't be opened!" << std::endl;
		tempFile.close();
		return false;
	}

	char line[MAX_LEN_LINE + 1];

	while (tempFile.getline(line, MAX_LEN_LINE)) {
		originalFile << line << std::endl;
	}

	tempFile.close();
	originalFile.close();

	return true;
}

int deleteMovieByTitle(const char* title, const char* fileName) {
	std::ifstream myFile = readMyFile(fileName);

	std::ofstream tempFile = createTempFile();

	bool found = deleteMovie(myFile, tempFile, title);
	myFile.close();
	tempFile.close();

	if (!found) {
		std::cout << "No movie found with the title \"" << title << "\"!" << std::endl;
		return 0;
	}

	if (!replaceOriginalFile(fileName, "temp.txt")) {
		std::cerr << "The original file couldn't be replaced!" << std::endl;
		return 1;
	}

	std::cout << "'" << title << "' has been successfully deleted!" << std::endl;
	return 0;
}

//Rate movie
//Function that finds a movie in the database and returns its index
int findMovieIndex(const char* movieTitle, const char* fileName) {
	std::ifstream file(fileName);
	char line[MAX_LEN_LINE + 1];
	int index = 0;

	if (!file.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return -1;
	}

	while (file.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, movieTitle)) {
			file.close();
			return index;
		}
		++index;
	}

	file.close();
	return -1;
}

// Function that writes the new rating and the movie index to Rating.txt
void appendRating(const char* ratingsFile, int movieIndex, int newRating) {
	std::ofstream file(ratingsFile, std::ios::app);
	if (!file) {
		return;
	}

	file << movieIndex << " " << newRating << "\n";
	file.close();
}

// Function to calculate the average rating for a movie from Ratings.txt
double calculateAverageRating(const char* ratingsFile, int movieIndex) {
	std::ifstream myRatings(ratingsFile);
	if (!myRatings.is_open()) {
		std::cerr << "Ratings.txt couldn't be opened!" << std::endl;
		return 0.0;
	}

	int index, rating, count = 0;
	float total = 0.0;

	while (myRatings >> index >> rating) {
		if (index == movieIndex) {
			total += rating;
			count++;
		}
	}

	myRatings.close();

	return (count > 0) ? (total / count) : 0.0;
}

//Function that finds the position of the ratings in our original movie database
int findRatingStartPos(char* line) {
	int len = 0;

	while (line[len] != '\0') {
		len++;
	}

	int pos = len - 1;

	while (pos >= 0 && line[pos] != '|') {
		pos--;
	}


	while (pos >= 0 && line[pos] == ' ') {
		pos--;
	}

	return pos + 1;
}

//Function that updates the new formatted calculated average rating in the line the movies is at
bool updateAverageRatingInLine(char* line, double newRating) {
	int integerPart = (int)newRating;
	int decimalPart = (newRating - integerPart) * 10;

	int startPos = findRatingStartPos(line);

	line[startPos] = '0' + integerPart;
	line[startPos + 1] = '.';
	line[startPos + 2] = '0' + decimalPart;

	line[startPos + 3] = '/';
	line[startPos + 4] = '1';
	line[startPos + 5] = '0';

	line[startPos + 6] = '\0';

	return true;
}

//Function that updates the new line with formatted decimal rating in our original the movie database text file
bool updateAverageMovieRating(const char* title, double newRating, const char* fileName) {
	std::ifstream inFile = readMyFile(fileName);
	std::ofstream outFile = createTempFile();

	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		return false;
	}

	bool ratingUpdated = false;
	char line[MAX_LEN_LINE + 1];

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (!ratingUpdated && myStrStr(line, title)) {
			ratingUpdated = updateAverageRatingInLine(line, newRating);
		}

		outFile << line << std::endl;
	}

	inFile.close();
	outFile.close();

	if (ratingUpdated) {
		std::ofstream originalFile(fileName, std::ios::trunc);
		if (!originalFile.is_open()) {
			std::cerr << fileName << " couldn't be opened for overwrite!" << std::endl;
			return false;
		}

		std::ifstream tempFile("temp.txt");
		if (!tempFile.is_open()) {
			std::cerr << "Temporary file couldn't be opened!" << std::endl;
			return false;
		}

		while (tempFile.getline(line, MAX_LEN_LINE)) {
			originalFile << line << std::endl;
		}

		tempFile.close();
		originalFile.close();
	}

	return ratingUpdated;
}


//Function that finds the location of the movie in the database based on its title
bool findMovieTitleLine(const char* title, const char* fileName, char* line) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Failed to open file: " << fileName << std::endl;
		return false;
	}

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			return true;
		}
	}

	return false;
}

// Main function to handle the rating process
void rateMovie(const char* movieTitle, int newRating, const char* fileName, const char* ratingsFile) {
	int movieIndex = findMovieIndex(movieTitle, fileName);
	if (movieIndex == -1) {
		std::cout << "\"" << movieTitle << "\" was not found!" << std::endl;
		return;
	}

	char line[MAX_LEN_LINE + 1];
	if (!findMovieTitleLine(movieTitle, fileName, line)) {
		std::cout << "Movie not found!" << std::endl;
		return;
	}

	appendRating(ratingsFile, movieIndex, newRating);

	double newAverageRating = calculateAverageRating(ratingsFile, movieIndex);

	updateAverageRatingInLine(line, newAverageRating);
	updateAverageMovieRating(movieTitle, newAverageRating, fileName);

	std::cout << "You have rated \"" << movieTitle << "\" successfully!" << std::endl;
}

int main() {
	char fileName[MAX_LEN_TEXT_FILE_NAME + 1] = "MovieDataBase.txt";
	std::cout << "Hello and welcome to my IMDB!" << std::endl;
	std::cout << "Firstly, you need to enter your role (user or admin/administrator): ";
	char role[MAX_LEN_ROLE + 1];
	std::cin.getline(role, MAX_LEN_ROLE);

	std::cout << "Now, as an " << toLower(role) << " you can choose one the the options below" << std::endl;
	std::cout << "by typing the digit in front of your chosen option: " << std::endl;

	if (myStrCmp(toLower(role), "user") == 0) {

		std::cout << "1. Find movie by genre" << std::endl;
		std::cout << "2. Find movie by title" << std::endl;
		std::cout << "3. View all movies" << std::endl;
		std::cout << "4. Sort movies by title" << std::endl;
		std::cout << "5. Sort movies by rating" << std::endl;
		std::cout << "6. Rate a movie" << std::endl;
		std::cout << "7. Filter movies by rating" << std::endl;
		std::cout << "If you want to exit the program, press - \"CLOSE\"!" << std::endl;

		std::cout << std::endl;

		while (true) {
			char command[MAX_LEN_COMMAND + 1];
			std::cout << "Your command: ";
			std::cin.getline(command, MAX_LEN_COMMAND);

			if (myStrCmp(command, "1") == 0) {
				char genre[MAX_LEN_GENRE + 1];
				std::cout << "Enter a movie genre: ";
				std::cin.getline(genre, MAX_LEN_GENRE);

				findMovieByGenre(genre, fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "2") == 0) {
				char movieTitle[MAX_LEN_MOVIE_TITLES + 1];
				std::cout << "Enter a movie title: ";
				std::cin.getline(movieTitle, MAX_LEN_MOVIE_TITLES);

				findMovieByTitle(movieTitle, fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "3") == 0) {
				showAllMoviesInDatabase(fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "4") == 0) {
				int movieCount = countLinesInFile(fileName);
				char** movies = readMoviesFromFile(fileName, movieCount);

				std::cout << "Movies sorted by title:" << std::endl;
				sortMoviesByTitle(movies, movieCount);
				printMovies(movies, movieCount);
				freeMovies(movies, movieCount);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "5") == 0) {
				int moviesCountR = countLinesInFile(fileName);
				char** moviesR = readMoviesFromFile(fileName, moviesCountR);

				std::cout << "Movies sorted by rating: " << std::endl;
				sortMoviesByRating(moviesR, moviesCountR);
				printMovies(moviesR, moviesCountR);
				freeMovies(moviesR, moviesCountR);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "6") == 0) {
				char movieToRate[MAX_LEN_MOVIE_TITLES + 1];
				std::cout << "Enter the title of the movie you want to rate: ";
				std::cin.getline(movieToRate, MAX_LEN_MOVIE_TITLES);

				int newRating;
				std::cout << "Enter your rating: ";
				std::cin >> newRating;
				if (!std::cin || newRating < 1 || newRating > 10) {
					std::cerr << "Invalid rating!" << std::endl;
					return 1;
				}
				std::cin.ignore();

				rateMovie(movieToRate, newRating, fileName, "Ratings.txt");

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "7") == 0) {
				std::cout << "Enter the rating you want to filter your movies by: ";
				double rating;
				std::cin >> rating;
				if (!std::cin || rating < 1 || rating > 10) {
					std::cerr << "Invalid input! The rating you are searching for should be a positive real number from 1 to 10!" << std::endl;
					return 1;
				}
				std::cin.ignore();

				filterMoviesByRating(fileName, rating);

				std::cout << std::endl;
			}
			else if (myStrCmp(toUpper(command), "CLOSE") == 0) {
				std::cout << "Thank you for using my IMDB! You can exit the program now by pressing 'ENTER'!" << std::endl;
				return 0;
			}
			else {
				std::cout << "Your command is invalid!" << std::endl;
			}
		}
	}
	else if (myStrCmp(toLower(role), "administrator") == 0 || myStrCmp(toLower(role), "admin") == 0) {
		std::cout << "1. Add a new movie" << std::endl;
		std::cout << "2. Find movie by genre" << std::endl;
		std::cout << "3. Find movie by title" << std::endl;
		std::cout << "4. View all movies" << std::endl;
		std::cout << "5. Change movie data" << std::endl;
		std::cout << "6. Delete movie" << std::endl;
		std::cout << "7. Sort movies by title" << std::endl;
		std::cout << "8. Sort movies by rating" << std::endl;
		std::cout << "9. Filter movies by rating" << std::endl;
		std::cout << "If you want to exit the program, press - \"CLOSE\"!" << std::endl;

		std::cout << std::endl;

		while (true) {
			char command[MAX_LEN_COMMAND + 1];
			std::cout << "Your command: ";
			std::cin.getline(command, MAX_LEN_COMMAND);

			if (myStrCmp(command, "1") == 0) {
				char movieTitle[MAX_LEN_MOVIE_TITLES + 1];
				std::cout << "Input a movie title: ";
				std::cin.getline(movieTitle, MAX_LEN_MOVIE_TITLES + 1);

				char movieGenre[MAX_LEN_GENRE + 1];
				std::cout << "Input a genre: ";
				std::cin.getline(movieGenre, MAX_LEN_GENRE);

				int releaseYear;
				std::cout << "Input the release year of the movie: ";
				std::cin >> releaseYear;
				if (!std::cin || releaseYear < 0) {
					std::cerr << "Invalid input! You have entered and incorrect year!" << std::endl;
					return 1;
				}
				std::cin.ignore();

				char movieDirector[MAX_LEN_MOVIE_DIRECTOR + 1];
				std::cout << "Input the name of the movie director: ";
				std::cin.getline(movieDirector, MAX_LEN_MOVIE_DIRECTOR);

				char movieCast[MAX_LEN_MOVIE_CAST + 1];
				std::cout << "Input the names of the movie cast: ";
				std::cin.getline(movieCast, MAX_LEN_MOVIE_CAST);

				addNewMovieToDataBase(movieTitle, releaseYear, movieGenre, movieDirector, movieCast, fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "2") == 0) {
				std::cout << "Enter your genre: ";
				char genreToFindMovie[MAX_LEN_GENRE + 1];

				std::cin.getline(genreToFindMovie, MAX_LEN_GENRE);

				findMovieByGenre(genreToFindMovie, fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "3") == 0) {
				std::cout << "Enter your title: ";
				char titleToFindMovie[MAX_LEN_MOVIE_TITLES];
				std::cin.getline(titleToFindMovie, MAX_LEN_MOVIE_TITLES);

				findMovieByTitle(titleToFindMovie, fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "4") == 0) {
				showAllMoviesInDatabase(fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "5") == 0) {
				char option[MAX_LEN_OPTION + 1];
				std::cout << "What do you want to change about a movie? - Enter one of the words \"title\", \"year\"";
				std::cout << ", \"genre\", \"director\", \"cast\" or \"rating\" here: ";
				std::cin.getline(option, MAX_LEN_OPTION);
				if (myStrCmp(toLower(option), "title") == 0) {
					std::cout << "Enter the movie you want to change the title of: ";
					char movieToChangeTitleOf[MAX_LEN_MOVIE_TITLES + 1];
					std::cin.getline(movieToChangeTitleOf, MAX_LEN_MOVIE_TITLES);
					std::cout << "Enter new movie title: ";
					char newMovieTitle[MAX_LEN_MOVIE_TITLES + 1];
					std::cin.getline(newMovieTitle, MAX_LEN_MOVIE_TITLES);

					if (updateMovieTitle(movieToChangeTitleOf, newMovieTitle, fileName)) {
						std::cout << "The title of \"" << movieToChangeTitleOf << "\" has been changed to \"";
						std::cout << "\"" << newMovieTitle << "\" successfully!" << std::endl;
					}
					else {
						std::cout << "The operation wasn't successful!" << std::endl;
					}

					std::cout << std::endl;
				}
				else if (myStrCmp(toLower(option), "year") == 0) {
					std::cout << "Enter the title of the movie you want to change the release year of: ";
					char movieToChangeTheReleaseYearOf[MAX_LEN_MOVIE_TITLES + 1];
					std::cin.getline(movieToChangeTheReleaseYearOf, MAX_LEN_MOVIE_TITLES);
					int newReleaseYear;
					std::cout << "Enter the new release year: ";
					std::cin >> newReleaseYear;
					std::cin.ignore();

					if (!std::cin || newReleaseYear < 0) {
						std::cerr << "Invalid input! Your new release year should be positive integer number!" << std::endl;
						return 1;
					}

					if (updateReleaseYear(movieToChangeTheReleaseYearOf, newReleaseYear, fileName)) {
						std::cout << "The release year of \"" << movieToChangeTheReleaseYearOf << "\" has been changed successfully!" << std::endl;
					}
					else {
						std::cout << "The operation wasn't successful!" << std::endl;
					}

					std::cout << std::endl;
				}
				else if (myStrCmp(toLower(option), "genre") == 0) {
					std::cout << "Enter the title of the movie you want to change the genre of: ";
					char movieToChangeGenreOf[MAX_LEN_MOVIE_TITLES + 1];
					std::cin.getline(movieToChangeGenreOf, MAX_LEN_MOVIE_TITLES);
					char newGenre[MAX_LEN_GENRE];
					std::cout << "Enter the new genre: ";
					std::cin.getline(newGenre, MAX_LEN_GENRE);

					if (updateMovieGenre(movieToChangeGenreOf, newGenre, fileName)) {
						std::cout << "The genre of \"" << movieToChangeGenreOf << "\" has been changed successfully!" << std::endl;
					}
					else {
						std::cout << "The operation wasn't successful!" << std::endl;
					}

					std::cout << std::endl;
				}
				else if (myStrCmp(toLower(option), "director") == 0) {
					std::cout << "Enter the movie you want to change the director of: ";
					char movieToChangeTheDirectorOf[MAX_LEN_MOVIE_TITLES + 1];
					std::cin.getline(movieToChangeTheDirectorOf, MAX_LEN_MOVIE_TITLES);
					char newDirector[MAX_LEN_MOVIE_DIRECTOR + 1];
					std::cout << "Enter the name of the new movie director: ";
					std::cin.getline(newDirector, MAX_LEN_MOVIE_DIRECTOR);

					if (updateMovieDirector(movieToChangeTheDirectorOf, newDirector, fileName)) {
						std::cout << "The director of \"" << movieToChangeTheDirectorOf << "\" has been changed successfully!" << std::endl;
					}
					else {
						std::cout << "The operation wasn't successful!" << std::endl;
					}

					std::cout << std::endl;
				}
				else if (myStrCmp(toLower(option), "cast") == 0) {
					std::cout << "Enter the title of the movie you want to change the cast of: ";
					char movieToChangeTheCastOf[MAX_LEN_MOVIE_CAST + 1];
					std::cin.getline(movieToChangeTheCastOf, MAX_LEN_MOVIE_TITLES);
					char newCast[MAX_LEN_MOVIE_CAST];
					std::cout << "Enter the new cast of the movie: ";
					std::cin.getline(newCast, MAX_LEN_MOVIE_CAST);

					if (updateMovieCast(movieToChangeTheCastOf, newCast, fileName)) {
						std::cout << "The cast of \"" << movieToChangeTheCastOf << "\" has been changed successfully!" << std::endl;
					}
					else {
						std::cout << "The operation wasn't successful!" << std::endl;
					}

					std::cout << std::endl;
				}
				else if (myStrCmp(toLower(option), "rating") == 0) {
					std::cout << "Enter the title of movie you want to change the rating of: ";
					char movieToChangeTheRatingOf[MAX_LEN_MOVIE_TITLES];
					std::cin.getline(movieToChangeTheRatingOf, MAX_LEN_MOVIE_TITLES);
					int newRating;
					std::cout << "Enter the new rating: ";
					std::cin >> newRating;
					if (!std::cin || newRating < 0 || newRating > 10) {
						std::cerr << "Invalid input! Your new rating must be a positive integer number between 1 and 10!" << std::endl;
						return 1;
					}
					std::cin.ignore();

					if (updateMovieRating(movieToChangeTheRatingOf, newRating, fileName)) {
						std::cout << "The rating of \"" << movieToChangeTheRatingOf << "\" has been changed successfully!" << std::endl;
					}
					else {
						std::cout << "The operatin wasn't successful!" << std::endl;
					}

					std::cout << std::endl;
				}
			}
			else if (myStrCmp(command, "6") == 0) {
				char movieToDelete[MAX_LEN_MOVIE_TITLES + 1];
				std::cout << "Enter the title of the movie you want to delete: ";
				std::cin.getline(movieToDelete, MAX_LEN_MOVIE_TITLES);

				deleteMovieByTitle(movieToDelete, fileName);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "7") == 0) {
				int movieCount = countLinesInFile(fileName);
				char** movies = readMoviesFromFile(fileName, movieCount);

				if (!movies) {
					std::cerr << "Failed to load movies from file!" << std::endl;
					return 1;
				}

				sortMoviesByTitle(movies, movieCount);

				std::cout << "Movies sorted by title:" << std::endl;
				printMovies(movies, movieCount);

				freeMovies(movies, movieCount);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "8") == 0) {
				int movieCount = countLinesInFile(fileName);
				char** movies = readMoviesFromFile(fileName, movieCount);
				sortMoviesByRating(movies, movieCount);

				std::cout << "Movies after sorting by rating:";
				printMovies(movies, movieCount);
				freeMovies(movies, movieCount);

				std::cout << std::endl;
			}
			else if (myStrCmp(command, "9") == 0) {
				std::cout << "Enter the rating you want to filter your movies by: ";
				double rating;
				std::cin >> rating;
				if (!std::cin || rating < 1 || rating > 10) {
					std::cerr << "Invalid input! The rating you are searching for should be a positive decimal number from 1 to 10!" << std::endl;
					return 1;
				}
				std::cin.ignore();
				filterMoviesByRating(fileName, rating);

				std::cout << std::endl;
			}
			else if (myStrCmp(toUpper(command), "CLOSE") == 0) {
				std::cout << "Thank you for using my IMDB! You can exit the program now by pressing 'ENTER'!" << std::endl;
				return 0;
			}
			else {
				std::cerr << "Your command is invalid!" << std::endl;
				std::cout << std::endl;
				return 1;
			}

		}

	}
	else {
		std::cerr << "Invalid input - you have entered and invalid role! Please try again!" << std::endl;
		return 1;
	}

	return 0;
}
