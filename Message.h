#pragma once
#include <string>

using namespace std;
class Message {
	string _sender;
	string _receiver;
	string _text;
public:
	Message(string sender, string receiver, string text) : _sender(sender), _receiver(receiver), _text(text) {}
	string getSender() { return _sender; }
	string getReceiver() { return _receiver; }
	string getText() { return _text; }
};