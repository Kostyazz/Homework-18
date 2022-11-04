#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "User.h"
#include "Message.h"

using namespace std;
namespace fs = std::filesystem;

int main()
{
	vector<User> users;
	vector<Message> messages;
	//if files don't exist, create them
	ifstream fin;
	ofstream fout;
	fin.open("Users.txt");
	if (!fin.is_open()) {
		fout.open("Users.txt");
		fout.close();
	} else {
		fin.close();
	}
	fin.open("Messages.txt");
	if (!fin.is_open()) {
		fout.open("Messages.txt");
		fout.close();
	}
	else {
		fin.close();
	}
	//fill users array with login credentials from "Users.txt"
	//separator is ' '
	try {
		ifstream loginFile;
		loginFile.open("Users.txt");
		if (!loginFile.is_open()) {
			throw runtime_error("ERROR: Login file not found");
		}
		while (! loginFile.eof()) {
			string login;
			string password;
			string name;
			loginFile >> login >> password >> name;
			if (login.empty()) {
				break;
			}
			loginFile.ignore();
			if (name.empty()) {
				throw runtime_error("ERROR: bad credentials in the file");
			}
			users.emplace_back(User(login, password, name));
		}
	}
	catch (runtime_error& ex) {
		cerr << ex.what() << endl;
		exit(1);
	}

	try {
		ifstream messageFile;
		messageFile.open("Messages.txt");
		if (!messageFile.is_open()) {
			throw runtime_error("ERROR: Message file not found");
		}
		while (! messageFile.eof()) {
			string sender;
			string receiver;
			string text;
			messageFile >> sender >> receiver;
			if (sender.empty()) {
				break;
			}
			getline(messageFile, text);
			if (text.empty()) {
				throw runtime_error("ERROR: bad data in the file");
			}
			messages.emplace_back(Message(sender, receiver, text));
		}
	}
	catch (runtime_error& ex) {
		cerr << ex.what() << endl;
		exit(1);
	}

	try {
		ofstream loginFile;
		loginFile.open("Users.txt");
		if (!loginFile.is_open()) {
			throw runtime_error("ERROR: Login file not found");
		}
		for (auto user : users) {
			loginFile << user.getLogin() << " " << user.getPass() << " " << user.getName() << endl;
		}
	}
	catch (runtime_error& ex) {
		cerr << ex.what() << endl;
		exit(1);
	}
	try {
		ofstream messageFile;
		messageFile.open("Messages.txt");
		if (!messageFile.is_open()) {
			throw runtime_error("ERROR: Login file not found");
		}
		for (auto message : messages) {
			messageFile << message.getSender() << " " << message.getReceiver() << " " << message.getText() << endl;
		}
	}
	catch (runtime_error& ex) {
		cerr << ex.what() << endl;
		exit(1);
	}

	//change files permissions
	fs::permissions("Users.txt", fs::perms::owner_read | fs::perms::owner_write, fs::perm_options::replace);
	fs::permissions("Messages.txt", fs::perms::owner_read | fs::perms::owner_write, fs::perm_options::replace);
}
