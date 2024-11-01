# Sistema de Semáforo com Arduino

&nbsp;&nbsp;&nbsp;&nbsp;A montagem teórica desse circuito foi feita pelo Tinkercad:

<div align="center">
<image src="assets/foto_ponderada_semaforo_teoria.png">
</div>

<br>

&nbsp;&nbsp;&nbsp;&nbsp;Segue a montagem prática do mesmo circuito:

<div align="center">
<image src="assets/foto_ponderada_semaforo.jpg">
</div>

<br>

&nbsp;&nbsp;&nbsp;&nbsp;O sistema de semáforo para Arduino UNO foi construído por meio da utilização de LEDs e circuitos elétricos simples (_jumpers_ e resistores). Para melhor entendimento do trabaljo realizado, segue a lista completa de materiais utilizados.

| **Nome**                   | **Quantidade** |
|----------------------------|----------------|
| Jumper macho-macho preto   |        3       |
| Jumper macho-macho laranja |        3       |
| Jumper macho-macho azul    |        1       |
| Resistor 330Ω              |        3       |
| LED verde                  |        1       |
| LED vermelho               |        1       |
| LED amarelo                |        1       |
| _Protoboard_               |        1       |
| Arduino UNO                |        1       |

&nbsp;&nbsp;&nbsp;&nbsp;O código componente do _firmware_ utilizado pode ser localizado no arquivo [main.ino](src/main.ino). No entanto, para melhor visualização, segue, também nessa documentação, o código referido:

``` cpp
// Definição da classe Semaforo para controlar as luzes do semáforo
class Semaforo 
{
  private:
    // Ponteiros para os pinos das luzes do semáforo
    int* pinLuzVerde;
    int* pinLuzAmarela;
    int* pinLuzVermelha;

    // Método privado para acender uma luz por um determinado tempo
    void acenderLuz(int* pin, float* tempo) 
    {
      digitalWrite(*pin, HIGH);          // Liga a luz
      delay(1000 * (*tempo));            // Mantém a luz ligada pelo tempo especificado (em segundos)
      digitalWrite(*pin, LOW);           // Desliga a luz após o tempo passar
    }

    // Método privado para piscar uma luz por um determinado número de vezes
    void piscarLuz(int* pin, int* tempo)
    {
      for (float i = 0; i < *tempo; i += 0.5)   // Laço para controlar o número de piscadas
      {
        digitalWrite(*pin, HIGH);               // Liga a luz
        delay(250 * (*tempo));                  // Mantém a luz ligada por uma fração do tempo especificado
        digitalWrite(*pin, LOW);                // Desliga a luz
        delay(250 * (*tempo));                  // Aguarda para acender a luz novamente
      }
    }

  public:
    // Construtor da classe que inicializa os pinos do semáforo
    Semaforo(int* numPinVerde, int* numPinAmarela, int* numPinVermelho)
    {
      pinLuzVerde = numPinVerde;                // Atribui o pino verde ao ponteiro
      pinLuzAmarela = numPinAmarela;            // Atribui o pino amarelo ao ponteiro
      pinLuzVermelha = numPinVermelho;          // Atribui o pino vermelho ao ponteiro
      pinMode(*pinLuzVerde, OUTPUT);            // Define o pino verde como saída
      pinMode(*pinLuzAmarela, OUTPUT);          // Define o pino amarelo como saída
      pinMode(*pinLuzVermelha, OUTPUT);         // Define o pino vermelho como saída
    }

    // Método público para acionar o semáforo em uma sequência de tempos específicos
    void ligar(float* tempoLuzVerde, float* tempoLuzAmarela, float* tempoLuzVermelha, int* tempoPiscarVerde)
    {
      acenderLuz(pinLuzVermelha, tempoLuzVermelha);   // Acende a luz vermelha pelo tempo especificado
      acenderLuz(pinLuzAmarela, tempoLuzAmarela);     // Acende a luz amarela pelo tempo especificado
      acenderLuz(pinLuzVerde, tempoLuzVerde);         // Acende a luz verde pelo tempo especificado

      // Se houver um tempo de piscada, aciona a função de piscar a luz verde
      if (*tempoPiscarVerde > 0)
      {
        piscarLuz(pinLuzVerde, tempoPiscarVerde);     // Pisca a luz verde pelo tempo especificado
      }

      acenderLuz(pinLuzAmarela, tempoLuzAmarela);     // Acende a luz amarela novamente antes de finalizar a sequência
    }
};

// Definição dos pinos para cada luz do semáforo
int pinVerde = 9;           // Pino para a luz verde
int pinAmarelo = 10;        // Pino para a luz amarela
int pinVermelho = 11;       // Pino para a luz vermelha

// Criação do objeto semáforo utilizando ponteiros para os pinos
Semaforo semaforo1(&pinVerde, &pinAmarelo, &pinVermelho);

void setup()
{
  // Configuração inicial do Arduino
}

void loop()
{
  // Variáveis de tempo para cada fase do semáforo
  float tempoVerde = 2.0;              // Tempo em segundos para a luz verde ficar acesa
  float tempoAmarelo = 2.0;            // Tempo em segundos para a luz amarela ficar acesa
  float tempoVermelho = 6.0;           // Tempo em segundos para a luz vermelha ficar acesa
  int tempoPiscarVerde = 2;            // Quantidade de vezes que a luz verde deve piscar

  // Chama o método ligar com ponteiros para os tempos
  semaforo1.ligar(&tempoVerde, &tempoAmarelo, &tempoVermelho, &tempoPiscarVerde);
}

```

