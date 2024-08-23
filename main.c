#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do paciente
typedef struct Paciente {
    char nome[50];
    char dadosPessoais[100];  // Dados adicionais, como idade, endereço, etc.
    int gravidade;
    char tratamento[100];
    int interno; // 0: não, 1: sim
    struct Paciente* proximo;
} Paciente;

// Definição da fila
typedef struct Fila {
    Paciente* frente;
    Paciente* traseira;
} Fila;

// Função para criar um novo paciente
Paciente* novoPaciente(char* nome, char* dadosPessoais, int gravidade, char* tratamento, int interno) {
    Paciente* p = (Paciente*)malloc(sizeof(Paciente));
    strcpy(p->nome, nome);
    strcpy(p->dadosPessoais, dadosPessoais);
    p->gravidade = gravidade;
    strcpy(p->tratamento, tratamento);
    p->interno = interno;
    p->proximo = NULL;
    return p;
}

// Função para criar uma fila
Fila* criarFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->frente = f->traseira = NULL;
    return f;
}

// Função para enfileirar um paciente
void enfileirar(Fila* f, char* nome, char* dadosPessoais, int gravidade, char* tratamento, int interno) {
    Paciente* p = novoPaciente(nome, dadosPessoais, gravidade, tratamento, interno);
    if (f->traseira == NULL) {
        f->frente = f->traseira = p;
        return;
    }
    f->traseira->proximo = p;
    f->traseira = p;
}

// Função para desenfileirar um paciente
Paciente* desenfileirar(Fila* f) {
    if (f->frente == NULL)
        return NULL;

    Paciente* p = f->frente;
    f->frente = f->frente->proximo;

    if (f->frente == NULL)
        f->traseira = NULL;

    return p;
}

// Função para exibir a fila de pacientes
void exibirFila(Fila* f) {
    Paciente* p = f->frente;
    while (p != NULL) {
        printf("Paciente: %s, Dados Pessoais: %s, Gravidade: %d, Tratamento: %s, Interno: %s\n",
               p->nome, p->dadosPessoais, p->gravidade, p->tratamento, p->interno ? "Sim" : "Não");
        p = p->proximo;
    }
}

// Função para liberar a memória alocada para a fila
void liberarFila(Fila* f) {
    Paciente* p;
    while ((p = desenfileirar(f)) != NULL) {
        free(p);
    }
    free(f);
}

