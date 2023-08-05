#include <ESP8266WiFi.h>

//setup your WIFI Credentials here
char ssid[] = "***";
char pass[] = "***";


WiFiServer server(23); //23 is the default port the server is listening to
static String receivedString[9]; //define how many commands your programm will have

bool checkCommand(char clientData, const char* command, int commandIndex) {
  if (clientData != '\r' && clientData != '\n') { //ignore return or new line   
  receivedString[commandIndex] += clientData;  //put the recieved input data in a String. Each command has its own "place" in the array

  // Check if the receivedString contains the command
  if (receivedString[commandIndex].indexOf(command) != -1) { //check the array if command is at some place, it will return -1 if there is no command like the user wrote.
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
    while(client.connected()){ //this is true when a client is connected
      if(client.available()){ //this is true when the client object holds data transmitted by the user.
        char clientData = client.read();
        Serial.write(clientData);
        
          // Check for commands
        if (checkCommand(clientData, "input1", 1)) {
          // Command "input1" found, do something here
          Serial.println("Received 'input1' command!");
        } else if (checkCommand(clientData, "input2",2)) {
          // Command "input2" found, do something here
          Serial.println("Received 'input2' command!");
        } else if (checkCommand(clientData, "input3",3)) {
          // Command "input3" found, do something here
          Serial.println("Received 'input3' command!");
        }
      }
    }
    
  }


}