&nbsp;&nbsp;&nbsp;&nbsp;O vídeo demonstrando o funcionamento do protótipo criado pode ser acessado via [Google Drive](https://drive.google.com/file/d/1IDfqiEp3MqJ0Lgm0-0lD9Ar7vNddnAqz/view?usp=sharing).

&nbsp;&nbsp;&nbsp;&nbsp;A avaliação de pares dessa atividade foi realizada pelo aluno João Victor Wandermurem, da turma 12 do ano de 2024.1 do Inteli, do seguinte modo:

|Critério|	Contempla (Pontos)|	Contempla Parcialmente (Pontos)	|Não Contempla (Pontos)	|Observações do Avaliador|
|-|-|-|-|-|
|Montagem física com cores corretas, boa disposição dos fios e uso adequado de resistores	|Até 3	|Até 1,5	|0 |3 |	
|Temporização adequada conforme tempos medidos com auxílio de algum instrumento externo	|Até 3	|Até 1,5	|0 |3 |	
|Código implementa corretamente as fases do semáforo e estrutura do código (variáveis representativas e comentários) |	Até 3|	Até 1,5 |	0 |3 |	
|Ir além: Implementou um componente de extra, fez com millis() ao invés do delay() e/ou usou ponteiros no código |	Até 1 |	Até 0,5 |	0 |1 |	
| | | | |Pontuação Total|

&nbsp;&nbsp;&nbsp;&nbsp;Além disso, a avaliação do protótipo construído por esse mesmo aluno, foi feita da seguinte maneira:

|Critério|	Contempla (Pontos)|	Contempla Parcialmente (Pontos)	|Não Contempla (Pontos)	|Observações do Avaliador|
|-|-|-|-|-|
|Montagem física com cores corretas, boa disposição dos fios e uso adequado de resistores	|Até 3	|Até 1,5	|0 |3 |	
|Temporização adequada conforme tempos medidos com auxílio de algum instrumento externo	|Até 3	|Até 1,5	|0 |3 |	
|Código implementa corretamente as fases do semáforo e estrutura do código (variáveis representativas e comentários) |	Até 3|	Até 1,5 |	0 |3 |	
|Ir além: Implementou um componente de extra, fez com millis() ao invés do delay() e/ou usou ponteiros no código |	Até 1 |	Até 0,5 |	0 |1 |	
| | | | |Pontuação Total|