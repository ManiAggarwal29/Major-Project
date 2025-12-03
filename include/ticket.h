// ticket.h - header file for ticket related details
#ifndef TICKET_H
#define TICKET_H
#define DATAFILE "tickets.txt"
// Structure for storing one ticket
typedef struct {
    int id;                 // ticket id
    int busNo;              // bus number
    char destination[50];   // where passenger is going
    char name[50];          // passenger name
    int seatNo;             // seat number
    int fare;               // ticket fare
} Ticket;
// Structure for bus details
typedef struct {
    int busNo;              // bus number
    char destination[50];   // city name
    int fare;               // fixed fare for that bus
} Bus;
// fixed buses we provide (defined in ticket.c)
extern Bus buses[4];
// all functions
int getNextTicketID(void);
int seatTaken(int busNo, int seatNo);
void bookTicket(void);
void viewAllTickets(void);
void viewBusTickets(void);
void viewByDestination(void);
void cancelTicket(void);
#endif
