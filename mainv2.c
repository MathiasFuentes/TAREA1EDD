#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void mostrarOpciones(){
  limpiarPantalla();
  printf("--------------------------------------------\n");
  printf("Bienvenido al Programa de Gestión de Tickets\n");
  printf("--------------------------------------------\n");
  puts("\n1. Ingresar un Ticket");
  puts("2. Asignar prioridad a un Ticket");
  puts("3. Mostrar todos los Tickets pendientes");
  puts("4. Procesar siguiente Ticket.");
  puts("5. Buscar un ticket por ID");
  puts("6. Salir del programa");

}

int main() {
  char opcion;
  list *tickets = createList(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarOpciones();
    printf("\nIngrese su opción: ");
    scanf(" %c", &opcion);
    while (getchar() != '\n');

    switch (opcion) {
    case '1':
      insertarTicket(tickets);
      break;
    case '2' :
      asignarPrioridadTicket(tickets);
      break;
    case '3' :
      mostrarTickets(tickets);
      break;
    case '4' :
      procesarTicket(tickets);
      break;
    case '5' :
      buscarTicket(tickets);
      break;
    case '6':
      puts("Saliendo del sistema de gestión de tickets...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();
  } while (opcion != '6');

  

  return 0;
}
