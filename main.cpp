#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <stdlib.h>
#include <algorithm>3
#include <exception>
#include <string>
#include <vector>
#include <memory>
#include <random>

using namespace std;

template <class T> class Vector; // forward declaration

class Time
{
private:
    int hour;
    int minute;

public:
    Time()
    {
        hour = 0;
        minute = 0;
    }
    Time(int hour, int minute) : hour(hour), minute(minute) {} // (initialization list)

    void operator = (const Time& x) // (overloading the = operator)
    {
        hour = x.hour;
        minute = x.minute;
    }

    bool operator == (const Time& x)
    {
        return x.hour == hour && x.minute == minute;
    }

    friend istream & operator >> (istream &in, Time &time);
    friend ostream & operator << (ostream &out, const Time &time);
};
istream & operator >> (istream &in, Time &time) // (overloading the >> operator)
{
    in >>time.hour >>time.minute;
    return in;
}
ostream & operator << (ostream &out, const Time &time) // (overloading the << operator)
{
    out <<time.hour <<":" <<time.minute;
    return out;
}

class TimeVector
{
private:
    vector<shared_ptr<Time>> data;

public:
    TimeVector() {}

    void add(const Time& time)
    {
        data.push_back(make_shared<Time>(time));

    }

    int get_size() const
    {
        return data.size();
    }

    bool find(const Time& time) const // ( function in <algorithm> )
    {
        return data.end() != find_if(data.begin(), data.end(), [&](shared_ptr<Time> const& item) // (iterator pattern)
        {
            return *item == time;
        });
    }

    friend ostream & operator << (ostream &out, const TimeVector &times);

};
ostream & operator << (ostream &out, const TimeVector &times)
{
    for (const auto& time : times.data)
    {
        out << *time << " ";
    }
    return out;
}

class Movie
{
private:
    char title[30];
    char type[3];
    char genre[10];
    int duration;

public:
    Movie()
    {
    }

    Movie(char* movie_title, char* movie_type, char* movie_genre, int movie_duration)
    {
        strcpy(title, movie_title);
        strcpy(type, movie_type);
        strcpy(genre, movie_genre);
        duration = movie_duration;
    }

    ~Movie()
    {
    }

    const char* getTitle() const
    {
        return title;
    }
    char* getType()
    {
        return type;
    }
    char* getGenre()
    {
        return genre;
    }
    int getDuration()
    {
        return duration;
    }

    friend ostream & operator << (ostream &out, const Movie &movie);

    static Vector<Movie> get_all(); // (static method)

};
ostream & operator << (ostream &out, const Movie &movie)
{
    out <<movie.title <<" -> " <<movie.type <<", " <<movie.genre <<", " <<movie.duration <<" min";
    return out;
}

template <class T>
class Vector
{
private:
    int size;
    T *data;

public:
    Vector()
    {
        size = 0;
        data = NULL;
    }

    ~Vector()
    {
        if (data != NULL)
        {
            delete[] data;
            data = NULL;
        }
    }

    Vector(const Vector& new_data)
    {
        size = new_data.size;
        if (size == 0)
        {
            data = NULL;
            return;
        }
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = new_data.data[i];
    }

    const T& operator[](int index)
    {
        return data[index];
    }

    void add(const T& item)
    {
        size++;
        T* new_data = new T[size];
        for (int i = 0; i < size - 1; i++)
            new_data[i] = data[i];
        new_data[size - 1] = item;
        delete[] data;
        data = new_data;
    }

    int get_size()
    {
        return size;
    }

