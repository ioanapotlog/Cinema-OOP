#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class MovieVector; // forward declaration
class CinemaVector; // forward declaration
class ProgramVector; // forward declaration

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
    int size;
    Time *data;

public:
    TimeVector()
    {
        size = 0;
        data = NULL;
    }

    ~TimeVector()
    {
        if (data != NULL)
        {
            delete [] data;
            data = NULL;
        }
    }

    TimeVector(const TimeVector &new_data) // (copy constructor)
    {
        size = new_data.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new Time[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for(int i=0;i<size;i++)
            data[i]=new_data.data[i];
    }

    const Time& operator[](int index)
    {
        return data[index];
    }

    void add(const Time& time)
    {
        size++;
        Time *new_data = new Time[size];
        for (int i = 0; i < size-1; i++)
            new_data[i] = data[i];
        new_data[size-1] = time;
        if (data != NULL)
            delete [] data;
        data = new_data;
    }

    int get_size()
    {
        return size;
    }

    void operator= (const TimeVector &x) // (overloading the = operator)
    {
        delete[] data;
        size = x.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new Time[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for(int i=0;i<x.size;i++)
            data[i] = x.data[i];
    }

    friend ostream & operator << (ostream &out, const TimeVector &times);

};
ostream & operator << (ostream &out, const TimeVector &times)
{
    for (int i=0;i<times.size;i++)
        out <<" " <<times.data[i];
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

    static MovieVector get_all();

};
ostream & operator << (ostream &out, const Movie &movie)
{
    out <<movie.title <<" -> " <<movie.type <<", " <<movie.genre <<", " <<movie.duration <<" min";
    return out;
}

class MovieVector
{
private:
    int size;
    Movie *data;

public:
    MovieVector()
    {
        size = 0;
        data = NULL;
    }

    ~MovieVector()
    {
        if (data != NULL)
        {
            data = NULL;
            delete [] data;
        }
    }

    MovieVector(const MovieVector &new_data) // (copy constructor)
    {
        size = new_data.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new Movie[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for(int i=0;i<size;i++)
            data[i]=new_data.data[i];
    }

    const Movie& operator[](int index)
    {
        return data[index];
    }

    void add(Movie movie)
    {
        size++;
        Movie *new_data = new Movie[size];
        for (int i = 0; i < size-1; i++)
            new_data[i] = data[i];
        new_data[size-1] = movie;
        if (data != NULL)
            delete [] data;
        data = new_data;
    }

    int get_size()
    {
        return size;
    }

    void operator= (const MovieVector &x) // (overloading the = operator)
    {
        delete[] data;
        size = x.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new Movie[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for(int i=0;i<x.size;i++)
            data[i] = x.data[i];
    }
};

MovieVector Movie::get_all()
{
    MovieVector movies;

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

    static CinemaVector get_all();
};
ostream & operator << (ostream &out, const Cinema &cinema)
{
    out <<cinema.name <<" -> " <<cinema.location <<", " <<cinema.seats <<" seats";
    return out;
}

class CinemaVector
{
private:
    int size;
    Cinema *data;

public:
    CinemaVector()
    {
        size = 0;
        data = NULL;
    }

    ~CinemaVector()
    {
        if (data != NULL)
        {
            data = NULL;
            delete [] data;
        }
    }

    CinemaVector(const CinemaVector &new_data) // (copy constructor)
    {
        size = new_data.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new Cinema[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for(int i=0;i<size;i++)
            data[i]=new_data.data[i];
    }

    const Cinema& operator[](int index)
    {
        return data[index];
    }
    void add(Cinema cinema)
    {
        size++;
        Cinema *new_data = new Cinema[size];
        for (int i = 0; i < size-1; i++)
            new_data[i] = data[i];
        new_data[size-1] = cinema;
        if (data != NULL)
            delete [] data;
        data = new_data;
    }
    int get_size()
    {
        return size;
    }

    void operator= (const CinemaVector &x) // (overloading the = operator)
    {
        delete[] data;
        size = x.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new Cinema[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for(int i=0;i<x.size;i++)
            data[i] = x.data[i];
    }
};

CinemaVector Cinema::get_all()
{
    CinemaVector cinemas;

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

    friend ostream & operator << (ostream &out, const Program &program);

    static ProgramVector get_for(const Movie& movie);
    static ProgramVector get_for(const Cinema& cinema);

};
ostream & operator << (ostream &out, const Program &program)
{
    out <<program.movie <<"; " <<program.cinema <<endl;
    out <<"\t hour(s) available ->" <<program.start_times <<endl;
    return out;
}

class ProgramVector
{
private:
    int size;
    Program *data;

public:
    ProgramVector()
    {
        size = 0;
        data = NULL;
    }

    ~ProgramVector()
    {
        if (data != NULL)
        {
            delete [] data;
            data = NULL;
        }
    }

    ProgramVector(const ProgramVector &new_data) // (copy constructor)
    {
        size = new_data.size;
        if (!size)
        {
            data = NULL;
            return;
        }
        data = new Program[size];
        if (!data)
        {
            size = 0;
            return;
        }
        for(int i=0;i<size;i++)
            data[i]=new_data.data[i];
    }

    const Program& operator[](int index)
    {
        return data[index];
    }

    void add(Program program)
    {
        size++;
        Program *new_data = new Program[size];
        for (int i = 0; i < size-1; i++)
            new_data[i] = data[i];
        new_data[size-1] = program;
        if (data != NULL)
            delete [] data;
        data = new_data;
    }

    int get_size()
    {
        return size;
    }

    void operator= (const ProgramVector &x) // (overloading the = operator)
    {
        delete[] data;

        size = x.size;

        if (!size)
        {
            data = NULL;
            return;
        }

        data = new Program[size];

        if (!data)
        {
            size = 0;
            return;
        }

        for(int i=0;i<x.size;i++)
            data[i] = x.data[i];
    }
};

ProgramVector Program::get_for(const Movie& movie)
{
    ProgramVector programs;

    CinemaVector cinemas = Cinema::get_all();
    int cinemas_count = cinemas.get_size();
    for (int i = 0; i < cinemas_count; i++)
    {
        TimeVector times;
        times.add(Time(10+i%3, 30));
        times.add(Time(15-i%2, 15+15*i%3));
        times.add(Time(18+i%2, 30));
        programs.add(Program(movie, cinemas[i], times, 20));
    }

    return programs;
}

ProgramVector Program::get_for(const Cinema& cinema)
{
    ProgramVector programs;

    MovieVector movies = Movie::get_all();
    int movies_count = movies.get_size();
    for (int i = 0; i < movies_count; i++)
    {
        TimeVector times;
        times.add(Time(10+i%3, 30));
        times.add(Time(15+i%4, 15+30*i%2));
        programs.add(Program(movies[i], cinema, times, 20));
    }

    return programs;
}

class Ticket
{
private:
    int quantity;
    float price;
    Program program;

public:
    Ticket()
    {

    }

    Ticket(int ticket_quantity, float ticket_price, Program ticket_program)
    {
        quantity = ticket_quantity;
        price = ticket_price;
        program = ticket_program;
    }

    int getQuantity()
    {
        return quantity;
    }

    void setQuantity(int new_quantity)
    {
        quantity = new_quantity;
    }

    float getPrince()
    {
        return price;
    }

    void setPrice(float new_price)
    {
        price = new_price;
    }

    float calculate_total_price()
    {
        return price * quantity;
    }
};

class User
{
private:
	char first_name[20];
	char last_name[20];
	char email[30];
	char phone[11];

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
        strcpy(email, new_email);
    }
    void setPhone(char new_phone[11])
    {
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

void show_menu_header()
{
    system("cls"); // clear screen
    cout <<"THE RETRO CINEMA" <<endl;
    cout <<endl;
}

void confirm_ticket()
{
    show_menu_header();

    cout <<"Thank you! Your reservation has been confirmed!" <<endl;
    cout <<endl;
}

void show_ticket(const User& user, int total_price)
{
    show_menu_header();

    cout <<"Your reservation:" <<endl;
    cout <<user;
    cout <<"Total price: $" <<total_price <<endl;
    cout <<endl;

    cout <<"Would you like to confirm? (Yes - Y / No - N) " ;
    char opt;
    cin >>opt;
    if (opt == 'Y')
        confirm_ticket();
    else if (opt == 'N')
        return;
// returnarea in main menu
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
    cout  <<"Email: ";
    cin >>sir;
    user.setEmail(sir);
    cout <<"Phone number: ";
    cin >>sir;
    user.setPhone(sir);

    int quantity;
    cout <<endl <<"Please introduce the number of seats: ";
    cin >>quantity;

    Ticket ticket;
    ticket.setQuantity(quantity);
    ticket.setPrice(program.getPrice());

    int total_price = ticket.calculate_total_price();

    show_ticket(user, total_price);
}

void show_program_menu(const Movie& movie)
{
    int opt = -1;
    while (opt != 0)
    {
        show_menu_header();

        cout <<"Program for the movie: " <<movie.getTitle() <<endl;

        ProgramVector program;
        program = Program::get_for(movie);
        int i;
        for (i=0;i<program.get_size();i++)
            cout <<i+1 <<": " <<program[i] <<endl;
        cout <<endl;

        cout <<"Please select the cinema to book your ticket: ";
        cin >>opt;
        cout <<endl;

        if (opt >= 1 && opt <= i)
        {
            Time time;
            cout <<"Please select the time: ";
            cin >>time;

            book_ticket(program[opt-1], time);
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

        ProgramVector program;
        program = Program::get_for(cinema);
        int i;
        for (i=0;i<program.get_size();i++)
            cout <<i+1 <<": " <<program[i] <<endl;
        cout <<endl;

        cout <<"Please select the movie to book your ticket: ";
        cin >>opt;
        cout <<endl;

        if (opt >= 1 && opt <= i)
        {
            Time time;
            cout <<"Please select the time: ";
            cin >>time;

            book_ticket(program[opt-1], time);
        }
    }
}

void show_movies_menu() // functie pentru afisarea listei filme
{
    int opt = -1;
    while (opt != 0)
    {
        show_menu_header();

        MovieVector movies = Movie::get_all();
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
void show_cinemas_menu() // functie pentru afisarea listei cinema
{
    int opt = -1;
    while (opt != 0)
    {
        show_menu_header();

        CinemaVector cinemas = Cinema::get_all();
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
        else if (opt == 0)
            return;
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
    show_main_menu();

    return 0;
}
