#define EXIT 10

// Função que limpa a tela
void clearScreen() { system("clear"); }

// Imprime mensagem passada por parâmetro seguida da mensagem padrão
// Aguarda por pressionar qualquer tecla para sair da função
void pressToContinue(char message[]) {
  printf("%s", message);
  printf("Pressione enter para voltar ao menu principal.");
  // Nescessário repetir a função pois o buffer pode conter uma quebra de linha
  getchar();
  getchar();
}

// Imprime o menu e retorna a opção selecionada
int menu() {
  clearScreen();
  printf("Gerenciador de tarefas \n");
  printf("1 - Criar nova tarefa \n");
  printf("2 - Deletar tarefa \n");
  printf("3 - Atualizar tarefa \n");
  printf("4 - Consultar tarefa \n");
  printf("5 - Listar tarefas \n");
  printf("%d - Finaliza \n", EXIT);

  int op;
  scanf("%d", &op);
	
  clearScreen();
  return op;
}