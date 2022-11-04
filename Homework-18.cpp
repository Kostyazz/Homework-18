#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class User {
    string _login;
    string _pass;
	string _name;
public:
	User(string login, string pass, string name) : _login(login), _pass(pass), _name(name) {};
};
class Message {
    string _sender;
    string _receiver;
	string _text;
public:
	Message(string sender, string receiver, string text) : _sender(sender), _receiver(receiver), _text(text) {};
};

int main()
{
	vector<User> users;
	vector<Message> messages;
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


}
