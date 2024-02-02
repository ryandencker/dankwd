#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <random>

using namespace std;

unordered_set<string> loadPasswords(const string& filename) {
    unordered_set<string> passwords;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
    } else {
        string line;
        while (getline(file, line)) {
            passwords.insert(line);
        }
    }

    return passwords;
}

void help()
{
    cout << "\n \nVersion 1.0" << endl;
    cout << "Usage:     dankwd <flag> <password>" << endl;
    cout << "Options:" << endl;
    cout << "\t -t \t compares password to large wordlists of common passwords" << endl;
    cout << "\t -p \t checks strength of password" << endl;
    cout << "\t -d \t checks how long it will take to crack password" << endl;
    cout << "\t -a \t does all the flags" << endl;
}

bool isInWordlists(const unordered_set<string>& rockYouPasswords, const unordered_set<string>& customPasswords, const unordered_set<string>& handsomePasswords, const string& password) {
    return rockYouPasswords.find(password) != rockYouPasswords.end() ||
           customPasswords.find(password) != customPasswords.end() ||
           handsomePasswords.find(password) != handsomePasswords.end();
}

void test(string usrpswd)
{
    cout << "Please wait while searching through wordlists..." << endl;
    unordered_set<string> rockYou = loadPasswords("Wordlists/rockyou.txt");
    unordered_set<string> xato = loadPasswords("Wordlists/xato-net-10-million-passwords.txt");
    unordered_set<string> human = loadPasswords("Wordlists/realhuman_phill.txt");
    bool safe = true;

    if(isInWordlists(rockYou, xato, human, usrpswd))
    {
        cout << "Your password was found in one of the wordlists and is not secure" << endl;
        return;
    }
    else
    {
        cout << "Your password was not found in our wordlists" << endl;
        return;
    }
}

void password()
{
    //check password for uppercase, lowercase, special characters
}

void crack()
{
    //calculate how long it will take to crack assuming it is a strong password
}

void all()
{
    //do test(), password(), and crack()
}

int main(int argc, char *argv[])    //argc is the number of commandline arguments recieved, argv is the strings
{
    

    //random dankwd text


    if(argc == 1)   //if user only runs the executable
    {
        help();
        return 0;
    }

    if(argc > 3)    //if there are too many arguements getting passed
    {
        help();
        return 0;
    }

    string flag = argv[1];
    string usrpswd = argv[2];

    if(flag == "-h") //not working, everything else after working
        help();
    else if (flag == "-t")
        test(usrpswd);
    else if (flag == "-p")
        password();
    else if (flag == "-d")
        crack();
    else if (flag == "-a")
        all();
    else
        cout << "Unknown flag: for usage do -h" << endl;

    return 0;
}