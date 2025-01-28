# Projeto 04: **Animações em Matriz de LEDs com Raspberry Pi Pico W**
**EMBARCATECH - UNIDADE 04**


## Desenvolvedores
**Desenvolvido pelo SubGrupo 9 - Grupo 4**
- **Adryellen Alves de Souza**  
- **Carlos Henrique Silva Lopes**
- **Graziele Coelho de Alencar**  
- **Nivaldo Rodrigues da Silva Júnior**  
- **Uriel Hapuque Barboza Santos**


## **Link do vídeo de Ensaio**
https://drive.google.com/file/d/120fpWD6Y9wA-tB3xdyNqKnIiiZ1wwcCg/view?usp=sharing

## **Descrição do Projeto**
Este projeto utiliza o Raspberry Pi Pico W, um teclado matricial 4x4 e uma matriz de LEDs coloridos (5x5 WS2812) para criar animações visuais, simulando o funcionamento da matriz de leds no ambiente de desenvolvimento Wokwi. O sistema permite controlar as animações por meio das teclas do teclado matricial.


## **Funcionalidades**

1. **Controle da matriz de LEDs**:
   - Cada tecla numérica (0 a 9) ativa uma animação diferente na matriz de LEDs.
   - Cada animação possui no mínimo 5 frames, com uma taxa de 1 FPS (1 frame por segundo).

2. **Funções de controle:**
   - Tecla A: Desliga todos os LEDs.
   - Tecla B: Liga todos os LEDs na cor azul (100% de intensidade).
   - Tecla C: Liga todos os LEDs na cor vermelha (80% de intensidade).
   - Tecla D: Liga todos os LEDs na cor verde (50% de intensidade).
   - Tecla #: Liga todos os LEDs na cor branca (20% de intensidade).
  
3. **Função do buzzer:**
   - Todas as teclas de 0 a 9 emitem sinal sonoro com buzzer, assim como a animação.


## Requisitos de Execução
- **Hardware:** 
  - Raspberry Pi Pico W
  - Teclado matricial 4x4
  - Componente Buzzer
  - Matriz de LEDs Coloridos (LED-RGB 5x5 WS2812)
- **Software:**
  - Visual Studio Code com Pico SDK configurado
  - Simulador Wokwi


## Configuração do Projeto

1. Clone este repositório para sua máquina:

   ```
   git clone https://github.com/CarlosHenriqueSL/Projeto-04-EmbarcaTech.git
   ```

2. Certifique-se de que o **Pico SDK** está configurado no VS Code.

3. Abra o projeto no **VS Code** e configure os arquivos `CMakeLists.txt` adequados para compilar o código.

4. Execute o projeto no simulador **Wokwi** ou faça o upload para o hardware físico do Raspberry Pi Pico W.


## Estrutura do Código

### Principais Arquivos
- **`pio_matrix.c`**: Contém a lógica principal para ler o teclado 4x4 e fazer o acionamento da matriz de LEDs, além de regular a coloração e intensidade dos LEDs.
- **`diagram.json`**: Configuração física do projeto no simulador Wokwi.
- **`desenhos`**: Contém os desenhos que serão feitos na matriz de LEDs.
- **`buzzers`**: Contém os códigos responsáveis pelos sinais sonoros do buzzer.
- **`pio_matrix.pio`**: Contém a configuração em Assembly para funcionamento do pio.
- **`README.md`**: Documentação detalhada do projeto.

### Funções Principais

#### `void iniciar_teclado()`
- Configura os pinos GPIO associados às linhas e colunas do teclado matricial.

#### `char get_tecla()`
- Lê a tecla pressionada no teclado matricial e retorna o caractere correspondente.

#### `uint32_t matrix_rgb()`
- Responsável por retornar a cor correta à ser acesa.

#### `void desenho_pio()`
- Mostra o desenho recebido na matriz de LEDs, na cor correta.



## Testes e Validação

1. Pressione as teclas no teclado matricial e observe as ações:
   - **0 a 9**: Animações de 5 frames devem aparecer na matriz de LEDs.
   - **A**: Os LEDs devem desligar.
   - **B**: Os LEDs devem ser ligados em azul, com 100% da intensidade.
   - **C**: Os LEDs devem ser ligados em vermelho, com 80% da intensidade.
   - **D**: Os LEDs devem ser ligados em verde, com 50% da intensidade.
   - **#**: Os LEDs devem ser ligados em branco (todas as cores), com 20% da intensidade.

3. Certifique-se de que o comportamento está de acordo com o esperado tanto no simulador quanto no hardware real.
