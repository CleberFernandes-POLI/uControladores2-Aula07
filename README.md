# PSI-Microcontroladores2-Aula07
Atividade: Semáforos de Pedestres e Veículos

## Objetivo
Desenvolver um sistema embarcado de controle de semáforos para pedestres e veículos, utilizando **threads** e **mutex**, e validar o funcionamento do código por meio de **testes utilizando o modelo V (testes unitários, de integração e de sistema)**.  
Opcionalmente, alunos podem utilizar **IA generativa** para auxiliar na elaboração de trechos de código ou na geração de planos de teste, mas **a avaliação deve se concentrar na qualidade dos testes e na correta validação do sistema**.

## Trabalho em Dupla
- A atividade deve ser realizada **em duplas**.
- Cada membro deve contribuir ativamente no desenvolvimento.
- **Commits no repositório Git** devem ser feitos de forma individual, permitindo a avaliação das contribuições de cada aluno.

## Descrição do Sistema
O sistema deve controlar semáforos de dois tipos: pedestres e carros, incluindo **modo noturno** e **botão de travessia de pedestres**.

### 1. Semáforo de Pedestres
- Contém dois LEDs: verde e vermelho.
- Comportamento:
  - Verde acende por 4 segundos.
  - Vermelho acende por 4 segundos.
- Controle deve ser feito por **duas threads independentes**, garantindo exclusão mútua (**mutex**) entre verde e vermelho.
- Deve ser utilizado o microcontrolador de um integrante.

### 2. Semáforo de Veículos
- Contém três LEDs: verde, amarelo e vermelho.
- Comportamento:
  - Verde acende por 3 segundos.
  - Amarelo acende por 1 segundo.
  - Vermelho acende por 4 segundos.
- Controle deve ser feito por **três threads independentes**, garantindo exclusão mútua (**mutex**) entre os LEDs.
- Deve ser validado que há **sincronismo** entre o semáforo de pedestres e o semáforo de veículos.
- Deve ser utilizado o microcontrolador do outro integrante.

### 3. Modo Noturno
- Um modo alternativo em que os semáforos piscam:
  - Carros: amarelo piscando a cada 2 segundos (1 segundo aceso, 1 segundo apagado).
  - Pedestres: vermelho piscando a cada 2 segundos (1 segundo aceso, 1 segundo apagado).

### 4. Botão de Travessia
- Permite que pedestres acionem o semáforo:
  - Pedestre verde é ativado.
  - Semáforo de carros é bloqueado de forma segura.
- O sistema deve suportar uma única via
- Controle de acesso deve garantir **consistência entre semáforos**, evitando conflito de LEDs.

## Requisitos de Projeto
1. Cada LED deve ser controlado por **uma thread**.
2. Threads devem utilizar **mutex** para evitar conflitos.
3. Modos de operação:
   - Normal (dia)
   - Noturno
   - Travessia acionada pelo botão
4. **Validação do código**
   - Alunos devem elaborar **planos de testes completos**, seguindo o **modelo V**, para garantir o correto funcionamento de cada parte e do sistema completo.
   - Testes devem incluir:
     - Testes unitários (cada semáforo)
     - Testes de integração (interação entre semáforos)
     - Testes de sistema (modos noturno e botão de travessia)
6. **Uso de IA generativa**
   - Sugestão de uso para auxiliar na geração de código ou testes.
   - A avaliação será baseada **na qualidade dos testes e nas evidências registradas no repositório**, não apenas na implementação do código.
7. **Controle de contribuições individuais**
   - Cada membro da dupla deve realizar **commits separados** no repositório.
   - A avaliação individual considerará o histórico de commits e a participação de cada aluno no desenvolvimento e validação do sistema.

## Histórico dos Commits

### 882f8d4 - Initial commit
- **Autor:** CleberFernandes-POLI
- **Data:** 16/11/2026
- Adicionou a licença do projeto e criou o arquivo `README.md` inicial.

### fa2e5a2 - First Commit - Project
- **Autor:** CleberFernandes-POLI
- **Data:** 18/11/2026
- Criou a estrutura inicial do projeto PlatformIO/Zephyr.
- Adicionou as configurações do projeto, arquivos de documentação das pastas, configuração do VS Code e o arquivo inicial `src/main.c`.

### 2fba7e8 - Código de apenas pedestres e vídeo
- **Autor:** CleberFernandes-POLI
- **Data:** 18/11/2026
- Implementou o controle inicial dos LEDs de pedestres vermelho e verde.
- Criou threads independentes, mutex e semáforos para alternar os LEDs com exclusão mútua.
- Configurou os LEDs nos pinos 18 e 19 como ativos em nível baixo.
- Definiu que o LED verde e o LED vermelho permanecem acesos por 4 segundos cada.
- Adicionou o vídeo `Video_Pedestres.mp4`.

### fb28c1b - Mudança nos Pinos para o teste no Protoboard
- **Autor:** rodriguesmurilo999
- **Data:** 19/11/2026
- Alterou os pinos dos LEDs de pedestres para o protoboard.
- O LED vermelho passou a utilizar o pino 8 e o LED verde passou a utilizar o pino 9.

### b9d11ab - Add video no protoboard
- **Autor:** rodriguesmurilo999
- **Data:** 19/11/2026
- Adicionou o vídeo `VideoPedestresProtoboard.mp4`, com o teste realizado no protoboard.

### 5df13ca - Atividade 2 code
- **Autor:** CleberFernandes-POLI 
- **Data:** 19/11/2026
- Transformou o controle em um semáforo de veículos com LEDs verde, amarelo e vermelho.
- Adicionou o LED amarelo no pino 10 e criou uma terceira thread.
- Alterou os tempos de operação para verde por 3 segundos, amarelo por 2 segundos e vermelho por 4 segundos.
- Utilizou semáforos para passar a execução entre as threads na sequência verde, amarelo e vermelho.

### 4bad06b - Erro de sintaxe
- **Autor:** rodriguesmurilo999
- **Data:** 19/11/2026
- Corrigiu a implementação da terceira thread do LED amarelo.
- Ajustou o tempo do amarelo para 1 segundo.
- Corrigiu a mensagem de inicialização do LED amarelo e a variável usada na criação da thread.

### 5e58a2a - Add Video da Atividade 2
- **Autor:** rodriguesmurilo999
- **Data:** 19/11/2026
- Adicionou o vídeo funcional da Atividade 2 em `VideoAtividade2_Funcional.mp4`.

### 63e9f4c - Código para a Etapa 3
- **Autor:** rodriguesmurilo999
- **Data:** 19/11/2026
- Renomeou os LEDs de pedestres para LEDs de veículos.
- Adicionou o botão do modo noturno no pino 11 configurado como entrada com pull-up interno.
- Implementou a ativação do modo noturno quando o botão é levado ao nível baixo, conectando-o ao GND.
- No modo noturno, o LED amarelo fica piscando por 1 segundo aceso e 1 segundo apagado.
- Ao sair do modo noturno, o programa retoma a sequência normal vermelho, verde e amarelo.
- Mantendo o controle com três threads, mutex e semáforos.

### bbef74c - Add Video modo Noturno
- **Autor:** rodriguesmurilo999
- **Data:** 19/11/2026
- Adicionou o vídeo `VideoAtividade3.mp4`, demonstrando o funcionamento do modo noturno.

### commit atual - Atualicao do README
- **Autor:** CleberFernandes-POLI
- **Data:** 23/11/2026
- Atualização do README, com o histórico de commits e resumo.
