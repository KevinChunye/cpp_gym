#include <iostream>
#include <algorithm>   // sort, random_shuffle
#include <vector>
using namespace std;


// MESSAGE CLASS
// Stores text + a creation-order stamp so messages can be re-sorted
// after the network shuffles them.
class Message {
public:
    static int index;

    int order;     
    string text;   

    // empty constructor -- required by the problem spec
    // captures the current index as this message's order stamp, then advances index
    Message() {
        order = index;   // stamp this message: 0, 1, 2, 3...
        index++;         // next message gets the next number
    }

    // getter -- returns text by const reference (no copy, no modification allowed)
    const string& get_text() {
        return text;
    }

    // < operator -- required by std::sort in fix_order()
    // sorts messages by their creation stamp (ascending)
    // lower order number = was created earlier = should print first
    bool operator<(const Message& other) {
        return order < other.order;
    }
};

// static member must be defined outside the class
// starts at 0, increments with each new Message constructed
int Message::index = 0;


class MessageFactory {
public:
    MessageFactory() {}   // empty constructor required by spec

    // creates a Message, assigns its text, and returns it
    // the stamp is set automatically inside Message() constructor
    // so by the time we set text, order is already correct
    Message create_message(const string& text) {
        Message a;        // order stamp assigned here inside Message()
        a.text = text;    // attach the text content
        return a;
    }
};


// Collects incoming messages into a vector,
// then sorts and prints them on demand.
class Recipient {
public:
    Recipient() {}

    // called by Network for each delivered message
    // just appends to internal vector regardless of arrival order
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }

    void print_messages() {
        fix_order();                          // sort before printing
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();                    // reset after printing
    }

private:
    // uses std::sort which calls Message::operator< to compare
    // this is why operator< must be implemented in Message
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }

    vector<Message> messages_;   // stores received messages in arrival order
};


// Simulates an unreliable network that delivers messages out of order.
class Network {
public:
    // takes messages BY VALUE (copy) so original order is not affected
    // random_shuffle reorders the copy, then delivers each to recipient
    static void send_messages(vector<Message> messages, Recipient& recipient) {
        random_shuffle(messages.begin(), messages.end());
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};

int main() {
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;

    string text;
    // reads lines until EOF, creates a stamped Message for each line
    // stamp order matches reading order = original sent order
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
    }

    // shuffle and deliver
    Network::send_messages(messages, recipient);

    // sort by stamp and print
    recipient.print_messages();
}