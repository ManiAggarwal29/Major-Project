// fileops.h - file related work (very simple)
#ifndef FILEOPS_H
#define FILEOPS_H
#include "ticket.h"
void addTicketToFile(const Ticket *t);  // saving ticket
int  removeTicketByID(int id);          // deleting ticket
void clearInput(void);                  // clear wrong input from stdin
#endif
