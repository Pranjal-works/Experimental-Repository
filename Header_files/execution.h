#include <string>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "classes.h"

using namespace std;

void Rooms ::show_availability()
{
  string availability;
  string room_no_str;
  int room_no;
  int i;
  ifstream fin("Rooms.txt");
  cout << setw(10) << "Room No." << setw(15) << "Availability" << endl;
  for (i = 0; i < 5; i++)
  {
    getline(fin, room_no_str);
    // room_no = stoi(room_no_str);
    // fin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(fin, availability);
    cout << setw(10) << room_no_str << setw(15) << availability << endl;
  }
  book_room();
}

void Customers :: get_cust_data()
{
  cout << "Enter customer details\nName: ";
  cin >> name;
  cout << "Mobile no: ";
  cin >> mob_no;
  cout << "AADHAR no: ";
  cin >> uid;
  cout << "Date of arrival(DD\\MM\\YYYY):";
  cin >> doa.dd >> doa.mm >> doa.yyyy;
  cout << "Stay nights: ";
  cin >> stay_nights;
  cout << "Payment type: ";
  cin >> payement_type;
  cout << "Number of people: ";
  cin >> nop;
  dod.dd = doa.dd + stay_nights;
  dod.mm = doa.mm;
  dod.yyyy = doa.yyyy;
  if (dod.mm == 2)
  {
    if (dod.dd > 28)
    {
      dod.mm = dod.mm + 1;
      carry = dod.dd - 28;
      dod.dd = carry;
    }
  }
  else if (dod.mm == 1 || dod.mm == 3 || dod.mm == 5 || dod.mm == 7 || dod.mm == 8 || dod.mm == 10 || dod.mm == 12)
  {
    if (dod.dd > 31)
    {
      dod.mm = dod.mm + 1;
      carry = dod.dd - 31;
      dod.dd = carry;
    }
  }
  else
  {
    if (dod.dd > 30)
    {
      dod.mm = dod.mm + 1;
      carry = dod.dd - 30;
      dod.dd = carry;
    }
  }

  if (dod.mm > 12)
  {
    dod.yyyy = dod.yyyy + 1;
    carry = dod.dd - 12;
    dod.dd = carry;
  }

  amount_to_pay = stay_nights * 2500;
  ofstream fout("Customers.txt",ios::app);
  fout << setw(20) << left << "Name:" << name << endl;
  fout << setw(20) << left << "Mobile no:" << mob_no << endl;
  fout << setw(20) << left << "AADHAR no:" << uid << endl;
  fout << setw(20) << left << "Stay nights:" << stay_nights << endl;
  fout << setw(20) << left << "Payment type:" << payement_type << endl;
  fout << setw(20) << left << "Number of people:" << nop << endl;
  fout << setw(20) << left << "Total amount: " << amount_to_pay << endl;
  fout << setw(20) << left << "Date of arrival : " << doa.dd << doa.mm << doa.yyyy<<endl;
  fout << setw(20) << left << "Date of departure : " << dod.dd << dod.mm << dod.yyyy<<endl;
  fout.close();
}

// void Customers ::print_recipt()
// {
//   ifstream fin("customers.txt");
//   if (!fin)
//   {
//     cerr << "Error opening file for reading." << endl;
//     return;
//   }
//   string label;
//   string value;
//   cout << "\nCustomer Details\n";
//   cout << setw(20) << left << "Field" << "Value" << endl;
//   cout << string(40, '-') << endl;

//   while (getline(fin, label))
//   {
//     if (getline(fin, value))
//     {
//       cout << setw(25) << left << label << setw(50) << value << endl;
//     }
//     cout << endl;
//   }
//   fin.close();
// }
void Customers ::print_recipt() {
    ifstream fin("Customers.txt");
    if (!fin) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    string label, value;
    cout << "\nCustomer Details\n";
    cout << setw(20) << left << "Field" << "Value" << endl;
    cout << string(40, '-') << endl;

    while (getline(fin, label)) {
        size_t pos = label.find(":"); // Find the colon separating the label and value
        if (pos != string::npos) {
            // Separate the label and value
            string field = label.substr(0, pos + 1);
            value = label.substr(pos + 1); // The value follows after the colon
            // Output the label and value, trimming extra spaces
            cout << setw(20) << left << field << setw(50) << value << endl;
        }
        cout << endl;
    }

    fin.close();
}


