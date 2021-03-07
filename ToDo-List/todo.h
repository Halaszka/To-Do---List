#pragma once
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

vector<string> entries;

int createToDo() {

	int rc;

	rc = CreateDirectoryA("C:\\To-Do", NULL);

	if (rc != 0) {
		return 0;
	}
	else {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			return 0;
		}
		else {
			return -1;
		}
	}

}

int createToDoTXT() {

	ofstream file("C:\\To-Do\\todo.txt", ios::app);

	if (file.fail()) {
		file.close();
		return -1;
	}
	else {
		file.close();
		return 0;
	}

}

int getList() {
	ifstream file("C:\\To-Do\\todo.txt");

	if (file.fail()) {
		return -1;
	}
	else {
		string line;

		while (getline(file, line)) {
			entries.push_back(line);
		}
	}

	file.close();

	return 0;
}

int deleteItem(string Name) {
	ifstream read_file("C:\\To-Do\\todo.txt");

	if (read_file.fail()) {
		return -1;
	}

	string line;
	string result = "";

	while (getline(read_file, line)) {
		result += line;
		result += "\n";

		line = "";
	}

	result.replace(result.find(Name), Name.size(), "");


	ofstream write_file("C:\\To-Do\\todo.txt");

	if (write_file.fail()) {
		return -1;
	}

	write_file << result;

	write_file.close();
	read_file.close();

	return 0;
}

int addItem(string Name) {

	ofstream write_file("C:\\To-Do\\todo.txt", ios::app);

	if (write_file.fail()) {
		return -1;
	}

	write_file << Name << "\n";

	write_file.close();

	return 0;
}