// Função para exibir o menu
void exibirMenu() {
    printf("\n1. Adicionar paciente\n");
    printf("2. Atender paciente\n");
    printf("3. Exibir filas\n");
    printf("4. Gerar relatórios\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para gerar relatórios
void gerarRelatorios(Fila* filaGravidade1, Fila* filaGravidade2, Fila* filaGravidade3, Fila* filaGravidade4, Fila* filaInternacao) {
    int totalPacientes = 0;
    int totalInternos = 0;
    int totalTratamentos = 0;
    int totalPacientesInternacao = 0;

    // Relatório de filas por gravidade
    printf("Relatório de Pacientes:\n");

    printf("Fila de Gravidade 1:\n");
    exibirFila(filaGravidade1);
    
    printf("Fila de Gravidade 2:\n");
    exibirFila(filaGravidade2);

    printf("Fila de Gravidade 3:\n");
    exibirFila(filaGravidade3);

    printf("Fila de Gravidade 4:\n");
    exibirFila(filaGravidade4);

    printf("Fila de Internação:\n");
    exibirFila(filaInternacao);

    // Contar totais
    Paciente* p;
    Fila* filas[4] = {filaGravidade1, filaGravidade2, filaGravidade3, filaGravidade4};
    for (int i = 0; i < 4; i++) {
        p = filas[i]->frente;
        while (p != NULL) {
            totalPacientes++;
            if (p->interno) totalInternos++;
            totalTratamentos++; // Contar cada paciente como um tratamento
            p = p->proximo;
        }
    }

    // Contar totais de internação
    p = filaInternacao->frente;
    while (p != NULL) {
        totalPacientesInternacao++;
        p = p->proximo;
    }

    // Exibir totalizadores
    printf("\nTotal de pacientes: %d\n", totalPacientes);
    printf("Total de internos: %d\n", totalInternos);
    printf("Total de tratamentos: %d\n", totalTratamentos);
    printf("Total de pacientes em internação: %d\n", totalPacientesInternacao);
}

int main() {
    // Criar filas para cada nível de gravidade e fila de internação
    Fila* filaGravidade1 = criarFila();
    Fila* filaGravidade2 = criarFila();
    Fila* filaGravidade3 = criarFila();
    Fila* filaGravidade4 = criarFila();
    Fila* filaInternacao = criarFila();

    int opcao;
    char nome[50];
    char dadosPessoais[100];
    char tratamento[100];
    int gravidade;
    int interno;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Nome do paciente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';  // Remover o caractere de nova linha
                printf("Dados pessoais do paciente: ");
                fgets(dadosPessoais, sizeof(dadosPessoais), stdin);
                dadosPessoais[strcspn(dadosPessoais, "\n")] = '\0';  // Remover o caractere de nova linha
                printf("Tratamento do paciente: ");
                fgets(tratamento, sizeof(tratamento), stdin);
                tratamento[strcspn(tratamento, "\n")] = '\0';  // Remover o caractere de nova linha
                do {
                    printf("Gravidade (1-4): ");
                    scanf("%d", &gravidade);
                } while (gravidade < 1 || gravidade > 4);
                printf("Paciente deve ser internado? (1 para Sim, 0 para Não): ");
                scanf("%d", &interno);
                
                // Enfileirar o paciente na fila correta
                switch (gravidade) {
                    case 1:
                        enfileirar(filaGravidade1, nome, dadosPessoais, gravidade, tratamento, interno);
                        break;
                    case 2:
                        enfileirar(filaGravidade2, nome, dadosPessoais, gravidade, tratamento, interno);
                        break;
                    case 3:
                        enfileirar(filaGravidade3, nome, dadosPessoais, gravidade, tratamento, interno);
                        break;
                    case 4:
                        enfileirar(filaGravidade4, nome, dadosPessoais, gravidade, tratamento, interno);
                        break;
                }
                printf("Paciente adicionado com sucesso!\n");
                break;

            case 2:
                printf("Atendendo paciente...\n");
                Paciente* atendido = NULL;

                if (filaGravidade1->frente != NULL) {
                    atendido = desenfileirar(filaGravidade1);
                } else if (filaGravidade2->frente != NULL) {
                    atendido = desenfileirar(filaGravidade2);
                } else if (filaGravidade3->frente != NULL) {
                    atendido = desenfileirar(filaGravidade3);
                } else if (filaGravidade4->frente != NULL) {
                    atendido = desenfileirar(filaGravidade4);
                }

                if (atendido) {
                    printf("Paciente atendido: %s, Dados Pessoais: %s, Gravidade: %d, Tratamento: %s, Interno: %s\n",
                           atendido->nome, atendido->dadosPessoais, atendido->gravidade, atendido->tratamento, atendido->interno ? "Sim" : "Não");
                    if (atendido->interno) {
                        enfileirar(filaInternacao, atendido->nome, atendido->dadosPessoais, atendido->gravidade, atendido->tratamento, atendido->interno);
                    }
                    free(atendido);
                } else {
                    printf("Nenhum paciente na fila!\n");
                }
                break;

            case 3:
                printf("Fila de Gravidade 1:\n");
                exibirFila(filaGravidade1);

                printf("Fila de Gravidade 2:\n");
                exibirFila(filaGravidade2);

                printf("Fila de Gravidade 3:\n");
                exibirFila(filaGravidade3);

                printf("Fila de Gravidade 4:\n");
                exibirFila(filaGravidade4);

                printf("Fila de Internação:\n");
                exibirFila(filaInternacao);
                break;

            case 4:
                gerarRelatorios(filaGravidade1, filaGravidade2, filaGravidade3, filaGravidade4, filaInternacao);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 5);

    // Liberar memória das filas
    liberarFila(filaGravidade1);
    liberarFila(filaGravidade2);
    liberarFila(filaGravidade3);
    liberarFila(filaGravidade4);
    liberarFila(filaInternacao);

    return 0;
}
