# The Retro Cinema
### Classes:
  * Time - Represents the hour and minute at which a movie starts. 
  * TimeVector - Represents a vector of type Time and is correlated through composition with the Time class. 
  * Movie - Represents the title, type, genre, and duration of a movie.
  * MovieVector - Represents a vector of type Movie and is correlated through composition with the Movie class. 
  * Cinema - Represents the name, location, and number of seats of a cinema.
  * CinemaVector - Represents a vector of type Cinema and is correlated through composition with the Cinema class. 
  * Program - Represents the movie, the cinema where it is screened, the starting times, and the ticket price. It is correlated through composition with the Movie, Cinema, and TimeVector classes.
  * ProgramVector - Represents a vector of type Program and is correlated through composition with the Program class. 
  * Ticket - Represents the number of tickets and the price of a ticket.
  * User - Represents the first name, last name, email address, and phone number of the customer.

### Functionalities:
The program allows booking tickets at a cinema. The booking can be done in two ways:

1. By selecting the preferred movie from a list, and then the cinema where that movie is playing.
2. By selecting the preferred cinema from a list, and then the movie, if it is playing at that cinema.

Once the movie and the cinema have been chosen, the next steps are selecting the starting time and the number of tickets.

Then, identification details must be provided to complete the booking:
* first name;
* last name;
* email address;
* phone number.

At the end, the booking information and the total price are displayed. The user can confirm the booking, in which case the application ends, or cancel it.

## How it works:
