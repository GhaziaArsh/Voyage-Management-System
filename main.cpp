#include <iostream>
#include <fstream>
#include <string>

#include <conio.h>
#include <windows.h>
#include <thread>

#ifdef _WIN32
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN    "\033[36m"
#else
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN    "\033[36m"
#endif

using namespace std;

namespace std {


    string getMaskedInput() {
        string password;
        char ch;
    #ifdef _WIN32
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
    #else
        struct termios oldTerm, newTerm;
        tcgetattr(STDIN_FILENO, &oldTerm);
        newTerm = oldTerm;
        newTerm.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);
        while ((ch = getchar()) != '\n') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
    #endif
        cout << endl;
        return password;
    }

}


void clearScreen()
 {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void gotoRowCol(int rpos, int cpos)
{
	int xpos=cpos, ypos = rpos;
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
const string MANAGER_ID = "admin";
const string MANAGER_PASSWORD = "admin";

class Person
 {
protected:
    string name;
    int age;
    string sex;
    string address;
    string phone;

public:
    Person(string nm = "Null", int ag = 0, string sx = "Null", string addr = "Null", string ph = "Null")
         {

         name=nm;
          age=ag;
           sex=sx;
            address=addr;
             phone=ph;
         }

    virtual void enterDetails()
    {
        cout << BLUE << "Enter Name: " << RESET;
        cin.ignore();
        getline(cin, name);
        cout << CYAN << "Enter Age: " << RESET;
        cin >> age;
        cout << GREEN << "Enter Sex: " << RESET;
        cin.ignore();
        getline(cin, sex);
        cout << YELLOW << "Enter Address: " << RESET;
        getline(cin, address);
        cout << RED << "Enter Phone Number: " << RESET;
        getline(cin, phone);
    }

    virtual void displayDetails() const
     {
        cout << GREEN << "Name: " << RESET << name << endl;
        cout << BLUE << "Age: " << RESET << age << endl;
        cout << CYAN << "Sex: " << RESET << sex << endl;
        cout << RED << "Address: " << RESET << address << endl;
        cout << MAGENTA << "Phone: " << RESET << phone << endl;
    }

    virtual void saveToFile(ofstream &ofs) const
    {
        ofs << name << '\n' << age << '\n' << sex << '\n' << address << '\n' << phone << '\n';
    }

    virtual void loadFromFile(ifstream &ifs)
     {
        getline(ifs, name);
        ifs >> age;
        ifs.ignore();
        getline(ifs, sex);
        getline(ifs, address);
        getline(ifs, phone);
    }
};

class Journey
{
protected:
    string source;
    string destination;
    string date;
    int duration;

public:
    Journey(string src = "Undefined", string dest = "Undefined", string dt = "Undefined", int dur = 0)
         {
             source=src;
              destination=dest;
              date=dt;
               duration=dur;
         }

    virtual void enterDetails()
     {
        cout << BLUE << "Enter Source: " << RESET;
        cin.ignore();
        getline(cin, source);
        cout << YELLOW << "Enter Destination: " << RESET;
        getline(cin, destination);
        cout << GREEN << "Enter Date: " << RESET;
        getline(cin, date);
        cout << RED << "Enter Duration (in days): " << RESET;
        cin >> duration;
    }

    virtual void displayDetails() const
     {
        cout << GREEN << "Source: " << RESET << source << endl;
        cout << CYAN << "Destination: " << RESET << destination << endl;
        cout << RED << "Date: " << RESET << date << endl;
        cout << BLUE << "Duration: " << RESET << duration << " days" << endl;
    }

    int getTicketPrice() const
     {
        return 50 * duration;
    }

    virtual void saveToFile(ofstream &ofs) const
    {
        ofs << source << '\n' << destination << '\n' << date << '\n' << duration << '\n';
    }

    virtual void loadFromFile(ifstream &ifs)
     {
        getline(ifs, source);
        getline(ifs, destination);
        getline(ifs, date);
        ifs >> duration;
        ifs.ignore();
    }
};

class Food
{
protected:
    int chinese;
    int indian;
    int other;
    string extraPreferences;

public:
    Food(int chi = 0, int ind = 0, int oth = 0, string extra = "None")
         {
         chinese=chi;
          indian=ind;
           other=oth;
            extraPreferences=extra;


         }

    virtual void enterDetails()
     {
        cout << BLUE << "Do you want Chinese food (1/0): " << RESET;
        cin >> chinese;
        cout << MAGENTA << "Do you want Indian food (1/0): " << RESET;
        cin >> indian;
        cout << RED << "Do you want to add some extra food like snacks etc (1/0): " << RESET;
        cin >> other;
        cout << GREEN << "Enter extra food preferences: " << RESET;
        cin.ignore();
        getline(cin, extraPreferences);
    }

    virtual void displayDetails() const
    {
        cout << GREEN << "Chinese: " << RESET << chinese << endl;
        cout << RED << "Indian: " << RESET << indian << endl;
        cout << YELLOW << "Other: " << RESET << other << endl;
        cout << MAGENTA << "Extra Preferences: " << RESET << extraPreferences << endl;
    }

    int calculateFoodExpenses() const
    {
        return (chinese * 10) + (indian * 8) + (other * 12);
    }

    virtual void saveToFile(ofstream &ofs) const
    {
        ofs << chinese << '\n' << indian << '\n' << other << '\n' << extraPreferences << '\n';
    }

    virtual void loadFromFile(ifstream &ifs)
     {
        ifs >> chinese >> indian >> other;
        ifs.ignore();
        getline(ifs, extraPreferences);
    }
};

class Activities
{
protected:
    int swimming;
    int theatre;
    int casino;
    int indoorSports;

public:
    Activities(int swim = 0, int theat = 0, int cas = 0, int indoor = 0)
         {
         swimming=swim;
          theatre=theat;
           casino=cas;
            indoorSports=indoor;


         }

virtual void enterDetails()
 {
    cout << BLUE << "Do you want swimming activities (1/0): " << RESET;
    cin >> swimming;
    cout << MAGENTA << "Do you want theatre activities (1/0): " << RESET;
    cin >> theatre;
    cout << RED << "Do you want casino activities (1/0): " << RESET;
    cin >> casino;
    cout << CYAN << "Do you want indoor sports activities (1/0): " << RESET;
    cin >> indoorSports;
}

    virtual void displayDetails() const {
    cout << CYAN << "Swimming: " << swimming << endl;
    cout << GREEN << "Theatre: " << theatre << endl;
    cout << YELLOW << "Casino: " << casino << endl;
    cout << MAGENTA << "Indoor Sports: " << indoorSports << endl << RESET;
}

    int calculateActivityExpenses() const
     {
        return (swimming * 5) + (theatre * 7) + (casino * 15) + (indoorSports * 6);
    }

    virtual void saveToFile(ofstream &ofs) const
     {
        ofs << swimming << '\n' << theatre << '\n' << casino << '\n' << indoorSports << '\n';
    }

    virtual void loadFromFile(ifstream &ifs)
    {
        ifs >> swimming >> theatre >> casino >> indoorSports;
        ifs.ignore();
    }
};

class Package : public Person, public Journey, public Food, public Activities
{
protected:
    int totalExpenses;

public:
    Package()
    {
     totalExpenses=0;
    }

    void calculateTotalExpenses()
    {
        totalExpenses = getTicketPrice() + calculateFoodExpenses() + calculateActivityExpenses();
    }

    void enterDetails()
    {
        Person::enterDetails();
        Journey::enterDetails();
        Food::enterDetails();
        Activities::enterDetails();
        calculateTotalExpenses();
    }

    void displayDetails() const
    {
        Person::displayDetails();
        Journey::displayDetails();
        Food::displayDetails();
        Activities::displayDetails();
        cout << "Total Expenses: $" << totalExpenses << endl;
    }
};



class User : public Person
{
private:
    string password;
    Journey journey;
    Food food;
    Activities activities;
    bool bookingCancelled;

public:
    User(const string& nm = "", int ag = 0, const string& sx = "", const string& addr = "", const string& ph = "", const string& pwd = "")
        : Person(nm, ag, sx, addr, ph), password(pwd), bookingCancelled(false) {}

    string getName() const
     {
        return name;
    }
    string getPassword() const
     {
          return password;
      }
    bool isBookingCancelled() const
     {
        return bookingCancelled;
         }

    void cancelBooking()
     {
        bookingCancelled = true;
        }

    void enterDetails()
     {
        bool choice;
        string password_1;
        string password_2;
        journey.enterDetails();
        food.enterDetails();
        activities.enterDetails();
        cout << "Do you want to edit personal details (1/0)? ";
        cin >> choice;
        if (choice == 1)
            {
            Person::enterDetails();
        }
        cout << "Do you want to update your password (1/0)? ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter New Password: ";
            cin >> password_1;
            cout << "Confirm Password: ";
            cin >> password_2;
            if (password_1 == password_2)
            {
                password = password_1;
                cout << "Successfully Updated the password." << endl;
            }
        else
            {
                cout << "Password Update Failed!!!" << endl;
            }
        }
    }

    void displayDetails() const
     {
        Person::displayDetails();
        journey.displayDetails();
        food.displayDetails();
        activities.displayDetails();
        cout << "Booking Cancelled: " << (bookingCancelled ? "Yes" : "No") << endl;
    }

    void editDetails()
    {
        enterDetails();
    }

    int calculateTotalExpenses() const
    {
        return journey.getTicketPrice() + food.calculateFoodExpenses() + activities.calculateActivityExpenses();
    }

    void saveToFile(ofstream &ofs) const
    {
        Person::saveToFile(ofs);
        ofs << password << '\n' << bookingCancelled << '\n';
        journey.saveToFile(ofs);
        food.saveToFile(ofs);
        activities.saveToFile(ofs);
    }

    void loadFromFile(ifstream &ifs)
    {
        Person::loadFromFile(ifs);
        getline(ifs, password);
        ifs >> bookingCancelled;
        ifs.ignore();
        journey.loadFromFile(ifs);
        food.loadFromFile(ifs);
        activities.loadFromFile(ifs);
    }
friend class Manager;
};

class Manager
 {
    User *users;
    int userCount;

public:
    Manager(User *u, int count)
     {
      users=u;
       userCount=count;

     }

    void displayShipInfo()
    {
    cout << GREEN << "Ship Information:\n" << RESET;
    cout << BLUE << "Name: Conqueror Atlantis\n" << RESET;
    cout << CYAN << "Capacity: 15000 people\n" << RESET;
    cout << MAGENTA << "Levels: 10 (5 for rooms, 5 for entertainment)\n" << RESET;
    cout << RED << "Languages: Multiple languages spoken by staff\n" << RESET;
    cout << YELLOW << "Journey Start: 6th month every year\n" << RESET;
    cout << GREEN << "Registrations: Start in 1st month every year\n" << RESET;
}


    void viewRegisteredUsers() {
        cout << "Registered Users:\n";
        for (int i = 0; i < userCount; ++i) {
            users[i].displayDetails();
            cout << "-------------------------\n";
        }
    }

    void approveCancellations()
    {
        cout << "Cancellation requests:\n";
        for (int i = 0; i < userCount; ++i) {
            if (users[i].isBookingCancelled()) {
                cout << i + 1 << ". User: " << users[i].getName() << endl;
            }
        }

        int choice;
        do {
            cout << "Enter the number of the user to approve cancellation (0 to cancel): ";
            cin >> choice;

            if (choice > 0 && choice <= userCount && users[choice - 1].isBookingCancelled())
                {
                cout << "Cancellation request approved for user: " << users[choice - 1].getName() << endl;
                // Remove user by shifting the array
                for (int j = choice - 1; j < userCount - 1; ++j)
                    {
                    users[j] = users[j + 1];
                }
                --userCount;
                break;
            } else if (choice == 0) {
                cout << "Cancellation approval canceled.\n";
                break;
            } else {
                cout << "Invalid choice or no cancellation request. Try again.\n";
            }
        } while (true);
    }

   void login()
   {
    string id, password;
    cout << CYAN << "Enter Manager ID: " << RESET;
    cin >> id;
    cout << CYAN << "Enter Password: " << RESET;
    password=getMaskedInput();

    if (id == MANAGER_ID && password == MANAGER_PASSWORD) {
        cout << GREEN << "Manager login successful!\n" << RESET;
        int choice;
        do {
            cout << "\nManager Menu:\n";
            cout << MAGENTA << "1. Display Ship Information\n";
            cout << CYAN << "2. View Registered Users\n";
            cout << RED << "3. Approve/Disapprove Cancellation Requests\n";
            cout << BLUE << "4. Logout\n";
            cout << GREEN << "Enter your choice: " << RESET;
            cin >> choice;

            switch (choice)
             {
                case 1:
                    displayShipInfo();
                    break;
                case 2:
                    viewRegisteredUsers();
                    break;
                case 3:
                    approveCancellations();
                    break;
                case 4:
                    cout << CYAN << "Logging out...\n" << RESET;
                    break;
                default:
                    cout << RED << "Invalid choice. Please try again.\n" << RESET;
            }
        } while (choice != 4);
    } else {
        cout << RED << "Invalid Manager ID or Password.\n" << RESET;
            Sleep(1500);
    }
}
};
bool loginUser(User *users, int userCount)
 {
    string name, password;
    cout << MAGENTA << "Enter Name: " << RESET;
    cin.ignore();
    getline(cin, name);
    cout << RED << "Enter Password: " << RESET;
    password=getMaskedInput();

    for (int i = 0; i < userCount; ++i)
        {
        if (users[i].getName() == name && users[i].getPassword() == password)
            {
            int choice;
            do {
                cout << "\nUser Menu:\n";
                cout << GREEN << "1. Display Details\n";
                cout << YELLOW << "2. Edit Details\n";
                cout << BLUE << "3. Request Cancellation\n";
                cout << RED << "4. Calculate and Display Expenses\n";
                cout << MAGENTA << "5. Logout\n";
                cout << CYAN << "Enter your choice: ";
                cin >> choice;
                switch (choice)
                 {
                    case 1:
                        users[i].displayDetails();
                        break;
                    case 2:
                        cout << GREEN << "Editing user details:\n" << RESET;
                        users[i].enterDetails();
                        break;
                    case 3:
                        users[i].cancelBooking();
                        cout << RED << "Cancellation request sent.\n" << RESET;
                        break;
                    case 4:
                        cout << CYAN << "Total Expenses: $" << users[i].calculateTotalExpenses() << endl << RESET;
                        break;
                    case 5:
                        cout << MAGENTA << "Logging out...\n" << RESET;
                        break;
                    default:
                        cout << YELLOW << "Invalid choice. Please try again.\n" << RESET;
                            Sleep(1500);
                }
            }
    while (choice != 5);
            return true;
        }
    }
    cout << RED << "Invalid login credentials!\n" << RESET;
    Sleep(1500);
    return false;
}

void registerUser(User *users, int &userCount, int maxUsers)
{
    if (userCount >= maxUsers)
        {
        cout << RED << "Maximum user limit reached. Cannot register more users.\n" << RESET;
        return;
    }
    string name, sex, address, phone, password;
    int age;
    cout << CYAN << "Enter Name: " << RESET;
    cin.ignore();
    getline(cin, name);
    cout << BLUE << "Enter Age: " << RESET;
    cin >> age;
    cout << RED << "Enter Sex: " << RESET;
    cin.ignore();
    getline(cin, sex);
    cout << MAGENTA << "Enter Address: " << RESET;
    getline(cin, address);
    cout << YELLOW << "Enter Phone Number: " << RESET;
    getline(cin, phone);
    cout << CYAN << "Enter Password: " << RESET;
    getline(cin, password);

    users[userCount] = User(name, age, sex, address, phone, password);
    ++userCount;

    cout << YELLOW << "User registered successfully.\n" << RESET;
}

void saveUsers(User *users, int userCount, const string &filename)
 {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Failed to open file for writing.\n";
        return;
    }

    for (int i = 0; i < userCount; ++i)
        {
        users[i].saveToFile(ofs);
    }
}

