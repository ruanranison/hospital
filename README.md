# Sistema de Gerenciamento de Fila de Atendimento de Hospital

## Descrição

Este programa é uma simulação de um sistema de gerenciamento de filas em um hospital. Ele organiza pacientes em filas de acordo com a gravidade dos sintomas e permite o gerenciamento do atendimento e internação. Além disso, o programa pode gerar relatórios detalhados sobre o atendimento dos pacientes.

## Funcionalidades

- **Cadastro de Pacientes**: Permite adicionar pacientes à fila com base na gravidade dos sintomas e se precisam de internação.
- **Atendimento de Pacientes**: Atende o paciente com a maior prioridade e, se necessário, o encaminha para a fila de internação.
- **Exibição de Filas**: Mostra todos os pacientes em cada fila de gravidade e na fila de internação.
- **Geração de Relatórios**: Cria relatórios sobre o total de pacientes, internos, tratamentos e pacientes em internação.

## Estrutura do Programa

### Estruturas de Dados

- **Paciente**: Armazena informações sobre o paciente, como nome, dados pessoais, gravidade, tratamento e status de internação.
- **Fila**: Utiliza uma lista encadeada para gerenciar a ordem de atendimento dos pacientes.

### Funções Principais

- **`novoPaciente`**: Cria um novo paciente com as informações fornecidas.
- **`criarFila`**: Inicializa uma nova fila vazia.
- **`enfileirar`**: Adiciona um paciente à fila apropriada com base na gravidade.
- **`desenfileirar`**: Remove o paciente da frente da fila e o retorna.
- **`exibirFila`**: Exibe todos os pacientes em uma fila específica.
- **`liberarFila`**: Libera a memória alocada para a fila.
- **`gerarRelatorios`**: Gera relatórios detalhados sobre o atendimento e internações.

### Menu de Operações

1. **Adicionar Paciente**:
   - Solicita informações do paciente, incluindo nome, dados pessoais, tratamento, gravidade (1 a 4) e se será internado.
   - Adiciona o paciente à fila correspondente com base na gravidade.

2. **Atender Paciente**:
   - Atende o paciente com a maior prioridade (menor número de gravidade) na fila.
   - Se o paciente precisa de internação, ele é movido para a fila de internação.

3. **Exibir Filas**:
   - Mostra todos os pacientes em cada fila de gravidade e na fila de internação.

4. **Gerar Relatórios**:
   - Exibe um relatório com:
     - Total de pacientes em cada fila de gravidade.
     - Total de pacientes internos.
     - Total de tratamentos realizados.
     - Total de pacientes na fila de internação.

5. **Sair**:
   - Encerra o programa.