    void operator=(const Vector& x)
    {
        delete[] data;
        size = x.size;
        if (size == 0)
        {
            data = nullptr;
            return;
        }
        data = new T[size];
                delete[] data;
        size = x.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new T[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for (int i = 0; i < size; i++)
            data[i] = x.data[i];
    }
};

Vector<Movie> Movie::get_all()
{
    Vector<Movie>  movies;

    movies.add(Movie("Dirty Dancing", "2D", "Romance", 100));
    movies.add(Movie("Back To The Future", "2D", "Sci-Fi", 116));
    movies.add(Movie("E.T. The Extra-Terrestrial", "3D", "Sci-Fi", 115));
    movies.add(Movie("GhostBusters", "3D", "Comedy", 107));
    movies.add(Movie("Airplane!", "2D", "Comedy", 88));
    movies.add(Movie("The Breakfast Club", "2D", "Drama", 92));
    movies.add(Movie("Dead Poets Society", "2D", "Drama", 128));
    movies.add(Movie("The Terminator", "3D", "Action", 108));
    movies.add(Movie("The Shining", "3D", "Horror", 142));

    return movies;
}

class Cinema
{
private:
    char name[40];
    char location[50];
    int seats;

public:
    Cinema()
    {

    }

    Cinema(char* cinema_name, char* cinema_location, int cinema_seats)
    {
        strcpy(name, cinema_name);
        strcpy(location, cinema_location);
        seats = cinema_seats;
    }

    const char* getName() const
    {
        return name;
    }
    char* getLocation()
    {
        return location;
    }
    int getSeats()
    {
        return seats;
    }

    friend ostream& operator << (ostream& out, const Cinema& c);

    static Vector<Cinema> get_all();
};
ostream & operator << (ostream &out, const Cinema &cinema)
{
    out <<cinema.name <<" -> " <<cinema.location <<", " <<cinema.seats <<" seats";
    return out;
}

Vector<Cinema> Cinema::get_all()
{
    Vector<Cinema> cinemas;

    cinemas.add(Cinema("Retro Cinema Lipscani", "street Lipscani no. 53", 50));
    cinemas.add(Cinema("Retro Cinema Victoriei", "street Calea Victoriei no. 224", 60));
    cinemas.add(Cinema("Retro Cinema Herastrau", "street Nordului no. 3", 80));

    return cinemas;
}

class Program
{
private:
	Movie movie;
	Cinema cinema;
	TimeVector start_times;
	float price;

public:
	Program()
	{

	}

	Program(const Movie &program_movie, const Cinema &program_cinema, const TimeVector &program_start_times, float program_price)
	{
	    movie = program_movie;
	    cinema = program_cinema;
	    start_times = program_start_times;
	    price = program_price;
	}

	const Movie &getMovie() const
	{
	    return movie;
	}
    const Cinema &getCinema() const
	{
	    return cinema;
	}
    float getPrice()
    {
        return price;
    }

    bool find_time(const Time& time) const
    {
        return start_times.find(time);
    }

    friend ostream & operator << (ostream &out, const Program &program);

    static Vector<Program> get_for(const Movie& movie);
    static Vector<Program> get_for(const Cinema& cinema);

};
ostream & operator << (ostream &out, const Program &program)
{
    out <<program.movie <<"; " <<program.cinema <<endl;
    out <<"\t hour(s) available ->" <<program.start_times <<endl;
    return out;
}

Vector<Program> Program::get_for(const Movie& movie)
{
    Vector<Program> programs;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> hour_dist(10, 18);
    uniform_int_distribution<> min_dist(1, 3);

    Vector<Cinema> cinemas = Cinema::get_all();
    int cinemas_count = cinemas.get_size();
    for (int i = 0; i < cinemas_count; i++)
    {
        TimeVector times;
        for (int j = 0;j < 3; j++)
        {
            times.add(Time(hour_dist(gen), 15*min_dist(gen)));
        }
        programs.add(Program(movie, cinemas[i], times, 20));
    }
    return programs;
}

Vector<Program> Program::get_for(const Cinema& cinema)
{
    Vector<Program> programs;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> hour_dist(10, 18);
    uniform_int_distribution<> min_dist(1, 3);

    Vector<Movie> movies = Movie::get_all();
    int movies_count = movies.get_size();
    for (int i = 0; i < movies_count; i++)
    {
        TimeVector times;
        for (int j = 0;j < 2; j++)
        {
            times.add(Time(hour_dist(gen), 15*min_dist(gen)));
        }
        programs.add(Program(movies[i], cinema, times, 20));
    }

    return programs;
}

class Ticket
{
private:
    int quantity;
    Program program;

protected:
    float price;
    string type;

    const float getPrice() const
    {
        return price;
    }