void loadUsers(User *users, int &userCount, const string &filename, int maxUsers)
{
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Failed to open file for reading.\n";
        return;
    }

    userCount = 0;
    while (userCount < maxUsers && ifs)
        {
        users[userCount].loadFromFile(ifs);
        if (ifs) {
            ++userCount;
        }
    }
}

void drawShip() {
cout << "  _______\n"
              << "       ____/       \\____\n"
              << "     /                    \\\n"
              << "    |  _________________  |\n"
              << "    |  |   |   |   |   |  |\n"
              << "    |  |___|___|___|___|  |\n"
              << "    |   \\            /    |\n"
              << "    |    \\__________/     |\n"
              << "    |                     |\n"
              << "     \\___________________/\n"
              << "      |                 |\n"
              << "      |                 |\n"
              << "      |_________________|\n"
              << "     /                   \\\n"
              << "    /_____________________\\\n"
              << "   /   o               o   \\\n"
              << "  /    o               o    \\\n"
              << " /___________________________\\\n";
}


void animateWaterWaves(int startRow, int endRow) {

    int currentRow = startRow;
    int waveLength = 40;
    bool direction = true;
     cout<<endl;
    for(int k=0;k<5;k++) {
        gotoRowCol(currentRow, 0);
        for(int i=0;i<10;i++)
        {
        cout << "~ ~ ~ ~ ~";
        Sleep(250);
        }

        if (direction) {
            currentRow++;
        } else {
            currentRow--;
        }

        if (currentRow == endRow || currentRow == startRow) {
            direction = !direction;
        }

        Sleep(500);
    }
}


