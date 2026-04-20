#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class KeyValueStore {
private:
    unordered_map<string, pair<string, time_t>> store;
    const string filename = "data.db";

public:
    // Load from file
    void load() {
        ifstream file(filename);
        if (!file.is_open()) return;

        string line, key, value;
        time_t expiry;

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, key, '=');
            getline(ss, value, '=');
            ss >> expiry;

            store[key] = {value, expiry};
        }
        file.close();
    }

    // Save to file
    void persist() {
        ofstream file(filename);
        for (auto &p : store) {
            file << p.first << "=" << p.second.first << "=" << p.second.second << endl;
        }
        file.close();
    }

    // PUT
    void put(string key, string value, int ttl) {
        time_t expiry = time(0) + ttl;
        store[key] = {value, expiry};
        persist();
        cout << "OK\n";
    }

    // GET
    void get(string key) {
        if (store.find(key) != store.end()) {
            time_t now = time(0);

            if (store[key].second < now) {
                store.erase(key);
                cout << "Key expired\n";
                return;
            }

            cout << store[key].first << endl;
        } else {
            cout << "Key not found\n";
        }
    }

    // DELETE
    void del(string key) {
        if (store.erase(key)) {
            persist();
            cout << "Deleted\n";
        } else {
            cout << "Key not found\n";
        }
    }

    // CLI
    void run() {
        load();
        cout << "Key-Value Store with TTL 🚀\n";

        string command;
        while (true) {
            cout << "> ";
            cin >> command;

            if (command == "PUT") {
                string key, value;
                int ttl;
                cin >> key >> value >> ttl;
                put(key, value, ttl);
            }
            else if (command == "GET") {
                string key;
                cin >> key;
                get(key);
            }
            else if (command == "DELETE") {
                string key;
                cin >> key;
                del(key);
            }
            else if (command == "EXIT") {
                break;
            }
            else {
                cout << "Invalid command\n";
            }
        }
    }
};

int main() {
    KeyValueStore kv;
    kv.run();
    return 0;
}