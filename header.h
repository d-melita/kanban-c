/* Projeto 1 IAED - Diogo Melita ist199202 */
/* gcc -Wall -Wextra -Werror -ansi -pedantic -o proj proj.c */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define RETURN_ZERO 0
#define MAX_TASKS 10000
#define MAXTASKDESCRIPTION 51
#define MAXATIVIDADE 21
#define MAXUSER 21
#define MAXUSERS 50
#define MAXACTIVITIES 10
#define TODO "TO DO"
#define INPROGRESS "IN PROGRESS"
#define DONE "DONE"
#define NST "no such task"
#define DD "duplicate description"
#define T "task"
#define ID "invalid duration"
#define TMT "too many tasks"
#define IT "invalid time"
#define UAE "user already exists"
#define TMU "too many users"
#define NSU "no such user"
#define NSA "no such activity"
#define TAS "task already started"
#define DURATION "duration="
#define SLACK "slack="
#define TMA "too many activities"
#define DA "duplicate activity"
#define INVALIDDESCRIPTION "invalid description"

void new_task();
void list_tasks();
void time();
void utilizador();
void movetask();
void tasksinactivity();
void addactivity();
int binarysearch(int id);
void ordenar(int n, int len);

struct tarefa
{
    int tempo; /* tempo esperado de duracao*/
    char descricao[MAXTASKDESCRIPTION];
    int id;
    char atividade[MAXATIVIDADE];
    int instinicio; /* instante de inicio */
};

struct utilizador
{
    int u; /* nº do utilizador */
    char user[MAXUSER];
};

struct atividade
{
    int numero; /*nº da atividade */
    char atividade[MAXATIVIDADE];
};
