#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "taskList.h"
#include "visual.h"


// ----------------------
//     VISUAL METHODS
// ----------------------

// Formata a impressão da tarefa
void printTask(Task t) {
    printf("%s, %d, %d/%d\n", t.nome, t.prioridade, t.entrega.day, t.entrega.month);
}

// Imprime a tabela de tarefas IN-ORDER
void printTasksTable(Task *r) {
	printf("Nome, Prioridade, Data \n");
    printTasks(r, printTask);
}

// ----------------------
//     CRUD METHODS
// ----------------------

void insTask(Task **list) {
    Task *t = (Task*) malloc(sizeof(Task));

    printf("Inserir tarefa: \n");
    printf("Nome: ");
    scanf("%s", t->nome);
    printf("Prioridade: ");
    scanf("%d", &t->prioridade);
    printf("Entrega (formato XX/XX): ");
    scanf("%d/%d", &t->entrega.day, &t->entrega.month);

    *list = addTaskToList(*list, t);
}

void delTask(Task **list) {
    char name[10];

    printf("Deletar tarefa: \n");
    printf("Nome: ");
    scanf("\n%s", name);

    delTaskByName(*list, name);
}

void queryTask(Task **list) {
    if (notEmptyList(*list)) {
        char name[10];

        printf("Consultar tarefa: \n");
        printf("Nome: ");
        scanf("\n%s", name);

        Task *task = getTaskByName(*list, name);
        clearScreen();

        if (task != NULL) {
            printf("Nome, Prioridade, Data \n");
            printTask( *task);
            pressToContinue("\n\n");
        } else {
            pressToContinue("Não é possível consultar tarefa!\nNão existe tarefa com "
                "esse nome.\n\n");
        }
    }
}

void upTask(Task **list) {
    char name[50];

    printf("Atualizar tarefa: \n");
    printf("Nome: ");
    scanf("\n%s", name);

    Task *update = getTaskByName(*list, name);
    clearScreen();

    if (update != NULL) {
        printf("Nova Prioridade: ");
        scanf("%d", &update->prioridade);
        printf("Nova Entrega (formato XX/XX): ");
        scanf("%d/%d", &update->entrega.day, &update->entrega.month);

        pressToContinue("Tarefa atualizada com sucesso!\n\n");
    } else {
        pressToContinue(
            "Tarefa não atualizada!\nNão existe tarefa com esse nome.\n\n");
    }
}

void listTasks(Task **list) {
    printf("Listar tarefas: \n");
    if (notEmptyList(*list)) {
        printTasksTable(*list);
    }
    pressToContinue("\n\n");
}


// ----------------------
//     FILE METHODS
// ----------------------

// Tenta ler o arquivo, se ele não existe, cria
FILE *openFile() {
    FILE *f = fopen("arquivo.txt", "r");

    if (f == NULL) {
        FILE *f = fopen("arquivo.txt", "w");
        fclose(f);
    }

    return fopen("arquivo.txt", "r");;
}

// Carrega todas as tarefas do arquivo, a raiz e'passada como parâmetro
void loadListFromFile(FILE *f, Task **list) {
	while (!feof(f)){
        Task *n = (Task*) malloc(sizeof(Task));
        fscanf(f, "%s ,", n->nome);
		if(strcmp(n->nome, "")==0) break;
        fscanf(f, " %d ,", &n->prioridade);
        fscanf(f, " %d ,", &n->entrega.day);
        fscanf(f, " %d\n", &n->entrega.month);
        *list = addTaskToList(*list, n);
    }
    fclose(f);
}

// Formata o registro da tarefa no arquivo
void writeTaskOnFile(Task t, FILE *f){
	fprintf(f, "%s , %d , %d , %d\n", t.nome, t.prioridade, t.entrega.day, t.entrega.month);
}

// Percorre cada uma das tarefas e salva no arquivo
void saveFile(Task *r) {
    FILE *f = fopen("arquivo.txt", "w");
	printTasksOnFile(r, writeTaskOnFile, f);
    fclose(f);
}


// ----------------------
//     MAIN PROGRAM
// ----------------------

int main() {
    Task *taskList = NULL;

    FILE *f = openFile();
    loadListFromFile(f, &taskList);

    typedef void(*tela)(Task**);
    tela telas[] = {
        &insTask,
        &delTask,
        &upTask,
        &queryTask,
        &listTasks
    };

    int op = 0;
    while (1) {		
        op = menu();
		if (op == EXIT) break;
        telas[op-1](&taskList);
    }

    saveFile(taskList);
    return 0;
}