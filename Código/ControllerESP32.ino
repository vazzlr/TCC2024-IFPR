/*
 * Pontos de Acesso com ESP32
 * Miguel Sena - blog.eletrogate.com
 */

#include <WiFi.h> //Inclui a biblioteca

const char* ssid = "ESP32-AP"; //Define o nome do ponto de acesso
const char* pass = "12345678"; //Define a senha
 
WiFiServer sv(80); //Cria um servidor na porta 80

int velocidade = 100;

void setup() {
  Serial.begin(115200); //Inicia o monitor serial
  pinMode(27, OUTPUT);  //FR
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(4, OUTPUT); //FL
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);

  pinMode(22, OUTPUT);  //BR
  pinMode(23, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(19, OUTPUT);  //BL
  pinMode(18, OUTPUT);
  pinMode(21, OUTPUT);

  delay(10);  //Atraso de 10 milissegundos

  Serial.println("\n"); //Pula uma linha
  WiFi.softAP(ssid, pass); //Inicia o ponto de acesso
  Serial.print("Se conectando a: "); //Imprime mensagem sobre o nome do ponto de acesso
  Serial.println(ssid);

  IPAddress ip = WiFi.softAPIP(); //Endereço de IP
  
  Serial.print("Endereço de IP: "); //Imprime o endereço de IP
  Serial.println(ip);

  sv.begin(); //Inicia o servidor 
  Serial.println("Servidor online"); //Imprime a mensagem de início
}

