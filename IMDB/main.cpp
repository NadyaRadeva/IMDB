#include<iostream>
#include<fstream>

const int MAX_LEN_ROLE = 14;
const int MAX_LEN_COMMAND = 6;
const int TO_LOWER_CASE_CHANGE = 'a' - 'A';
const int TO_UPPER_CASE_CHANGE = 'A' - 'a';
const int TO_CHAR = '0';
const int TO_INTEGER = -'0';
const int DEFAULT_RATING = 5;
const int MAX_LEN_GENRE = 100;
const int MAX_LEN_MOVIE_TITLES = 1000;
const int MAX_LEN_MOVIE_DIRECTOR = 500;
const int MAX_LEN_MOVIE_CAST = 2056;
const int MAX_LEN_LINE = 3673; // MAX_LEN_MOVIE_TITLES + MAX_LEN_MOVIE_DIRECTOR + MAX_LEN_MOVIE_CAST + RATING (MAX - 2 digits) + 10 spaces + 5 lines

//Base Functions
bool isLowerCase(char c);
bool isUpperCase(char c);
int findTextLen(const char* text);
char* toLower(char* userInput);
int myStrCmp(const char* str1, const char* str2);
char* myStrStr(const char* str1, const char* str2);
bool contains(const char* str1, const char* str2);
std::ofstream createTempFile();
int countLinesInFile(const char* fileName);
void myStrCpy(const char* source, char* dest);

//Main Functions
int addNewMovieToDataBase(const char* title, int year, const char* genre, const char* director, const char* cast, const char* fileName);
int findMovieByGenre(const char* genre, const char* fileName);
int findMovieByTitle(const char* title, const char* fileName);
int printAllMoviesInfo(const char* fileName);
bool deleteMovie(std::ifstream& myFile, std::ofstream& tempFile, const char* title);
bool replaceOriginalFile(const char* fileName);
int deleteMovieByTitle(const char* title, const char* fileName);



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

bool contains(const char* str1, const char* str2) {
	return myStrStr(str1, str2) != nullptr;
}

