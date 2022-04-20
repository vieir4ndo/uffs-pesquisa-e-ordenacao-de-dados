// ----------------------
//       STRUCTS
// ----------------------

typedef struct {
  int day;
  int month;
}
Date;

typedef struct REC {
  char nome[50];
  int prioridade;
  Date entrega;
  struct REC * left;
  struct REC * right;
} Task;


// Função que calcula, recursivamente, qual é o tamanho das árvores abaixo dela
int depthSubTree(Task *r) {
    if (!r) return 0;
    int depthLeft, depthRight;
    depthLeft = depthSubTree(r->left);
    depthRight = depthSubTree(r->right);
    return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
}

// Rotação simples a direita do balanceamento AVL
Task *ll(Task *r) {
    Task *newRoot = r->left;
    r->left = newRoot->right;
    newRoot->right = r;
    return newRoot;
}

// Rotação simples a esquerda do balanceamento AVL
Task *rr(Task *r) {
    Task *newRoot = r->right;
    r->right = newRoot->left;
    newRoot->left = r;
    return newRoot;
}

// Rotação esquerda-direita do balanceamento AVL
Task *lr(Task *r) {
    r->left = rr(r->left);
    return ll(r);
}

// Rotação direita-equerda do balanceamento AVL
Task *rl(Task *r) {
    r->right = ll(r->right);
    return rr(r);
}

// Faz o balanceamento da árvore de acordo com o método AVL
Task *AVLBalance(Task *r) {
    int rootBalance, childBalance;
    rootBalance = depthSubTree(r->left) - depthSubTree(r->right);

    if (rootBalance > 1) {
        // Se a subárvore estiver desbalanceada para a esquerda
        childBalance = depthSubTree(r->left->left) - depthSubTree(r->left->right);
        r = (childBalance > 0) ? ll(r) : lr(r);
    } else if (rootBalance < -1) {
        // Se a subárvore estiver desbalanceada para a direita
        childBalance = depthSubTree(r->right->left) - depthSubTree(r->right->right);
        r = (childBalance < 0) ? rr(r) : rl(r);
    }
    return r;
}

// Adiciona um nó recursivamente à árvore e aplica as regras de balanceamento
Task *addTaskToList(Task *r, Task *n) {
	n->right = NULL;
	n->left = NULL;
    if (!r) return n;
    if (strcmp(r->nome, n->nome) >= 0) {
        // Procura uma folha na subárvore da esquerda
        r->left = addTaskToList(r->left, n);
    } else {
        // Procura uma folha na subárvore da direta
        r->right = addTaskToList(r->right, n);
    }
    return AVLBalance(r);
}

// Retorna a tarefa cujo nome corresponde com o parâmetro de pesquisa
// Se o id não for encontrado retorna NULL
Task *getTaskByName(Task *r, char* nome) {
    if (!r || strcmp(r->nome, nome) == 0) return r;
    if (strcmp(r->nome, nome) > 0) {
        // Procura pelo valor pela esquerda
        return getTaskByName(r->left, nome);
    } else {
        // Procura pelo valor pela direita
        return getTaskByName(r->right, nome);
    }
}

// Encontra o menor valor da subárvore
Task *minTask(Task *r) {
    if (!r->left) return r;
    return minTask(r->left);
}

// Apaga o nó cujo nome é passado como parâmetro, recursivamente
Task *delTaskByName(Task *r, char* nome) {
    if (!r) return r;
    if (strcmp(nome, r->nome) < 0) {
        // Procura pela tarefa pela esquerda
        r->left = delTaskByName(r->left, nome);
    } else if (strcmp(nome, r->nome) > 0) {
        // Procura pela tarefa pela direita
        r->right = delTaskByName(r->right, nome);
    } else {
        // Encotrou o id do parâmetro
        Task *left = r->left;
        Task *right = r->right;
        if (!left && !right) {
            // Caso seja uma folha
            free(r);
            return NULL;
        } else if (!left) {
            // Caso só tenha o filho da direita, promove-o
            free(r);
            return right;
        } else if (!right) {
            // Caso só tenha o filho da esquerda, promove-o
            free(r);
            return left;
        }
        // Caso tenha os dois filhos, irá promover o menor valor da subárvore direita
        r = minTask(r->right);
        r->left = left;
        // Após copiá-lo para cima, é nescessário excluí-lo
        r->right = delTaskByName(right, r->nome);
    }
    return r;
}

// Libera o espaço alocado na memória para a estrutura da árvore
void freeTree(Task *r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

// Verifica se a lista está vazia e imprime alerta
int notEmptyList(Task *r) {
    if (!r) {
        // br(1);
        printf("Lista de Tarefas Vazia!");
    }
    return r ? 1 : 0; // 0 = vazia; 1 = tem tarefas;
}

// Executa a função passada como parametro para cada um dos elementos da árvore IN-ORDER
void printTasks(Task *r, void (*func)(Task) ) {    
    if (r->left) printTasks(r->left, func);
    func(*r);
    if (r->right) printTasks(r->right, func);
}

// Executa a função passada como parametro para cada um dos elementos da árvore IN-ORDER
void printTasksOnFile(Task *r, void (*func)(Task, FILE*), FILE *f) {    
    if (r->left) printTasksOnFile(r->left, func, f);
    func(*r, f);
    if (r->right) printTasksOnFile(r->right, func, f);
}