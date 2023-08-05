#include <ESP8266WiFi.h>

char ssid[] = "Vonkeck";
char pass[] = "Zimtgemahlen";
char clientData[255];

WiFiServer server(23);
static String receivedString[9]; //define how many commands your programm will have

bool checkCommand(char c, const char* command, int commandIndex) {
  if (c != '\r' && c != '\n') {
  // Create a static buffer to accumulate incoming characters
  
  receivedString[commandIndex] += c;

  // Check if the receivedString contains the command
  if (receivedString[commandIndex].indexOf(command) != -1) {
    // Command found, clear the receivedString after processing
    receivedString[commandIndex] = "";
    return true;
  }
  return false;
  }
  return false;
}


void setup()
{
  Serial.begin(9600);
  Serial.println();

  WiFi.begin(ssid, pass); //setting up connection

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) //waiting while connection is set up
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  server.setNoDelay(true);


}

void loop() {
  WiFiClient client = server.available(); //wait for a client to connect
  if(client)
  {
    Serial.println("client connected");
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        
          // Check for commands
        if (checkCommand(c, "input1", 1)) {
          // Command "input1" found, do something here
          Serial.println("Received 'input1' command!");
        } else if (checkCommand(c, "input2",2)) {
          // Command "input2" found, do something here
          Serial.println("Received 'input2' command!");
        } else if (checkCommand(c, "input3",3)) {
          // Command "input3" found, do something here
          Serial.println("Received 'input3' command!");
        }
        


      }
    }
    
  }


}