int countLinesInFile(const char* fileName) {
	std::ifstream myFile(fileName);
	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return -1;
	}

	int lineCount = 0;
	char lines[1024];

	while (myFile.getline(lines, sizeof(lines))) {
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

int findMovieByGenre(const char* genre, const char* fileName) {
	std::ifstream myFile(fileName);

	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	char line[MAX_LEN_LINE];
	bool found = false;

	std::cout << "Movies in the genre '" << genre << "': " << std::endl;
	while (myFile.getline(line, sizeof(line))) {
		if (contains(line, genre)) {
			std::cout << line << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "No movies found in the genre '" << genre << "!" << std::endl;
	}

	myFile.close();
	return 0;
}

int findMovieByTitle(const char* title, const char* fileName) {
	std::ifstream myFile(fileName);

	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	char line[MAX_LEN_LINE];
	bool found = false;

	std::cout << "Movies in the genre '" << title << "': " << std::endl;
	while (myFile.getline(line, sizeof(line))) {
		if (contains(line, title)) {
			std::cout << line << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "No movies found with the title '" << title << "!" << std::endl;
	}

	myFile.close();
	return 0;
}

int printAllMoviesInfo(const char* fileName) {
	std::ifstream myFile(fileName);

	myFile.open(fileName);

	if (!myFile) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return 1;
	}

	char line[MAX_LEN_LINE];

	while (!myFile.eof()) {
		myFile.getline(line, MAX_LEN_LINE);

		std::cout << line << std::endl;
	}

	myFile.close();
	return 0;
}

int changeMovieInfoTitle(const char* newTitle, const char* fileName) {

}

int changeMovieInfoGenre(const char* newGenre, const char* fileName) {

}

int changeMovieInfoDirector(const char* newDirector, const char* fileName) {

}

int changeMovieInfoCast(const char* newCast, const char* fileName) {

}

void readMoviesFromFile(const char* fileName, char movies[][MAX_LEN_LINE], int movieCount) {
	std::ifstream myFile(fileName);
	if (!myFile.is_open()) {
		std::cerr << fileName << " couldn't be opened!" << std::endl;
		return;
	}

	for (int i = 0; i < movieCount; ++i) {
		myFile.getline(movies[i], MAX_LEN_LINE);
	}

	myFile.close();
}

void sortMoviesByTitle(char movies[][MAX_LEN_LINE], int movieCount) {
	for (int i = 0; i < movieCount - 1; ++i) {
		for (int j = i + 1; j < movieCount; ++j) {
			if (myStrCmp(movies[i], movies[j]) > 0) {
				char temp[MAX_LEN_LINE];
				myStrCpy(temp, movies[i]);
				myStrCpy(movies[i], movies[j]);
				myStrCpy(movies[j], temp);
			}
		}
	}
}

void printMovies(const char movies[][MAX_LEN_LINE], int movieCount) {
	for (int i = 0; i < movieCount; ++i) {
		std::cout << movies[i] << std::endl;
	}
}

//Delete movie
std::ofstream createTempFile() {
	std::ofstream tempFile("temp.txt");
	if (!tempFile.is_open()) {
		std::cerr << "Temporary file couldn't be created!" << std::endl;
	}
	return tempFile;
}

bool deleteMovie(std::ifstream& myFile, std::ofstream& tempFile, const char* title) {
	char line[MAX_LEN_LINE];
	bool found = false;

	while (myFile.getline(line, sizeof(line))) {
		if (contains(line, title)) {
			found = true;
		}
		else {
			tempFile << line << std::endl;
		}
	}

	return found;
}

bool replaceOriginalFile(const char* fileName) {
	if (remove(fileName) != 0) {
		std::cerr << "Error deleting the original file!" << std::endl;
		return false;
	}

	if (rename("temp.txt", fileName) != 0) {
		std::cerr << "Error renaming the temporary file!" << std::endl;
		return false;
	}

	return true;
}

int deleteMovieByTitle(const char* title, const char* fileName) {
	std::ifstream myFile(fileName);

	if (!myFile.is_open()) {
		return 1;
	}

	std::ofstream tempFile = createTempFile();
	if (!tempFile.is_open()) {
		return 1;
	}

	bool found = deleteMovie(myFile, tempFile, title);
	myFile.close();
	tempFile.close();

	if (!found) {
		std::cout << "No movie found with the title '" << title << "'!" << std::endl;
		return 0;
	}

	if (!replaceOriginalFile(fileName)) {
		return 1;
	}

	std::cout << title << "' has been successfully deleted!" << std::endl;

	return 0;
}

int main() {
	char fileName[19] = "MovieDataBase.txt";
	std::cout << "Hello and welcome to my IMDB!\nFirstly, you need to enter your role (user or administrator): ";
	char role[MAX_LEN_ROLE];
	std::cin.getline(role, MAX_LEN_ROLE);

	std::cout << "Now, as an " << toLower(role) << " you can choose one the the options below" << std::endl;
	std::cout << "by typing the digit in front of your chosen option : " << std::endl;

	char command[MAX_LEN_COMMAND];

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
			if (myStrCmp(command, "1") == 0) {
				char genre[MAX_LEN_GENRE];
				std::cout << "Enter a genre: ";
				std::cin.getline(genre, MAX_LEN_GENRE + 1);

				findMovieByGenre(genre, fileName);
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
		std::cout << "7. Sort movies by rating" << std::endl;
		std::cout << "8. Filter movies by rating" << std::endl;
		std::cout << "If you want to exit the program, press - \"CLOSE\"!" << std::endl;

		while (true) {
			if (myStrCmp(command, "1") == 0) {
				char movieTitle[MAX_LEN_MOVIE_TITLES];
				std::cout << "Input a movie title: ";
				std::cin.ignore();
				std::cin.getline(movieTitle, MAX_LEN_MOVIE_TITLES + 1);

				char movieGenre[MAX_LEN_GENRE];
				std::cout << "Input a genre: ";
				std::cin.ignore();
				std::cin.getline(movieGenre, MAX_LEN_GENRE + 1);

				int releaseYear;
				std::cout << "Input the release year of the movie: ";
				std::cin >> releaseYear;
				if (!std::cin || releaseYear < 0) {
					std::cerr << "Invalid input! You have entered and incorrect year!" << std::endl;
					return 1;
				}

				char movieDirector[MAX_LEN_MOVIE_DIRECTOR];
				std::cout << "Input the names of the movie director: ";
				std::cin.ignore();
				std::cin.getline(movieDirector, MAX_LEN_MOVIE_DIRECTOR + 1);

				char movieCast[MAX_LEN_MOVIE_CAST];
				std::cout << "Input the names of the movie cast: ";
				std::cin.ignore();
				std::cin.getline(movieCast,MAX_LEN_MOVIE_CAST + 1);

				addNewMovieToDataBase(movieTitle, releaseYear, movieGenre, movieDirector, movieCast, fileName);
			}
		}

	}
	else {
		std::cerr << "Invalid input - you have entered and invalid role! Please try again!" << std::endl;
		return 1;
	}

	return 0;
}