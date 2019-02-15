// Classwork 1 Dictionary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h> 
#include <sstream>
#include <conio.h>

namespace fs = std::filesystem;

#pragma warning(disable : 4996);



struct vocab {
	char russian[64];
	char english[64];
};


void gotoxy(int x, int y);
int DisplayMainMenu();
void adding();
void finding();


int main()
{
	while (1)
	{
		int selection = DisplayMainMenu();
		switch (selection)
		{
		case 1:
			adding();
			break;
		case 2:
			finding();
			break;
		case 3:
		default:
			return 0;
		};
	}
	return 0;

}

void adding() {

	bool boolean = true;

	while (boolean == true) {
		::system("cls");

		gotoxy(5, 4);
		std::cout << "___________________________________________";

		gotoxy(5, 6);
		std::cout << "Russian: ";

		gotoxy(5, 7);
		std::cout << "English: ";

		gotoxy(5, 8);
		std::cout << "___________________________________________";

		gotoxy(18, 6);
		char russian[64];
		std::cin >> russian;

		gotoxy(17, 7);
		char english[64];
		std::cin >> english;

		FILE *system_data;
		system_data = fopen("system.txt", "r");
		int id;
		fscanf(system_data, "%d", &id);
		fclose(system_data);
		id++;

		system_data = fopen("system.txt", "w");
		fprintf(system_data, "%d", id);
		fclose(system_data);

		char filename[25];
		std::string str_filename;
		str_filename = std::to_string(id) + ".dat";
		std::stringstream(str_filename) >> filename;

		char pathFile[100] = "C:\\Julia\\Programming\\Classwork\\Classwork 1 Dictionary\\Classwork 1 Dictionary\\Words\\";

		FILE *items;

		char path_file[125];
		path_file[0] = '\0';
		strcat(path_file, pathFile);
		strcat(path_file, filename);

		
		items = fopen(path_file, "w+b");
		vocab m;
		strncpy(m.english, english, sizeof(english));
		strncpy(m.russian, russian, sizeof(russian));
		fwrite(&m, sizeof(m), 1, items);
		fclose(items);

		gotoxy(5, 11);
		std::cout << "Do you want to add another word (Y/N)? ";
		char ch = getch();
		if (ch == 'Y' || ch == 'y')
			continue;
		else
		{
			break;
		}
	}


}

int DisplayMainMenu()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. Add words";

	gotoxy(5, 7);
	std::cout << "2. Find words";

	gotoxy(5, 8);
	std::cout << "3. Exit";

	gotoxy(5, 9);
	std::cout << "___________________________________________";

	gotoxy(5, 13);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

void gotoxy(int x, int y)
{
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void finding() {

	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "English - ";

	gotoxy(5, 7);
	std::cout << "___________________________________________";


	char english[25];
	gotoxy(16, 6);
	std::cin >> english;


	FILE *items;
	std::string path = "C:\\Julia\\Programming\\Classwork\\Classwork 1 Dictionary\\Classwork 1 Dictionary\\Words";
	bool success = false;

	for (const auto & entry : fs::directory_iterator(path)) {

		std::filesystem::path my_path = entry.path();
		items = fopen(my_path.string().c_str(), "r+b");
		vocab word;
		fread(&word, sizeof(word), 1, items);
		if (strcmp(word.english, english)==0) {
			gotoxy(5, 8);
			std::cout << "Russian - " << word.russian;
			success = true;
		}
		fclose(items);
	}

	if (success == false)
		std::cout << "No words found";
	char ch = getch();
}

