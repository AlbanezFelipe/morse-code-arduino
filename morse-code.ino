/**
  Morse Code for Arduino

  Author: Felipe Albanez Contin
  Date:   03/26/2020
*/

/*-------------------------
 * Message
 *-----------------------*/

const char message[] = "Arduino is awesome";

/*-------------------------
 * Frequency (ms)
 *-----------------------*/
 
const int dot = 150;  // dot duration
const int dash = 450; // dash duration

const int perSignal = 100; // delay of dots and dashs
const int perSymbol = 300; // delay of letters and numbers

const int perWord = 600; // delay of space

const int perMessage = 2000; // delay of message loop

/*-------------------------
 * Morse code
 *-----------------------*/

const char morse[36][5] = {
  {'.', '-'},
  {'-', '.', '.', '.'},
  {'-', '.', '-', '.'},
  {'-', '.', '.'},
  {'.'},
  {'.', '.', '-', '.'},
  {'-', '-', '.'},
  {'.', '.', '.', '.'},
  {'.', '.'},
  {'.', '-', '-', '-'},
  {'-', '.', '-'},
  {'.', '-', '.', '.'},
  {'-', '-'},
  {'-', '.'},
  {'-', '-', '-'},
  {'.', '-', '-', '.'},
  {'-', '-', '.', '-'},
  {'.', '-', '.'},
  {'.', '.', '.'},
  {'-'},
  {'.', '.', '-'},
  {'.', '.', '.', '-'},
  {'.', '-', '-'},
  {'-', '.', '.', '-'},
  {'-', '.', '-', '-'},
  {'-', '-', '.', '.'},
  {'.', '-', '-', '-', '-'},
  {'.', '.', '-', '-', '-'},
  {'.', '.', '.', '-', '-'},
  {'.', '.', '.', '.', '-'},
  {'.', '.', '.', '.', '.'},
  {'-', '.', '.', '.', '.'},
  {'-', '-', '.', '.', '.'},
  {'-', '-', '-', '.', '.'},
  {'-', '-', '-', '-', '.'},
  {'-', '-', '-', '-', '-'}
};

/*-------------------------
 * Alphabet and Numbers
 *-----------------------*/


const char symbols[36] = {'a', 'b', 'c', 'd', 'e', 'f', 
                          'g', 'h', 'i', 'j', 'k', 'l', 
                          'm', 'n', 'o', 'p', 'q', 'r', 
                          's', 't', 'u', 'v', 'w', 'x', 
                          'y', 'z', '1', '2', '3', '4', 
                          '5', '6', '7', '8', '9', '0'};

/*-------------------------
 * Functions
 *-----------------------*/

int getIndexOfSymbol(char c){
    for(int i = 0; i < 36; i++){
        if(tolower(c) == symbols[i]){
            return i;
        }
    }
    return -1;
}

int countString(const char *string){
  const char *lastAddress = string;
  
  while(*lastAddress)
    ++lastAddress;
    
  return lastAddress - string;
}

int dotOrDash(char c){
  return c == '.' ? 0 : (c == '-' ? 1 : -1);  
}

/*---------------------
 * Setup
 *-------------------*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

/*---------------------
 * Loop
 *-------------------*/

void loop() {

   for (int i = 0; i < (int) sizeof(message) - 1; i++){

      if(message[i] == ' '){ // for spaces in message
        delay(perWord - perSymbol);
        continue;  
      }
      
      const char *currentSymbolCode = morse[getIndexOfSymbol(message[i])]; // get morse code from current letter or number

      for(int j = 0; j < countString(currentSymbolCode); j++){
        
        digitalWrite(LED_BUILTIN, HIGH);
        delay(dotOrDash(currentSymbolCode[j]) ? dash : dot);
        
        digitalWrite(LED_BUILTIN, LOW);
        delay(perSignal);
      
      }
    
      delay(perSymbol - perSignal);   
  }
  
  delay(perMessage - perSymbol);
}
