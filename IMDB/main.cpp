#include<iostream>
#include<fstream>

const int MAX_LEN_ROLE = 15;
const int MAX_LEN_COMMAND = 7;
const int MAX_LEN_OPTION = 9;  // GENRE - 5 , CAST - 4, DIRECTOR - 8, RATING - 6, TITLE - 5
const int TO_LOWER_CASE_CHANGE = 'a' - 'A';
const int TO_UPPER_CASE_CHANGE = 'A' - 'a';
const int TO_CHAR = '0';
const int TO_INTEGER = -'0';
const int DISTANCE_BETWEEN_MOVIE_PARAMETERS = 3; // " | "
const char* DELIMITER = " | ";
const int DEFAULT_RATING = 5;
const int MAX_LEN_GENRE = 400;
const int MAX_LEN_MOVIE_TITLES = 1000;
const int MAX_LEN_MOVIE_DIRECTOR = 500;
const int MAX_LEN_MOVIE_CAST = 4000;
const int MIN_RATING = 0;
const int MAX_RATING = 10;
const int MAX_LEN_RATING = 3;
const int MAX_LEN_LINE = MAX_LEN_GENRE + MAX_LEN_GENRE + MAX_LEN_MOVIE_DIRECTOR + MAX_LEN_MOVIE_CAST + 2 + 10 + 5; // MAX_LEN_MOVIE_TITLES + MAX_LEN_MOVIE_DIRECTOR + MAX_LEN_MOVIE_CAST + RATING (MAX - 2 digits) + 10 spaces + 5 lines

//Base Functions
//Simple checks
bool isLetter(char ch);
bool isLowerCase(char ch);
bool isUpperCase(char ch);
char toLowerCaseChar(char ch);
char toUpperCaseChar(char ch);

int findTextLen(const char* text);

//Functions that handle the release year and turn it into char string
int countDigitsInNumber(int year);
int reverseYear(int year);
char* yearToChar(int year);

//Text modifications and more complicated checks
char* toLower(char* userInput);
char* toUpper(char* userInput);
bool contains(const char* str1, const char* str2);
char* modifyInputGenre(const char* inputGenre);
bool isSubstringMatch(const char* str, const char* subStr);

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

int countLinesInFile(const char* fileName);
void myStrCpy(const char* source, char* dest);

//bool myStrCat(char* destination, const char* source, size_t destSize);
//const char* findDelimiter(const char* str, int n, char delimiter = '|');
//void myStrCpyWithStartPos(char* dest, const char* src, int index);
//char** readMoviesFromFile(const char* fileName, int& movieCount);
//void writeLines(const char* fileName, char** lines, int lineCount);
//void freeMovies(char** movies, int movieCount);
//void printMovies(char** movies, int movieCount);
//bool checkIfRatingIsValid(const char* rating);

//Main Functions
int addNewMovieToDataBase(const char* title, int year, const char* genre, const char* director, const char* cast, const char* fileName);
int findMovieByGenre(const char* genre, const char* fileName);
int findMovieByTitle(const char* title, const char* fileName);
int showAllMoviesInDatabase(const char* fileName);
bool updateMovieTitle(const char* oldTitle, const char* newTitle, const char* fileName);
bool updateReleaseYear(const char* title, int newReleaseYear, const char* fileName);
bool updateMovieGenre(const char* title, const char* newGenre, const char* fileName);
bool updateMovieDirector(const char* title, const char* newDirector, const char* fileName);
bool updateMovieCast(const char* title, const char* newCast, const char* fileName);

bool deleteMovie(std::ifstream& myFile, std::ofstream& tempFile, const char* title);
bool replaceOriginalFile(const char* fileName);
int deleteMovieByTitle(const char* title, const char* fileName);


//Function that checks if a character is letter
bool isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
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

//Function that finds the length of a string array
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

//Functions that handle the release year and turn it into a char array
int countDigitsInNumber(int number) {
	int digitsCounter = 0;

	while (number != 0) {
		int temp = number % 10;
		number /= 10;
		digitsCounter++;
	}

	return digitsCounter;
}

int reverseYear(int year) {
	int reversed = 0;
	while (year > 0) {
		int digit = year % 10;
		reversed = reversed * 10 + digit;
		year /= 10;
	}
	return reversed;
}

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

