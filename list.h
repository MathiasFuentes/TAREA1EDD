#ifndef LIST_H
#define LIST_H

#include <time.h>
#include <stdbool.h>

typedef struct Node {
  size_t ID;                // Identificador numérico del ticket.
  char *desc;               // Descripción del ticket.
  unsigned short prioridad; // Prioridad del ticket.
  time_t horaRegistro;      // Hora de registro del ticket.
  struct Node *next;        // Puntero al siguiente nodo.
  struct Node *prev;        // Puntero al nodo anterior.
} Node;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
} list;

list *createList();
// Crear lista y devolver el puntero a la misma.

bool isEmpty(list *list);
// Revisa si la lista está vacía o no.

void *insertTicket(list *list, size_t idTicket, char *descTicket);
// Insertar un ticket con prioridad baja.

void asignarPrioridad(list *list, size_t idTicket, int prioridadAsignada);
// Asignar prioridad a un ticket ya creado, ordenar en la lista.

void mostrarTickets(list *list);
// Mostrar los tickets en orden de prioridad, desde la más alta hasta la más
// baja

void procesarTicket(list *list);
// Muestra los datos del primer ticket en la lista y los muestra.

void buscarTicket(list *list, size_t id);
// Busca un ticket y muestra los datos del mismo.

//  FUNCIONES APLICABLES AL MAIN.

void limpiarPantalla();

void presioneTeclaParaContinuar();

void insertarTicket(list *list);

void asignarPrioridadTicket(list *list);

#endif