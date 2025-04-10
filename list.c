#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void limpiarPantalla(){ system("cls"); }

bool existeTicket(list *L, size_t ID) {
  Node *curr = L->head;
  while (curr != NULL) {
    if (curr->ID == ID) return true;
    curr = curr->next;
  }
  return false;
}

void presioneTeclaParaContinuar() {
  puts("Presione Enter para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

list *createList() {
  list *newList = (list *)malloc(sizeof(list));
  newList->head = NULL;
  newList->tail = NULL;
  newList->size = 0;
  return newList;
}

bool isEmpty(list *L) {
  if (L->size == 0)
    return true;
  return false;
}

void *insertTicket(list *L, size_t idTicket, char *descTicket) {

  // CREACIÓN DE UN NUEVO NODO
  Node *newTicket = (Node *)malloc(sizeof(Node));
  if (newTicket == NULL) {
    puts("Fallo en la asignación de memoria");
    return NULL;
  }

  // GUARDAR DESCRIPCIÓN DEL TICKET
  newTicket->desc = (char *)malloc(strlen(descTicket) + 1);
  if (newTicket->desc == NULL) {
    puts("Fallo en la asignación de la descripción");
    return NULL;
  }

  // GUARDAR LOS DATOS INGRESADOS EN EL NODO
  newTicket->ID = idTicket;
  strcpy(newTicket->desc, descTicket);
  newTicket->horaRegistro = time(NULL);
  newTicket->next = newTicket->prev = NULL;
  newTicket->prioridad = 1;

  // SI LA LISTA ESTA VACIA SE PONE AL INICIO
  if (isEmpty(L)){
    L->head = newTicket;
    L->tail = newTicket;
    L->size = 1;
  }

  // SINO SE PONE AL FINAL DE LA LISTA
  else {

    Node *aux = L->head;
    for (size_t i = 0; aux->next != NULL; i++) {
      aux = aux->next;
    }
    aux->next = newTicket;
    newTicket->prev = aux;
    L->tail = newTicket;
    L->size += 1;
  }
}

void asignarPrioridad(list *L, size_t idTicket, int prioridadAsignada) {
  Node *aux = L->head;

  while (aux != NULL && aux->ID != idTicket) {
    aux = aux->next;
  }

  if (aux == NULL) {
    printf("No se encontró el ticket con ID: %zu\n", idTicket);
    return;
  }

  aux->prioridad = prioridadAsignada;

  // Remover el nodo de su posición actual
  if (aux->prev)
    aux->prev->next = aux->next;
  else
    L->head = aux->next;

  if (aux->next)
    aux->next->prev = aux->prev;
  else
    L->tail = aux->prev;

  aux->next = aux->prev = NULL;

  // Reinsertar en la posición correcta
  Node *curr = L->head;
  while (curr != NULL) {
    if (aux->prioridad > curr->prioridad ||
        (aux->prioridad == curr->prioridad &&
         aux->horaRegistro < curr->horaRegistro)) {
      // Insertar antes de 'curr'
      aux->next = curr;
      aux->prev = curr->prev;
      if (curr->prev)
        curr->prev->next = aux;
      else
        L->head = aux;
      curr->prev = aux;
      puts("Prioridad Asignada con Éxito!! :D");
      return;
    }
    curr = curr->next;
  }

  // Si no se insertó en el medio, va al final
  if (L->tail) {
    L->tail->next = aux;
    aux->prev = L->tail;
    L->tail = aux;
  } else {
    // Lista estaba vacía
    L->head = L->tail = aux;
  }
  puts("Prioridad Asignada con Éxito!! :D");
}

void mostrarTickets(list *L) {
  if (L->head == NULL) {
    printf("No se ha ingresado ningún ticket aún!\n");
  } else {
    const char *prioridades[] = {"BAJA", "MEDIA", "ALTA"};

    Node *curr = L->head;
    printf("\n--- Lista de Tickets ---\n");

    while (curr != NULL) {
      char timeStr[9]; // hh:mm:ss
      strftime(timeStr, sizeof(timeStr), "%H:%M:%S", localtime(&curr->horaRegistro));

      printf("ID: %zu | Prioridad: %s | Hora: %s | Desc: %s\n",
             curr->ID, prioridades[curr->prioridad - 1], timeStr, curr->desc);

      curr = curr->next;
    }

    printf("------------------------\n");
  }
}

void procesarTicket(list *L) {
  if (isEmpty(L)) {
    puts("No hay tickets para procesar.");
    return;
  }

  Node *primero = L->head;

  // Mostrar los datos
  const char *prioridades[] = {"BAJA", "MEDIA", "ALTA"};
  char timeStr[9];
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", localtime(&primero->horaRegistro));

  printf("\nProcesando Ticket...\n");
  printf("ID: %zu | Prioridad: %s | Hora: %s | Desc: %s\n",
         primero->ID, prioridades[primero->prioridad - 1], timeStr, primero->desc);

  // Actualizar punteros de la lista
  L->head = primero->next;
  if (L->head != NULL)
    L->head->prev = NULL;
  else
    L->tail = NULL;  // La lista queda vacía

  // Liberar memoria
  free(primero->desc);
  free(primero);
  L->size--;

  puts("Ticket procesado.");
}

void buscarTicket(list *L, size_t id) {
  Node *curr = L->head;
  while (curr != NULL) {
    if (curr->ID == id) {
      char timeStr[9]; // hh:mm:ss → 8 caracteres + '\0'
      strftime(timeStr, sizeof(timeStr), "%H:%M:%S", localtime(&curr->horaRegistro));

      printf("Encontrado:\nID: %zu | Prioridad: %hu | Hora: %s | Desc: %s\n",
             curr->ID, curr->prioridad, timeStr, curr->desc);
      return;
    }
    curr = curr->next;
  }
  printf("No se encontró ticket con ID %zu\n", id);
}


// FUNCIONES PARA EL MAIN.


void insertarTicket(list *L) {
  limpiarPantalla();
  printf("Para ingresar el ticket, debe proporcionar:\n");
  puts("1. ID Numérico del Ticket.");
  puts("2. Descripción del Ticket.");

  size_t ID;
  char desc[256];

  // Solicitar ID hasta que sea válido y no duplicado
  while (true) {
    printf("\nIngrese el ID del Ticket: ");
    if (scanf(" %zu", &ID) != 1) {
      printf("Entrada inválida. El ID debe ser un número.\n");
      while (getchar() != '\n'); // Limpiar buffer
      continue;
    }

    if (existeTicket(L, ID)) {
      printf("Error: Ya existe un ticket con ID %zu. Intente otro.\n", ID);
      while (getchar() != '\n'); // Limpiar buffer restante
      continue;
    }

    break; // Salir del bucle si el ID es válido y único
  }

  getchar();  // Limpiar salto de línea pendiente


  printf("Ingrese la descripción del Ticket: ");
  fgets(desc, sizeof(desc), stdin);
  desc[strcspn(desc, "\n")] = '\0';  // Eliminar salto de línea

  insertTicket(L, ID, desc);
  puts("Ticket ingresado con éxito.");
}

void asignarPrioridadTicket(list *L){
  limpiarPantalla();
  puts("Para asignar prioridad a un ticket, debe proporcionar :");
  puts("1. ID del Ticket");
  puts("2. Número de Prioridad a asignar al ticket :");
  puts("  1. Baja");
  puts("  2. Media");
  puts("  3. Alta");

  size_t ID;
  int prioridad;
  bool flag = false;

  printf("\nIngrese el ID del Ticket :");
  scanf(" %zu", &ID);

  do{
    printf("\nIngrese la Prioridad del Ticket :");
    scanf(" %d", &prioridad);
    
    if (prioridad >= 1 && prioridad < 4) flag = true;
    else puts("Prioridad no válida, porfavor ingrese una entre 1 y 3.");

  } while(flag != true);

  asignarPrioridad(L, ID, prioridad);
}