int main()
 {
         clearScreen();
    gotoRowCol(2, 10);
    drawShip();
    gotoRowCol(13, 12);
    cout << "Titanic";
    thread waveThread(animateWaterWaves, 20, 25);

    cin.get();

    waveThread.join();
    clearScreen();
    const int MAX_USERS = 100;
    User users[MAX_USERS];
    int userCount = 0;

    loadUsers(users, userCount, "users.dat", MAX_USERS);

    int choice;
    do {
        clearScreen();
        cout << "\n" << MAGENTA << "Voyage Management System:\n" << RESET;
        cout << CYAN << "1. Register New User\n";
        cout << MAGENTA << "2. User Login\n";
        cout << RED << "3. Manager Login\n";
        cout << GREEN << "4. Exit\n" << RESET;
        cout << BLUE << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser(users, userCount, MAX_USERS);
                break;
            case 2:
                if (loginUser(users, userCount)) {
                    saveUsers(users, userCount, "users.dat");
                }
                break;
            case 3:
                 {
                Manager manager(users, userCount);
                manager.login();
                saveUsers(users, userCount, "users.dat");
                break;
            }
            case 4:
                saveUsers(users, userCount, "users.dat");
                cout << "Exiting the program...\n";
                break;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
                Sleep(1500);
        }
    } while (choice != 4);

    return 0;
}
