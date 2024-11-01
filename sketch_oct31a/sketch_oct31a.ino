class Semaforo 
{
  private:
    int* pinLuzVerde;
    int* pinLuzAmarela;
    int* pinLuzVermelha;

    void acenderLuz(int* pin, float* tempo) 
    {
      digitalWrite(*pin, HIGH);
      delay(1000 * (*tempo));
      digitalWrite(*pin, LOW);
    }

    void piscarLuz(int* pin, int* tempo)
    {
      for (float i = 0; i < *tempo; i += 0.5)
      {
        digitalWrite(*pin, HIGH);
        delay(250 * (*tempo));
        digitalWrite(*pin, LOW);
        delay(250 * (*tempo));
      }
    }

  public:
    Semaforo(int* numPinVerde, int* numPinAmarela, int* numPinVermelho)
    {
      pinLuzVerde = numPinVerde;
      pinLuzAmarela = numPinAmarela;
      pinLuzVermelha = numPinVermelho;
      pinMode(*pinLuzVerde, OUTPUT);
      pinMode(*pinLuzAmarela, OUTPUT);
      pinMode(*pinLuzVermelha, OUTPUT);
    }

    void ligar(float* tempoLuzVerde, float* tempoLuzAmarela, float* tempoLuzVermelha, int* tempoPiscarVerde)
    {
      acenderLuz(pinLuzVermelha, tempoLuzVermelha);
      acenderLuz(pinLuzAmarela, tempoLuzAmarela);
      acenderLuz(pinLuzVerde, tempoLuzVerde);

      if (*tempoPiscarVerde > 0)
      {
        piscarLuz(pinLuzVerde, tempoPiscarVerde);
      }

      acenderLuz(pinLuzAmarela, tempoLuzAmarela);
    }
};

// Definição dos pinos
int pinVerde = 9;
int pinAmarelo = 10;
int pinVermelho = 11;

// Instanciação do semáforo usando ponteiros para os pinos
Semaforo semaforo1(&pinVerde, &pinAmarelo, &pinVermelho);

void setup()
{
}

void loop()
{
  // Variáveis de tempo
  float tempoVerde = 2.0;
  float tempoAmarelo = 2.0;
  float tempoVermelho = 6.0;
  int tempoPiscarVerde = 2;

  // Chama a função ligar com ponteiros para os tempos
  semaforo1.ligar(&tempoVerde, &tempoAmarelo, &tempoVermelho, &tempoPiscarVerde);
}