    const int getQuantity() const
    {
        return quantity;
    }

public:
    Ticket()
    {

    }

    Ticket(int ticket_quantity, float ticket_price, Program ticket_program) :
        quantity(ticket_quantity), price(ticket_price), program(ticket_program)
    {
        type = "regular";
    }

    const string getType() const
    {
        return type;
    }

    virtual float calculate_total_price()
    {
        return price * quantity;
    }

    friend ostream & operator << (ostream &out, const Ticket &ticket);
};
ostream & operator << (ostream &out, const Ticket &ticket)
{
    if (ticket.quantity > 0)
        out <<ticket.quantity <<": " <<ticket.type <<endl;
    return out;
}

class IDiscount // (interface with two methods)
{
public:
    virtual double getDiscountValue() = 0;

    virtual string getDiscountType() = 0;
};

class DiscountTicket : public Ticket, public IDiscount // (multiple inheritance)
{
private:
    double discount;

public:
    DiscountTicket(int ticket_quantity, float ticket_price, Program ticket_program, double ticket_discount) :
        Ticket(ticket_quantity, ticket_price, ticket_program)
    {
        discount = ticket_discount;
    }

    double getDiscountValue()
    {
        return discount;
    }

    string getDiscountType()
    {
        return type;
    }

    float get_discounted_price()
    {
        return getPrice() * discount / 100;
    }

    float calculate_total_price() override
    {
        return get_discounted_price() * getQuantity();
    }
};

class ChildTicket : public DiscountTicket
{
public:
    ChildTicket(int ticket_quantity, float ticket_price, Program ticket_program) :
        DiscountTicket(ticket_quantity, ticket_price, ticket_program, 50)
    {
        type = "child";
    }
};

class StudentTicket : public DiscountTicket
{
public:
    StudentTicket(int ticket_quantity, float ticket_price, Program ticket_program) :
        DiscountTicket(ticket_quantity, ticket_price, ticket_program, 40)
    {
        type = "student";
    }
};

class SeniorTicket : public DiscountTicket
{
public:
    SeniorTicket(int ticket_quantity, float ticket_price, Program ticket_program) :
        DiscountTicket(ticket_quantity, ticket_price, ticket_program, 30)
    {
        type = "senior";
    }
};

class ValidationException : public std::exception
{
private:
    const char* message;

public:
    ValidationException(const char* msg) : message(msg) {}

    const char* getMessage() const
    {
        return message;
    }
};

class User
{
private:
	char first_name[20];
	char last_name[20];
	char email[30];
	char phone[11];

	void validate_phone(char* phone)
	{
        if (strlen(phone) != 10)
            throw ValidationException("Phone number must have 10 digits.");
        for (int ch=0; ch<strlen(phone); ch++)
            if (phone[ch] <'0' || phone[ch] >'9')
                throw ValidationException("Phone number must contain only digits.");
	}

	void validate_email(char* email)
	{
	    int ok = 0, len = strlen(email);
        for (int ch = 0; ch<len; ch++)
            if (email[ch] == '@')
                ok = 1;
        if (ok == 0)
            throw ValidationException("Email must contain '@'.");
        if (email[0] == '@' || email[len-1] == '@')
            throw ValidationException("Email must not begin or end with '@'.");
	}

public:
    User()
    {

    }

	User(char user_first_name[20], char user_last_name[20], char user_email[30], char user_phone[11])
	{
	    strcpy(first_name, user_first_name);
	    strcpy(last_name, user_last_name);
	    strcpy(email, user_email);
	    strcpy(phone, user_phone);
	}

    void setFirst_Name(char new_first_name[20])
    {
        strcpy(first_name, new_first_name);
    }
    void setLast_Name(char new_last_name[20])
    {
        strcpy(last_name, new_last_name);
    }
    void setEmail(char new_email[30])
    {
        validate_email(new_email);
        strcpy(email, new_email);
    }
    void setPhone(char new_phone[11])
    {
        validate_phone(new_phone);
        strcpy(phone, new_phone);
    }

