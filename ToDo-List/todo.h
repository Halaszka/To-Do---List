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

	vector<string> lines;

	while (getline(read_file, line)) {
		lines.push_back(line);

		line = "";
	}


	ofstream write_file("C:\\To-Do\\todo.txt");

	if (write_file.fail()) {
		return -1;
	}

	for (int i = 0; i != lines.size(); i++) {
		if (lines.at(i).size() >= 2 && lines.at(i).find(Name) == std::string::npos) {
			write_file << lines.at(i) << "\n";
		}
	}

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