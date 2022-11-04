#pragma once
#include <string>

using namespace std;
class User {
private:
	string _login;
	string _pass;
	string _name;
public:
	User(string login, string pass, string name) : _login(login), _pass(pass), _name(name) {}
	string getLogin() { return _login; }
	string getPass() { return _pass; }
	string getName() { return _name; }
};