    char* getFirst_Name()
    {
        return first_name;
    }
    char* getLast_Name()
    {
        return last_name;
    }
    char* getEmail()
    {
        return email;
    }
    char* getPhone()
    {
        return phone;
    }
    friend ostream & operator << (ostream &out, const User &user);

};
ostream & operator << (ostream &out, const User &user)
{
    out <<user.first_name <<" " <<user.last_name <<endl <<user.email <<endl <<user.phone <<endl;
    return out;
}

template <typename T>
T sum(const vector<T>& vec)
{
    T total = 0;
    for (int i = 0; i < vec.size(); i++)
        total += vec[i];
    return total;
}

class Order
{
private:
    User user;
    vector<Ticket*> tickets;

public:
    Order(User user_order) : user(user_order) {}

    virtual ~Order() // (virtual destructor)
    {
        tickets.clear();
    }

    const double total_amount() const
    {
        int size = tickets.size();
        vector<double> prices;
        for (int i=0; i<size; i++)
            prices.push_back(tickets[i]->calculate_total_price()); // (polymorphism)
        return sum(prices);
    }

    void add_ticket(Ticket* ticket)
    {
        tickets.push_back(ticket);
    }

    const User &getUser() const
    {
        return user;
    }

    friend ostream &operator << (ostream &out, const Order &order);
};
ostream &operator << (ostream &out, const Order &order)
{
    out <<order.user;

    int tickets_count = order.tickets.size();
    for (int i=0; i<tickets_count; i++)
        out <<*(order.tickets[i]);

    out <<"Total price: $" <<order.total_amount() <<endl;
    return out;
}

class PaymentException : public ValidationException
{
public:
    PaymentException(const char* msg) : ValidationException(msg) {}
};

class Payment // (abstract class)
{
private:
    double amount;
    string currency;
    static int try_count; // (static data member)

protected:
    Payment(double amount_payment, string currency_payment)
    {
        amount_payment = amount;
        currency_payment = currency;
    }

    void addTryCount()
    {
        try_count++;
    }

public:
    virtual bool process_payment() = 0; // (abstract method)

    double getAmount()
    {
        return amount;
    }
    string getCurrency()
    {
        return currency;
    }

    static int getTryCount() // (static method using static data member)
    {
        return try_count;
    }
};

int Payment::try_count = 0;

class CreditCardPayment : public Payment
{
private:
    string number;
    int expiration_month;
    int expiration_year;
    int cvv;

public:
    CreditCardPayment(string number_card, int expiration_month_card, int expiration_year_card, int cvv_card, double amount_payment, string currency_payment) :
        Payment(amount_payment, currency_payment), number(number_card), expiration_month(expiration_month_card), expiration_year(expiration_year_card), cvv(cvv_card) {}

    bool process_payment() override
    {
        addTryCount();

        int ok = 1;
        if (number.length() != 16)
            throw PaymentException("Card number must contain 16 digits.");
        for (int ch=0; ch<number.length(); ch++)
            if (number[ch]<'0' || number[ch]>'9')
                throw PaymentException("Card number must contain only digits.");
        if (expiration_month < 1 || expiration_month >12)
            throw PaymentException("Month value must be between 1 and 12.");
        if (expiration_year < 23)
            throw PaymentException("Card expired.");
        else if (expiration_year == 23)
            if (expiration_month < 4)
                throw PaymentException("Card expired.");
        if (cvv <100 || cvv>999)
            throw PaymentException("CVV must contain 3 digits.");

        cout <<endl <<"Processing payment..." <<endl;
        return true;
    }
};

class PayPalPayment : public Payment
{
private:
    string account;

public:
    PayPalPayment(string account_payment, double amount_payment, string currency_payment) :
        Payment(amount_payment, currency_payment), account(account_payment) {}

