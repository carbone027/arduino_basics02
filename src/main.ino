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
