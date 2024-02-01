#include <iostream>

using namespace std;

void help()
{
    cout << "\n \nVersion 1.0" << endl;
    cout << "Usage:     dankwd <flag> <password>" << endl;
    cout << "Options:" << endl;
    cout << "\t -t \t test password \t compares password to common passwords" << endl;
    cout << "\t -p \t checks strength of password" << endl;
    cout << "\t -d \t checks how long it will take to crack password" << endl;
    cout << "\t -a \t does all the flags" << endl;
}

void test()
{
    //check rockyou.txt and other common password files for that password
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


    if(argc == 1)
    {
        help();
    }

    if(argc > 3)    //if there are more than 3 arguements getting passed
    {
        help();
        return 0;
    }
    
    if(argv[1] == "-h")
        help();
    else if (argv[1] == "-t")
        test();
    else if (argv[1] == "-p")
        password();
    else if (argv[1] == "-d")
        crack();
    else if (argv[1] == "-a")
        all();
    else
        cout << "Unknown flag: for usage do -h" << endl;

    return 0;
}