    bool process_payment()
    {
        addTryCount();

        int ok = 0;
        for (int ch = 0; ch<account.length(); ch++)
            if (account[ch] == '@')
                ok = 1;
        if (ok == 0)
            throw PaymentException("Account must contain '@'.");
        if (account[0] == '@' || account[account.length()-1] == '@')
            throw PaymentException("Account must not begin or end with '@'.");

        cout <<endl <<"Processing payment..." <<endl;
        return true;
    }
};

void show_menu_header()
{
    system("cls"); // clear screen
    cout <<"THE RETRO CINEMA" <<endl;
    cout <<endl;
}

void show_payment(double amount, string currency)
{
    char opt = ' ';
    Payment* payment;

    while (opt != NULL)
    {
        show_menu_header();

        cout <<"Select a payment method (C) - card or (P) - paypal: " <<endl;
        cin >>opt;

        if (opt == 'C' || opt == 'c')
        {
            cout <<"Enter your card information: " <<endl;

            string number;
            int exp_month, exp_year, cvv;

            try
            {
                cout <<"Card number: ";
                cin >>number;
                cout <<"Expiration month: ";
                cin >>exp_month;
                cout  <<"Expiration year: ";
                cin >>exp_year;
                cout <<"CVV: ";
                cin >>cvv;
            }
            catch (ios_base::failure &ex)
            {
                cout <<"Invalid input. Press any key to retry." <<endl;
                cin.clear();
                getch();
                continue;
            }

            payment = new CreditCardPayment(number, exp_month, exp_year, cvv, amount, currency); // (upcasting)
        }
        else if (opt == 'P' || opt == 'p')
        {
            cout <<"Enter your account information: " <<endl;

            string sir;
            cout <<"PayPal Account: ";
            cin >>sir;

            PayPalPayment* paypal = new PayPalPayment(sir, amount, currency);
            payment = dynamic_cast<Payment*>(paypal); // (downcasting)
        }
        else continue;

        try
        {
            if (payment->process_payment())
            {
                cout <<"Payment was processed successfully!" <<endl;
                cout <<"Number of tries: " <<Payment::getTryCount() <<endl;
                delete payment;

                cout <<endl <<"Press any key to exit program.";
                getch();
                exit(0);
            }
        }
        catch (PaymentException &ex)
        {
            cout <<"There was an error while processing your payment: " <<ex.getMessage() <<endl;
            cout <<"Number of tries: " <<Payment::getTryCount() <<endl;
        }

        cout <<"Press any key to retry.";
        getch();
    }
}

void show_order(const Order& order)
{
    show_menu_header();

    cout <<"Your reservation:" <<endl;
    cout <<order <<endl;

    cout <<"Confirm order? Press Y to proceed to payment or press any key to cancel: ";
    char opt;
    cin >>opt;
    cout <<endl;
    if (opt == 'y' || opt == 'Y')
        show_payment(order.total_amount(), "lei");
    // else returns movie / cinema selection
}

void book_ticket(Program program, const Time &time)
{
    show_menu_header();

    cout <<program.getMovie() <<"; " <<program.getCinema() <<";" <<endl;
    cout <<"\t hour selected -> " <<time <<endl;
    cout <<"\t seat price: $" <<program.getPrice() <<endl;

    cout <<endl <<"Introduce your information: " <<endl;
    User user;
    char sir[30];
    cout <<"First name: ";
    cin >>sir;
    user.setFirst_Name(sir);

    cout <<"Last name: ";
    cin >>sir;
    user.setLast_Name(sir);

    bool ok = false;
    while (!ok)
    {
        cout  <<"Email: ";
        cin >>sir;
        try
        {
            user.setEmail(sir);
            ok = true;
        }
        catch (ValidationException &ex)
        {
            cout <<ex.getMessage() <<endl;
        }
    }

    ok = false;
    while (!ok)
    {
        cout <<"Phone number: ";
        cin >>sir;
        try
        {
            user.setPhone(sir);
            ok = true;
        }
        catch (ValidationException &ex)
        {
            cout <<ex.getMessage() <<endl;
        }
    }


    Order myorder(user);

    int quantity, i = 1;
    string type;
    cout <<endl <<"Please enter the number of seats: " <<endl;

    cout <<" - regular - full price: ";
    cin >>quantity;
    Ticket ticket(quantity, program.getPrice(), program);
    myorder.add_ticket(&ticket);

    cout <<" - child - 50% discount: ";
    cin >>quantity;
    ChildTicket child_ticket(quantity, program.getPrice(), program);
    myorder.add_ticket(&child_ticket); // (upcasting)

    cout <<" - student - 40% discount: ";
    cin >>quantity;
    StudentTicket student_ticket(quantity, program.getPrice(), program);
    myorder.add_ticket(&student_ticket); // (upcasting)

    cout <<" - senior - 30% discount: ";
    cin >>quantity;
    SeniorTicket senior_ticket(quantity, program.getPrice(), program);
    myorder.add_ticket(&senior_ticket); // (upcasting)

    show_order(myorder);
}

void show_program_menu(const Movie& movie)
{
    int opt = -1;
    while (opt != 0)
    {
        show_menu_header();

        cout <<"Program for the movie: " <<movie.getTitle() <<endl;

        Vector<Program> program;
        program = Program::get_for(movie);
        int i;
        for (i=0;i<program.get_size();i++)
            cout <<i+1 <<": " <<program[i] <<endl;
        cout <<endl;

        cout <<"Please select the cinema to book your ticket or 0 (zero) to return: ";
        cin >>opt;
        cout <<endl;

        if (opt >= 1 && opt <= i)
        {
            Time time;
            cout <<"Please select the time: ";
            cin >>time;

            if (program[opt-1].find_time(time))
                book_ticket(program[opt-1], time);
            else
                cout <<"The hour selected doesn't exist in the program!" << endl;
        }
    }
}

void show_program_menu(const Cinema& cinema)
{
    int opt = -1;
    while (opt != 0)
    {
        show_menu_header();

        cout <<"Program for the cinema: " <<cinema.getName() <<endl;

        Vector<Program> program;
        program = Program::get_for(cinema);
        int i;
        for (i=0;i<program.get_size();i++)
            cout <<i+1 <<": " <<program[i] <<endl;
        cout <<endl;

        cout <<"Please select the movie to book your ticket or 0 (zero) to return: ";
        cin >>opt;
        cout <<endl;

        if (opt >= 1 && opt <= i)
        {
            Time time;
            cout <<"Please select the time: ";
            cin >>time;

            if (program[opt-1].find_time(time))
                book_ticket(program[opt-1], time);
            else
                cout <<"The hour selected doesn't exist in the program!" << endl;
        }
    }
}

void show_movies_menu()
{
    Vector<Movie> movies = Movie::get_all();

    int opt = -1;
    while (opt != 0)
    {
        show_menu_header();

        int movies_count = movies.get_size();
        for (int i = 0; i < movies_count; i++)
        {
            cout << i+1 <<". " <<movies[i] <<endl;
        }

        cout <<endl <<"Please select a movie number or 0 (zero) to return: ";
        cin >>opt;
        cout <<endl;

        if (opt >= 1 && opt <= movies_count)
            show_program_menu(movies[opt-1]);
    }
}
void show_cinemas_menu()
{
    Vector<Cinema> cinemas = Cinema::get_all();

    int opt = -1;
    while (opt != 0)
    {
        show_menu_header();

        int cinemas_count = cinemas.get_size();
        for (int i = 0; i < cinemas_count; i++)
        {
            cout << i+1 <<". " <<cinemas[i] <<endl;
        }

        cout <<endl <<"Please select a cinema number or 0 (zero) to return: ";
        cin >>opt;
        cout <<endl;

        if (opt >= 1 && opt <= cinemas_count)
            show_program_menu(cinemas[opt-1]);
    }
}

void show_main_menu()
{
    int opt = 0;
    while (opt != 3)
    {
        show_menu_header();

        cout <<"WELCOME!" <<endl;
        cout <<endl;
        cout <<"MAIN MANU:" <<endl;
        cout <<"1--> SHOW MOVIE LIST" <<endl;
        cout <<"2--> SHOW CINEMA LIST" <<endl;
        cout <<"3--> EXIT" <<endl;
        cout <<endl;

        cout <<"Please select an option: ";
        cin >>opt;

        if (opt == 1)
            show_movies_menu();
        if (opt == 2)
            show_cinemas_menu();
    }
}

int main()
{
    cin.exceptions(ios::failbit); // turn on cin exceptions

    show_main_menu();

    return 0;
}