void loop() {
  WiFiClient client = sv.available(); //Cria o objeto cliente

  if (client) { //Se este objeto estiver disponível
    String line = ""; //Variável para armazenar os dados recebidos

    while (client.connected()) { //Enquanto estiver conectado
      if (client.available()) { //Se estiver disponível
        char c = client.read(); //Lê os caracteres recebidos
        if (c == '\n') { //Se houver uma quebra de linha
          if (line.length() == 0) { //Se a nova linha tiver 0 de tamanho
            client.println("HTTP/1.1 200 OK"); //Envio padrão de início de comunicação
            client.println("Content-type:text/html");
            client.println();

            client.println("<html>");
            client.println("<head>");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<title>Controle do Robô</title>");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }");
            client.println(".control { display: grid; grid-template-columns: repeat(3, 100px); grid-gap: 10px; justify-content: center; }");
            client.println("button { width: 100px; height: 50px; font-size: 16px; background-color: #4CAF50; color: white; border: none; border-radius: 10px; cursor: pointer; }");
            client.println("button:hover { background-color: #45a049; }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Controle do Robô</h1>");
            client.println("<div class=\"control\">");
            //para diagonal direita frente
            client.println("<form action=\"/diagonalfrentedireita\" method=\"get\">");
            client.println("<button type=\"submit\">Diag Frente-Dir</button>");
            client.println("</form>");
            //botão frente
            client.println("<form action=\"/Frente\" method=\"get\">");
            client.println("<button type=\"submit\">Frente</button>");
            client.println("</form>");
            //para diagonal esquerda frente
            client.println("<form action=\"/diagonalfrenteesquerda\" method=\"get\">");
            client.println("<button type=\"submit\">Diag Frente-Esq</button>");
            client.println("</form>");
            //esquerda
            client.println("<form action=\"/Esquerda\" method=\"get\">");
            client.println("<button type=\"submit\">Esquerda</button>");
            client.println("</form>");
            //parar
            client.println("<form action=\"/Parar\" method=\"get\">");
            client.println("<button type=\"submit\">Parar</button>");
            client.println("</form>");
            //direita
            client.println("<form action=\"/Direita\" method=\"get\">");
            client.println("<button type=\"submit\">Direita</button>");
            client.println("</form>");
            //diagonal trás esquerda
            client.println("<form action=\"/diagonaltrasesquerda\" method=\"get\">");
            client.println("<button type=\"submit\">Diag Trás-Esq</button>");
            client.println("</form>");
            //dtrás
            client.println("<form action=\"/Tras\" method=\"get\">");
            client.println("<button type=\"submit\">Trás</button>");
            client.println("</form>");
            //diagonal trás direita
            client.println("<form action=\"/diagonaltrasdireita\" method=\"get\">");
            client.println("<button type=\"submit\">Diag Trás-Dir</button>");
            client.println("</form>");
            //girar esquerda/horário
            client.println("<form action=\"/girarhorario\" method=\"get\">");
            client.println("<button type=\"submit\">Girar Horário</button>");
            client.println("</form>");
            //botão de dança, autonomo sla
            client.println("<form action=\"/danca\" method=\"get\">");
            client.println("<button type=\"submit\">Dança</button>");
            client.println("</form>");
            //girar direita/anti-horario
            client.println("<form action=\"/girarantihorario\" method=\"get\">");
            client.println("<button type=\"submit\">Girar Anti-Horário</button>");
            client.println("</form>");

            client.println("</div>");
            client.println("</body>");
            client.println("</html>");

            
            client.println();
            break;
          } else {   
            line = "";
          }
        } else if (c != '\r') { 
          line += c; //Adiciona o caractere recebido à linha de leitura
        }

        if (line.endsWith("GET /diagonalfrentedireita")){
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, LOW); //FR
          digitalWrite(14, LOW); 
          analogWrite(12, 0); 

          digitalWrite(4, HIGH);  //FL
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW);  //BL
          digitalWrite(18, LOW);
          analogWrite(21, 0);         

          Serial.println("ta indo para a diagonal direita F");
        }

        if (line.endsWith("GET /Frente")) { //Se a linha terminar com "/ligar", liga o led
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, HIGH); //FR
          digitalWrite(14, LOW);
          analogWrite(12, velocidade);

          digitalWrite(4, HIGH);  //FL
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, HIGH);  //BL
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);

          Serial.println("ta indo para frente");             
        }

        if (line.endsWith("GET /diagonalfrenteesquerda")){
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, HIGH); //FR
          digitalWrite(14, LOW); 
          analogWrite(12, velocidade); 

          digitalWrite(4, LOW);  //FL
          digitalWrite(2, LOW);
          analogWrite(15, 0);

          digitalWrite(22, LOW);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, 0);

          digitalWrite(19, HIGH);  //BL
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);         

          Serial.println("ta indo para a diagonal esquerda F");
        }
        
        if (line.endsWith("GET /Esquerda")){
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, HIGH); //FR
          digitalWrite(14, LOW); 
          analogWrite(12, velocidade); 

          digitalWrite(4, LOW);  //FL
          digitalWrite(2, HIGH);
          analogWrite(15, velocidade);

          digitalWrite(22, LOW);  //BR
          digitalWrite(23, HIGH);
          analogWrite(5, velocidade);

          digitalWrite(19, HIGH);  //BL
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);         

          Serial.println("ta indo para a esquerda");
        }

        if (line.endsWith("GET /Parar")) { //Se a linha terminar com "/desligar", desliga o led
          digitalWrite(27, LOW); //FR
          digitalWrite(14, LOW); 
          analogWrite(12, 0); 

          digitalWrite(4, LOW);  //FL
          digitalWrite(2, LOW);
          analogWrite(15, 0);

          digitalWrite(22, LOW);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, 0);

          digitalWrite(19, LOW);  //BL
          digitalWrite(18, LOW);
          analogWrite(21, 0);         

          Serial.println("desligou");  
        }

        if (line.endsWith("GET /Direita")){
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, LOW); //FR
          digitalWrite(14, HIGH); 
          analogWrite(12, velocidade); 

          digitalWrite(4, HIGH);  //FL
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW);  //BL
          digitalWrite(18, HIGH);
          analogWrite(21, velocidade);         

          Serial.println("ta indo para a direita");
        }

        if (line.endsWith("GET /Tras")) {
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, LOW); //FR
          digitalWrite(14, HIGH); 
          analogWrite(12, velocidade); 

          digitalWrite(4, LOW);  //FL
          digitalWrite(2, HIGH);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW);  //BL
          digitalWrite(18, HIGH);
          analogWrite(21, velocidade);         

          Serial.println("ta indo para trás"); 
        }

        if (line.endsWith("GET /diagonaltrasesquerda")){
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, LOW); //FR
          digitalWrite(14, HIGH); 
          analogWrite(12, velocidade); 

          digitalWrite(4, LOW);  //FL
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW);  //BL
          digitalWrite(18, HIGH);
          analogWrite(21, velocidade);         

          Serial.println("ta indo para a diagonal esquerda B");
        }

        if (line.endsWith("GET /diagonaltrasdireita")){
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, LOW); //FR
          digitalWrite(14, LOW); 
          analogWrite(12, velocidade); 

          digitalWrite(4, LOW);  //FL
          digitalWrite(2, HIGH);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW);  //BL
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);         

          Serial.println("ta indo para a diagonal direita B");
        }

        if (line.endsWith("GET /girarhorario")){
          velocidade = constrain(velocidade + 10, 0, 255);

          digitalWrite(27, HIGH); //FR
          digitalWrite(14, LOW); 
          analogWrite(12, velocidade); 

          digitalWrite(4, LOW);  //FL
          digitalWrite(2, HIGH);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW);  //BL
          digitalWrite(18, HIGH);
          analogWrite(21, velocidade);         

          Serial.println("girar esquerda");
        }

        if (line.endsWith("GET /girarantihorario")){
          velocidade = constrain(velocidade + 10, 0, 255);

          // Girar Direita
          digitalWrite(27, LOW); //FR para trás
          digitalWrite(14, HIGH); 
          analogWrite(12, velocidade);

          digitalWrite(4, HIGH); //FL para frente
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, HIGH); //BL para frente
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);       

          Serial.println("girar direita");
        }
        
        if (line.endsWith("GET /danca")) {
          velocidade = 100; // Define uma velocidade base
          Serial.println("Iniciando sequência de dança!");

          // Movimento 1: Frente
          digitalWrite(27, HIGH); // FR
          digitalWrite(14, LOW);
          analogWrite(12, velocidade);

          digitalWrite(4, HIGH); // FL
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, HIGH); // BL
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);

          delay(1000); // Mantém o movimento por 1 segundo

          // Movimento 2: Trás
          digitalWrite(27, LOW); // FR
          digitalWrite(14, HIGH);
          analogWrite(12, velocidade);

          digitalWrite(4, LOW); // FL
          digitalWrite(2, HIGH);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW); // BL
          digitalWrite(18, HIGH);
          analogWrite(21, velocidade);

          delay(1000); // Mantém o movimento por 1 segundo

          // Movimento 3: Esquerda
          digitalWrite(27, HIGH); // FR
          digitalWrite(14, LOW);
          analogWrite(12, velocidade);

          digitalWrite(4, LOW); // FL
          digitalWrite(2, HIGH);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, HIGH); // BL
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);

          delay(1000); // Mantém o movimento por 1 segundo

          // Movimento 4: Direita
          digitalWrite(27, LOW); // FR
          digitalWrite(14, HIGH);
          analogWrite(12, velocidade);

          digitalWrite(4, HIGH); // FL
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW); // BL
          digitalWrite(18, HIGH);
          analogWrite(21, velocidade);

          delay(1000); // Mantém o movimento por 1 segundo

          // Movimento 5: Girar (sentido horário)
          digitalWrite(27, HIGH); // FR
          digitalWrite(14, LOW);
          analogWrite(12, velocidade);

          digitalWrite(4, LOW); // FL
          digitalWrite(2, HIGH);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, HIGH); // BL
          digitalWrite(18, LOW);
          analogWrite(21, velocidade);

          delay(1000); // Mantém o movimento por 1 segundo

          // Movimento 6: Girar (sentido anti-horário)
          digitalWrite(27, LOW); // FR
          digitalWrite(14, HIGH);
          analogWrite(12, velocidade);

          digitalWrite(4, HIGH); // FL
          digitalWrite(2, LOW);
          analogWrite(15, velocidade);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW); // BL
          digitalWrite(18, HIGH);
          analogWrite(21, velocidade);

          delay(1000); // Mantém o movimento por 1 segundo

          // Parar o robô no final
          digitalWrite(27, LOW);
          digitalWrite(14, LOW);
          analogWrite(12, 0);

          digitalWrite(4, LOW);
          digitalWrite(2, LOW);
          analogWrite(15, 0);

          digitalWrite(22, HIGH);  //BR
          digitalWrite(23, LOW);
          analogWrite(5, velocidade);

          digitalWrite(19, LOW);
          digitalWrite(18, LOW);
          analogWrite(21, 0);

          Serial.println("Sequência de dança finalizada!");}

      }
    }
    client.stop();//Para o cliente
  }
}
