#include <WiFi.h>
#include <HTTPClient.h>

#define led_verde 41 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led amarelo

const int botaoPin = 18;  // Pino utilizado para controle do botão 
int estadoBotao = 0;  // Variável para ler estado do botão

const int ldrPin = 4;  // Pino para controle do sensor LDR
int threshold=600; // Define o limiar de luz do led

//Define lógica para debounce
long lastDebounceTime = 0; // Inicializa variável de último clique
long debounceDelay = 50; // Define o delay para próximo clique


//Definindo a dinâmica de modo diurno e noturno

void modonortuno(){
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  digitalWrite(led_amarelo, HIGH);
  delay(1000);
  digitalWrite(led_amarelo, LOW);
  delay(1000);
}

void modoDiurno(){
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  digitalWrite(led_verde, HIGH);
  delay(3000);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarelo, HIGH);
  delay(2000);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, HIGH);
  delay(5000);
}

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(led_amarelo, OUTPUT);

  // Inicialização das entradas
  pinMode(botaoPin, INPUT); // Inicializa botão como input

  // Inicializa os leds desligados
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() == WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Disconnected");
  }
}

void loop() {
  
  // Verifica estado do botão
  estadoBotao = digitalRead(botaoPin);

  // Lógica de clique com debounce

  if ( (millis() - lastDebounceTime) > debounceDelay) {

    if (estadoBotao == HIGH) {
      Serial.println("Botão pressionado!");
      lastDebounceTime = millis(); // Atualiza o tempo do último clique
    } else {
      Serial.println("Botão não pressionado!");
      lastDebounceTime = millis();
    }
  }
  
  // Lógica de mudança de modos de semáforo

  int ldrstatus=analogRead(ldrPin);
  Serial.println(ldrstatus);

  if(ldrstatus<=threshold){
    Serial.print("Está escuro, modo nortuno!: ");
    Serial.println(ldrstatus);
    modonortuno();
  }else{
    Serial.print("Está claro, modo diurno! ");
    Serial.println(ldrstatus);
    modoDiurno();
  }
}