// void Rooms ::book_room()
// {
//   string availability;
//   int flag = 0;

//   ifstream fin("Rooms.txt");
//   ofstream fout("Rooms.txt",ios::app);
//   int lineNumber = 0;
//   while (getline(fin, availability))
//   {
//     lineNumber++;
//     if (lineNumber % 2 == 0)
//     {
//       if (availability == "true")
//       {
//         flag = 1;
//         lineNumber--;
//         fin >> room_no;
//         cout << "Your room no. is :  " << room_no << endl;
//         lineNumber++;
//         fout << "false";
//       }
//         break;
//     }
//   }
//     if (flag == 0)
//     {
//       cout << "All rooms are booked\n";
//     }
// }

bool Rooms::book_room() {
    string availability;
    int flag = 0;
    vector<string> fileData;  // To store file content temporarily
    int room_no = -1;

    // Open the file for reading
    ifstream fin("Rooms.txt");
    if (!fin) {
        cerr << "Error opening file for reading." << endl;
        return false;
    }

    string line;
    int lineNumber = 0;
    while (getline(fin, line)) {
        fileData.push_back(line);  // Store each line in the vector
        lineNumber++;

        // Check for availability every second line (even lines)
        if (lineNumber % 2 == 0 && line == "true" && flag == 0) {
            flag = 1;
            room_no = stoi(fileData[lineNumber - 2]);  // Get the room number from the previous line
            cout << "Your room no. is: " << room_no << endl;
            fileData[lineNumber - 1] = "false";  // Update availability to "false"
            return true;
        }
    }
    fin.close();

    if (flag == 0) {
        cout << "All rooms are booked\n";
        return false;
    } else {
        // Open the file for writing (overwrite the entire file)
        ofstream fout("Rooms.txt");
        if (!fout) {
            cerr << "Error opening file for writing." << endl;
            return false;
        }

        // Write updated data back to the file
        for (const auto &line : fileData) {
            fout << line << endl;
        }
        fout.close();
        return true;
    }
}

  void Manager ::add_staff()
  {
    ofstream outfile("staff_details.txt",ios::app);
    cout << "Enter staff name: ";
    cin >> sname;
    cout << "Enter staff ID: ";
    cin >> sid;
    cout << "Enter staff position: ";
    cin.ignore(); // Ignore leftover newline from previous input
    cin >> position;
    cout << "Enter staff salary: ";
    cin >> salary;
    cout << "Enter staff mobile number: ";
    cin >> smob_no;
    cout << "Enter number of days worked: ";
    cin >> days_worked;
    cin.ignore(); // Ignore leftover newline

    // Write staff data to the file
    outfile << sname << '\n'
            << sid << '\n'
            << position << '\n'
            << salary << '\n'
            << smob_no << '\n'
            << days_worked << '\n';
  }

  void Manager ::get_staff_data()
  {
    ifstream inFile("staff_details.txt"); // Open file for reading
    if (!inFile)
    {
      cerr << "Error opening file for reading." << endl;
      return;
    }

    // Print header
    cout << left << setw(20) << "Name"
         << setw(10) << "ID"
         << setw(20) << "Position"
         << setw(10) << "Salary"
         << setw(15) << "Mobile No"
         << setw(15) << "Days Worked" << endl;
    cout << string(90, '-') << endl;

    while (getline(inFile, sname))
    {
      inFile >> sid;
      inFile.ignore(); // Ignore leftover newline
      getline(inFile, position);
      inFile >> salary;
      inFile >> smob_no;
      inFile >> days_worked;
      inFile.ignore();

      cout << left << setw(20) << sname
           << setw(10) << sid
           << setw(20) << position
           << setw(10) << salary
           << setw(15) << smob_no
           << setw(15) << days_worked << endl;
    }

    inFile.close();
  }