//Handle rating
char* turnRatingToChar(int rating) {
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

//Function that turns all letters in a string array lower case
char* toLower(char* userInput) {
	int textLen = findTextLen(userInput);

	for (size_t i = 0; i < textLen; ++i) {
		userInput[i] = toLowerCaseChar(userInput[i]);
	}

	return userInput;
}

//Function that turns all letters in a string array upper case
char* toUpper(char* userInput) {
	int textLen = findTextLen(userInput);

	for (size_t i = 0; i < textLen; ++i) {
		userInput[i] = toUpperCaseChar(userInput[i]);
	}

	return userInput;
}



//Function that checks if a string array is a substring of another string array
bool contains(const char* str1, const char* str2) {
	return myStrStr(str1, str2) != nullptr;
}

//Function that changes the first letter of the genre, inputed by the used, by turning it in upper case
char* modifyInputGenre(const char* inputGenre) {
	int inputGenreLen = findTextLen(inputGenre);
	char* modifiedGenre = new char[inputGenreLen + 1];
	bool inWord = false;

	for (size_t i = 0; i < inputGenreLen; ++i) {
		if (isLetter(inputGenre[i])) {
			if (!inWord) {
				if (isLowerCase(inputGenre[i])) {
					modifiedGenre[i] = inputGenre[i] + TO_UPPER_CASE_CHANGE;
				}
				else {
					modifiedGenre[i] = inputGenre[i];
				}
				inWord = true;
			}
			else {
				modifiedGenre[i] = inputGenre[i];
			}
		}
		else {
			inWord = false;
			modifiedGenre[i] = inputGenre[i];
		}
	}

	modifiedGenre[inputGenreLen] = '\0';
	return modifiedGenre;
}

//Function checking if the user input matches a part of the title
bool isSubstringMatch(const char* str, const char* subStr) {
	if (!str || !subStr) {
		return false;
	}

	int strLen = strlen(str);
	int subStrLen = strlen(subStr);

	if (subStrLen > strLen) {
		return false;
	}

	for (size_t i = 0; i <= strLen - subStrLen; ++i) {
		bool isMatchFound = true;
		for (size_t j = 0; j < subStrLen; ++j) {
			if (toLowerCaseChar(str[i + j]) != toLowerCaseChar(subStr[j])) {
				isMatchFound = false;
				break;
			}
		}
		if (isMatchFound) return true;
	}

	return false;
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

//Function that checks if a string array is a substring of another string array by return a pointer
char* myStrStr(const char* str1, const char* str2) {
	if (!*str2) {
		return (char*)str1;
	}

	while (*str1) {
		const char* h = str1;
		const char* n = str2;

		while (*h && *n && (*h == *n)) {
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

//const char* findDelimiter(const char* str, int n, char delimiter) {
//	const char* pos = str;
//	while (*pos && n > 0) {
//		if (*pos == delimiter) {
//			n--;
//		}
//		pos++;
//	}
//
//	return (n == 0) ? pos : nullptr;
//}

//Function that counts how many lines there are in our text file (movie database)
int countLinesInFile(const char* fileName) {
	std::ifstream myFile(fileName);
	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return -1;
	}

	int lineCount = 0;
	char lines[MAX_LEN_LINE];

	while (myFile.getline(lines, MAX_LEN_LINE)) {
		++lineCount;
	}

	myFile.close();
	return lineCount;
}

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

void sortMoviesByTitle(char** movies, int movieCount);
char** readAndSortMovies(const char* fileName, int& movieCount) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "File could not be opened!" << std::endl;
		movieCount = 0;
		return nullptr;
	}

	int capacity = 10;
	movieCount = 0;
	char** movies = new char* [capacity];
	char line[MAX_LEN_LINE];

	while (file.getline(line, sizeof(line))) {
		std::cout << "Read line: [" << line << "]" << std::endl; // Debugging line

		if (movieCount >= capacity) {
			capacity *= 2;
			char** newMovies = new char* [capacity];
			for (int i = 0; i < movieCount; ++i) {
				newMovies[i] = movies[i];
			}
			delete[] movies;
			movies = newMovies;
		}

		int len = strlen(line) + 1;  // Include null terminator
		movies[movieCount] = new char[len];
		myStrCpy(movies[movieCount], line);  // Copy line into movies array
		++movieCount;
	}

	file.close();
	return movies;
}

void printMovies(char** movies, int movieCount) {
	for (int i = 0; i < movieCount; ++i) {
		std::cout << "Movie " << (i + 1) << ": " << movies[i] << std::endl;
	}
}

void freeMovies(char** movies, int movieCount) {
	for (int i = 0; i < movieCount; ++i) {
		delete[] movies[i];
	}
	delete[] movies;
}

//bool checkIfRatingIsValid(const char* rating) {
//	if (!rating || rating[0] == '\0') {
//		return false;
//	}
//
//	if (rating[0] < '0' || rating[0] > '9') {
//		return false;
//	}
//
//	if (rating[1] == '\0') {
//		return rating[0] >= '1' && rating[0] <= '9';
//	}
//
//	if (rating[0] == '1' && rating[1] == '0' && rating[2] == '\0') {
//		return true;
//	}
//
//	return false;
//}




//Add new movie to the database
int addNewMovieToDataBase(const char* title, int year, const char* genre, const char* director, const char* cast, const char* fileName) {
	std::ofstream myFile(fileName, std::ios::app);

	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	myFile << title << " | " << year << " | " << genre << " | " << director << " | " << cast << " | " << DEFAULT_RATING << "/10" << std::endl;

	myFile.close();

	std::cout << title << " has been successfully added to the movie data base!" << std::endl;

	return 0;
}

//Find movie by genre
int findMovieByGenre(const char* genre, const char* fileName) {
	std::ifstream myFile(fileName);

	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	char line[MAX_LEN_LINE];
	bool found = false;

	char* modifiedGenre = modifyInputGenre(genre);
	std::cout << "Movies in the genre '" << genre << "': " << std::endl;
	while (myFile.getline(line, MAX_LEN_LINE)) {
		if (contains(line, modifiedGenre)) {
			std::cout << line << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "No movies found in the genre '" << genre << "'!" << std::endl;
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

	char line[MAX_LEN_LINE];
	bool found = false;

	std::cout << "Movies with the title '" << title << "': " << std::endl;
	while (myFile.getline(line, MAX_LEN_LINE)) {
		if (isSubstringMatch(line, title)) {
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
	std::ifstream myFile(fileName);

	if (!myFile) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	char line[MAX_LEN_LINE];

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

bool updateMovieTitle(const char* oldTitle, const char* newTitle, const char* fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	std::ofstream outFile("temp.txt");
	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		inFile.close();
		return false;
	}
	
	bool titleUpdated = false;
	char line[MAX_LEN_LINE];

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
	if(!secondDelimiter) {
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

bool updateReleaseYear(const char* title, int newReleaseYear, const char* fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return false;
	}

	std::ofstream outFile("temp.txt");
	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		inFile.close();
		return false;
	}

	bool releaseYearUpdated = false;
	char line[MAX_LEN_LINE];

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

bool updateMovieGenre(const char* title, const char* newGenre, const char* fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return false;
	}

	std::ofstream outFile("temp.txt");
	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		inFile.close();
		return false;
	}

	bool genreUpdated = false;
	char line[MAX_LEN_LINE];

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

bool updateMovieDirector(const char* title, const char* newDirector, const char* fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return false;
	}

	std::ofstream outFile("temp.txt");
	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		inFile.close();
		return false;
	}

	bool directorUpdated = false;
	char line[MAX_LEN_LINE];

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

bool updateMovieCast(const char* title, const char* newCast, const char* fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return false;
	}

	std::ofstream outFile("temp.txt");
	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		inFile.close();
		return false;
	}

	bool castUpdated = false;
	char line[MAX_LEN_LINE];

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
bool updateRatingInLine(char* line, int newRating) {
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

	const char* sixthDelimiter = myStrStr(fifthDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS, "/10");
	if (!sixthDelimiter) {
		return false;
	}

	const char* ratingStart = fifthDelimiter + DISTANCE_BETWEEN_MOVIE_PARAMETERS;
	int oldLen = sixthDelimiter - ratingStart;
	int newLen = countDigitsInNumber(newRating);

	int diff = newLen - oldLen;

	if (diff > 0) {
		for (size_t i = MAX_LEN_LINE - 1; i >= (sixthDelimiter - line); --i) {
			if (i + diff < MAX_LEN_LINE) {
				line[i + diff] = line[i];
			}
		}
	}
	else if (diff < 0) {
		for (size_t i = sixthDelimiter - line; i < MAX_LEN_LINE; ++i) {
			line[i + diff] = line[i];
		}
	}

	char* ratingStr = turnRatingToChar(newRating);

	for (size_t i = 0; i < newLen; ++i) {
		line[ratingStart - line + i] = ratingStr[i];
	}

	line[ratingStart - line + newLen] = '/';
	line[ratingStart - line + newLen + 1] = '1';
	line[ratingStart - line + newLen + 2] = '0';

	line[(sixthDelimiter - line) + diff + 3] = '\0';

	delete[] ratingStr;

	return true;
}

bool updateMovieRating(const char* title, int newRating, const char* fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return false;
	}

	std::ofstream outFile("temp.txt");
	if (!outFile.is_open()) {
		std::cerr << "The temporary file couldn't be opened!" << std::endl;
		inFile.close();
		return false;
	}

	bool ratingUpdated = false;
	char line[MAX_LEN_LINE];

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			if (updateRatingInLine(line, newRating)) {
				ratingUpdated = true;
			}
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

		tempFile.close();
		originalFile.close();
	}

	return ratingUpdated;
}


//Sort movies by title
int strCmpTitles(const char* str1, const char* str2) {
	while (*str1 != '\0' && *str1 != '|' && *str2 != '\0' && *str2 != '|') {
		if (*str1 < *str2) return -1;
		if (*str1 > *str2) return 1;
		++str1;
		++str2;
	}
	return 0;
}

void sortMoviesByTitle(char** movies, int movieCount) {
	for (int i = 0; i < movieCount - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < movieCount; ++j) {
			if (strCmpTitles(movies[j], movies[minIndex]) < 0) {
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


//Sort movies by rating
//int extractRating(const char* movie) {
//	int i = 0;
//
//	while (movie[i] != '\0') {
//		++i; 
//	}
//
//	int end = i - 1;
//	while (end >= 0 && (movie[end] < '0' || movie[end] > '9')) {
//		--end; 
//	}
//
//	int start = end;
//	while (start >= 0 && movie[start] >= '0' && movie[start] <= '9') {
//		--start; 
//	}
//	++start;
//
//	int rating = 0;
//	for (int j = start; j <= end; ++j) {
//		rating = rating * 10 + (movie[j] - '0');
//	}
//
//	return rating;
//}

//void sortMoviesByRating(char** movies, int movieCount) {
//	for (int i = 0; i < movieCount - 1; ++i) {
//		int maxIndex = i;
//		for (int j = i + 1; j < movieCount; ++j) {
//			if (extractRating(movies[j]) > extractRating(movies[maxIndex])) {
//				maxIndex = j;
//			}
//		}
//		if (maxIndex != i) {
//			char* temp = movies[i];
//			movies[i] = movies[maxIndex];
//			movies[maxIndex] = temp;
//		}
//	}
//}

//Rate movie
//bool updateMovieRatingToAvg(char** lines, int lineCount, const char* title, int newRating) {
//	for (int i = 0; i < lineCount; ++i) {
//		if (myStrStr(lines[i], title)) {
//			int lastPipe = -1;
//			for (int j = 0; lines[i][j] != '\0'; ++j) {
//				if (lines[i][j] == '|') lastPipe = j;
//			}
//
//			if (lastPipe == -1) continue;
//
//			int currentRating = lines[i][lastPipe + 2] - '0';
//			int averageRating = (currentRating + newRating) / 2;
//
//			lines[i][lastPipe + 2] = averageRating + '0';
//			return true;
//		}
//	}
//
//	return false;
//}
//
//int rateMovie(const char* title, int rating, const char* fileName) {
//	int lineCount = 0;
//	char** lines = readMoviesFromFile(fileName, lineCount);
//	if (!lines) return 1;
//
//	if (!updateMovieRatingToAvg(lines, lineCount, title, rating)) {
//		for (int i = 0; i < lineCount; ++i) delete[] lines[i];
//		delete[] lines;
//		return 1;
//	}
//
//	writeLines(fileName, lines, lineCount);
//	return 0;
//}

//Filter movies by rating
//void filterMoviesByRating(const char* fileName, int userRating) {
//	std::ifstream file(fileName);
//
//	if (!file.is_open()) {
//		std::cerr << fileName << " couldn't be opened!" << std::endl;
//		return;
//	}
//
//	char line[MAX_LEN_LINE];
//	bool found = false;
//
//	while (file.getline(line, MAX_LEN_LINE)) {
//		int rating = -1;
//		int i = 0;
//
//		while (line[i] != '\0') {
//			if (line[i] == '|') {
//				int j = i + 1;
//				while (line[j] != '\0' && line[j] >= '0' && line[j] <= '9') {
//					rating = rating * 10 + (line[j] + TO_INTEGER);
//					++j;
//				}
//			}
//			++i;
//		}
//
//		if (rating >= userRating) {
//			found = true;
//			std::cout << line << std::endl;
//		}
//	}
//
//	if (!found) {
//		std::cout << "No movies found with a rating >= " << userRating << "." << std::endl;
//	}
//
//	file.close();
//}

//Delete movie
std::ofstream createTempFile() {
	std::ofstream tempFile("temp.txt");
	if (!tempFile.is_open()) {
		std::cerr << "Temporary file couldn't be created!" << std::endl;
	}
	return tempFile;
}

bool deleteMovie(std::ifstream& inFile, std::ofstream& outFile, const char* title) {
	char line[MAX_LEN_LINE];
	bool found = false;

	while (inFile.getline(line, MAX_LEN_LINE)) {
		if (myStrStr(line, title)) {
			found = true;
			continue; 
		}
		outFile << line << '\n';
	}

	return found;
}


bool replaceOriginalFile(const char* originalFileName, const char* tempFileName) {
	std::ifstream tempFile(tempFileName);
	if (!tempFile.is_open()) {
		std::cerr << "Error: Could not open the temporary file!" << std::endl;
		return false;
	}

	std::ofstream originalFile(originalFileName, std::ios::trunc);
	if (!originalFile.is_open()) {
		std::cerr << "Error: Could not open the original file!" << std::endl;
		tempFile.close();
		return false;
	}

	char line[MAX_LEN_LINE];
	
	while (tempFile.getline(line, MAX_LEN_LINE)) {
		originalFile << line << std::endl;
	}

	tempFile.close();
	originalFile.close();

	return true;
}


int deleteMovieByTitle(const char* title, const char* fileName) {
	std::ifstream myFile(fileName);
	if (!myFile.is_open()) {
		std::cerr << "Error: Could not open the file '" << fileName << "'!" << std::endl;
		return 1;
	}

	std::ofstream tempFile = createTempFile();
	if (!tempFile.is_open()) {
		std::cerr << "Error: Could not create a temporary file!" << std::endl;
		myFile.close();
		return 1;
	}

	bool found = deleteMovie(myFile, tempFile, title);
	myFile.close();
	tempFile.close();

	if (!found) {
		std::cout << "No movie found with the title '" << title << "'!" << std::endl;
		return 0;
	}

	if (!replaceOriginalFile(fileName, "temp.txt")) {
		std::cerr << "Error: Could not replace the original file!" << std::endl;
		return 1;
	}

	std::cout << "'" << title << "' has been successfully deleted!" << std::endl;
	return 0;
}


int main() {
	char fileName[19] = "MovieDataBase.txt";
	std::cout << "Hello and welcome to my IMDB!\nFirstly, you need to enter your role (user or administrator): ";
	char role[MAX_LEN_ROLE];
	std::cin.getline(role, MAX_LEN_ROLE);

	std::cout << "Now, as an " << toLower(role) << " you can choose one the the options below" << std::endl;
	std::cout << "by typing the digit in front of your chosen option : " << std::endl;

	if (myStrCmp(toLower(role),"user") == 0) {
		
		std::cout << "1. Find movie by genre" << std::endl;
		std::cout << "2. Find movie by title" << std::endl;
		std::cout << "3. View all movies" << std::endl;
		std::cout << "4. Sort movies by title" << std::endl;
		std::cout << "5. Sort movies by rating" << std::endl;
		std::cout << "6. Rate a movie" << std::endl;
		std::cout << "7. Filter movies by rating" << std::endl;
		std::cout << "If you want to exit the program, press - \"CLOSE\"!" << std::endl;

		while (true) {
			char command[MAX_LEN_COMMAND + 1];
			std::cin.getline(command, MAX_LEN_COMMAND);

			if (myStrCmp(command, "1") == 0) {
				char genre1[MAX_LEN_GENRE];
				std::cout << "Enter a movie genre: ";
				std::cin.getline(genre1, MAX_LEN_GENRE);

				findMovieByGenre(genre1, fileName);
			}
			else if (myStrCmp(command, "2") == 0) {
				char movieTitle2[MAX_LEN_MOVIE_TITLES];
				std::cout << "Enter a movie title: ";
				std::cin.getline(movieTitle2, MAX_LEN_MOVIE_TITLES);

				findMovieByTitle(movieTitle2, fileName);
			}
			else if (myStrCmp(command, "3") == 0) {
				showAllMoviesInDatabase(fileName);
			}
			/*else if (myStrCmp(command, "4") == 0) {
				int moviesCountT = countLinesInFile(fileName);
				char** moviesT = readMoviesFromFile(fileName, moviesCountT);
				std::cout << "Movies sorted by title:" << std::endl;
				sortMoviesByTitle(moviesT, moviesCountT);
				printMovies(moviesT, moviesCountT);
				freeMovies(moviesT, moviesCountT);
			}*/
			/*else if (myStrCmp(command, "5") == 0) {
				int moviesCountR = countLinesInFile(fileName);
				char** moviesR = readMoviesFromFile(fileName, moviesCountR);
				std::cout << "Movies sorted by rating: " << std::endl;
				sortMoviesByRating(moviesR, moviesCountR);
				printMovies(moviesR, moviesCountR);
				freeMovies(moviesR, moviesCountR);
			}*/
			/*else if (myStrCmp(command, "6") == 0) {
				char movieTitle6[MAX_LEN_MOVIE_TITLES];
				std::cout << "Movie you want to rate: ";
				std::cin.ignore();

				std::cin.getline(movieTitle6, MAX_LEN_MOVIE_TITLES);

				int newRating;
				std::cout << "Enter your rating for " << movieTitle6 << ": ";
				std::cin >> newRating;

				if (!std::cin || newRating < 0 || newRating>10) {
					std::cerr << "You have entered invalid rating! Your rating must be integer number between 0 and 10!" << std::endl;
					return 1;
				}

				int result = rateMovie(movieTitle6, newRating, fileName);

				if (result == 0) {
					std::cout << "Rating successfully updated!" << std::endl;
				}
				else {
					std::cout << "Failed to update the rating." << std::endl;
				}
			}*/
			/*else if (myStrCmp(command, "7") == 0) {
				int rating;
				std::cout << "Enter rating you want to filter the movies by: ";
				std::cin >> rating;

				filterMoviesByRating(fileName, rating);
			}*/
			else if (myStrCmp(toUpper(command), "CLOSE") == 0) {
				std::cout << "Thank you for using my IMDB! You can exit the program now by pressing 'ENTER'!" << std::endl;
				return 0;
			}
			else {
				std::cout << "Your command is invalid!" << std::endl;
			}
		}
	}
	else if (myStrCmp(toLower(role),"administrator") == 0 || myStrCmp(toLower(role),"admin") == 0) {
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

		while (true) {
			char command[MAX_LEN_COMMAND + 1];
			std::cin.getline(command, MAX_LEN_COMMAND);

			if (myStrCmp(command, "1") == 0) {
				char movieTitle[MAX_LEN_MOVIE_TITLES];
				std::cout << "Input a movie title: ";
				std::cin.getline(movieTitle, MAX_LEN_MOVIE_TITLES + 1);

				char movieGenre[MAX_LEN_GENRE];
				std::cout << "Input a genre: ";
				std::cin.getline(movieGenre, MAX_LEN_GENRE + 1);

				int releaseYear;
				std::cout << "Input the release year of the movie: ";
				std::cin >> releaseYear;
				if (!std::cin || releaseYear < 0) {
					std::cerr << "Invalid input! You have entered and incorrect year!" << std::endl;
					return 1;
				}
				std::cin.ignore();

				char movieDirector[MAX_LEN_MOVIE_DIRECTOR];
				std::cout << "Input the name of the movie director: ";
				std::cin.getline(movieDirector, MAX_LEN_MOVIE_DIRECTOR + 1);

				char movieCast[MAX_LEN_MOVIE_CAST];
				std::cout << "Input the names of the movie cast: ";
				std::cin.getline(movieCast,MAX_LEN_MOVIE_CAST + 1);

				addNewMovieToDataBase(movieTitle, releaseYear, movieGenre, movieDirector, movieCast, fileName);
			
				std::cout << std::endl;
			}
			else if (myStrCmp(command, "2") == 0) {
				std::cout << "Enter your genre: ";
				char genreToFindMovie[MAX_LEN_GENRE];

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
				char option[MAX_LEN_OPTION];
				std::cout << "What do you want to change about a movie? - Enter one of the words \"title\", \"year\", \"genre\", \"director\", \"cast\" or \"rating\" here: ";
				std::cin.getline(option, MAX_LEN_OPTION);
				if (myStrCmp(toLower(option), "title") == 0) {
					std::cout << "Enter the movie you want to change the title of: ";
					char movieToChangeTitleOf[MAX_LEN_MOVIE_TITLES];
					std::cin.getline(movieToChangeTitleOf, MAX_LEN_MOVIE_TITLES);
					std::cout << "Enter new movie title: ";
					char newMovieTitle[MAX_LEN_MOVIE_TITLES];
					std::cin.getline(newMovieTitle, MAX_LEN_MOVIE_TITLES);

					if (updateMovieTitle(movieToChangeTitleOf, newMovieTitle, fileName)) {
						std::cout << "The title of \"" << movieToChangeTitleOf << "\" has been changed to \"" << newMovieTitle << "\" successfully!" << std::endl;
					}
					else {
						std::cout << "The operation wasn't successful!" << std::endl;
					}
					
					std::cout << std::endl;
				}
				else if (myStrCmp(toLower(option), "year") == 0) {
					std::cout << "Enter the title of the movie you want to change the release year of: ";
					char movieToChangeTheReleaseYearOf[MAX_LEN_MOVIE_TITLES];
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
					char movieToChangeGenreOf[MAX_LEN_MOVIE_TITLES];
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
					char movieToChangeTheDirectorOf[MAX_LEN_MOVIE_TITLES];
					std::cin.getline(movieToChangeTheDirectorOf, MAX_LEN_MOVIE_TITLES);
					char newDirector[MAX_LEN_MOVIE_DIRECTOR];
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
					char movieToChangeTheCastOf[MAX_LEN_MOVIE_CAST];
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
						std::cerr << "Invalid input! Your new rating must be a positive integer number between 0 and 10!" << std::endl;
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
				char movieToDelete[MAX_LEN_MOVIE_TITLES];
				std::cout << "Enter the title of the movie you want to delete: ";
				std::cin.getline(movieToDelete, MAX_LEN_MOVIE_TITLES);

				deleteMovieByTitle(movieToDelete, fileName);

				std::cout << "The movie \"" << movieToDelete << "\" has been deleted successfully!" << std::endl;

				std::cout << std::endl;
			}
			//if (myStrCmp(command, "7") == 0) { // Sort movies by title
			//	int moviesCounter = 0;
			//	char** movies = readAndSortMovies(fileName, moviesCounter);

			//	if (!movies) {
			//		std::cerr << "Failed to load movies." << std::endl;
			//		continue;
			//	}

			//	sortMoviesByTitle(movies, moviesCounter);

			//	std::cout << "Movies sorted by title:" << std::endl;
			//	printMovies(movies, moviesCounter);

			//	freeMovies(movies, moviesCounter);
			//}
			/*else if (myStrCmp(command, "8") == 0) {
				int moviesCountToSortByR = countLinesInFile(fileName);
				char** moviesToSortByRating = readMoviesFromFile(fileName, moviesCountToSortByR);
				std::cout << "Movies sorted by rating: " << std::endl;
				sortMoviesByRating(moviesToSortByRating, moviesCountToSortByR);
				printMovies(moviesToSortByRating, moviesCountToSortByR);
				freeMovies(moviesToSortByRating, moviesCountToSortByR);
			}*/
			/*else if (myStrCmp(command, "9") == 0) {
				int rating;
				std::cout << "Enter rating you want to filter the movies by: ";
				std::cin >> rating;

				filterMoviesByRating(fileName, rating);
			}*/
			else if (myStrCmp(toUpper(command), "CLOSE") == 0) {
				std::cout << "Thank you for using my IMDB! You can exit the program now by pressing 'ENTER'!" << std::endl;
				return 0;
			}
			else {
				std::cerr << "Your command is invalid!" << std::endl;
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
