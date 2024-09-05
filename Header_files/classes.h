#ifndef classes
#define classes
using namespace std;

struct date
{
    int dd, mm, yyyy;
};

class Customers
{
protected:
    struct date doa;
    struct date dod;
    struct date cd;
    string name, payement_type;
    int stay_nights, nop, amount_to_pay, carry;
    string mob_no, uid;

public:
    void get_cust_data();
    void print_recipt();
};

class Rooms : public virtual Customers
{
protected:
    int room_no;

public:
    void show_availability();
    bool book_room();
};

class Receptionist : virtual public Rooms
{
protected:
    string password;

public:
    friend bool check_validate();
};

class Manager
{
protected:
    string sname, position;
    int sid, salary, days_worked;
    string smob_no;

public:
    void get_staff_data();
    void add_staff();
};
#endif
