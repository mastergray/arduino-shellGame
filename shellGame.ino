const int SHELL_1 = 2;
const int SHELL_2 = 4;
const int SHELL_3 = 6;

const int BUTTON_1 = 3;
const int BUTTON_2 = 5;
const int BUTTON_3 = 7;
const int SPEAKER = 8;

boolean game_started = false;
int winning_shell = 0;

int counter = 0;

void setup() {

   pinMode(SHELL_1, OUTPUT);
   pinMode(SHELL_2, OUTPUT);
   pinMode(SHELL_3, OUTPUT);
   pinMode(SPEAKER, OUTPUT);
   pinMode(BUTTON_1, INPUT);
   pinMode(BUTTON_2, INPUT);
   pinMode(BUTTON_3, INPUT);
  
}

int getShell(int shell) {
  switch (shell) {
    case 1:
      return SHELL_1;
    break;
    case 2:
      return SHELL_2;
    break;
    case 3:
      return SHELL_3;
    break;
    default:
      return NULL;
  }
}

void showShell(int shell) {

  for (counter = 0; counter < 3; counter++) {
    
    digitalWrite(getShell(shell), HIGH);
    delay(500);
    digitalWrite(getShell(shell), LOW);
    delay(500);

  }  

}


void hideShell(int shell) {

  switch(shell) {
    case 1:
      digitalWrite(SHELL_1, HIGH);
      digitalWrite(SHELL_2, LOW);
      digitalWrite(SHELL_3, LOW);
      tone(SPEAKER, 440, 100);
    break;
    case 2:
      digitalWrite(SHELL_1, LOW);
      digitalWrite(SHELL_2, HIGH);
      digitalWrite(SHELL_3, LOW);
      tone(SPEAKER, 494, 100);
    break;
    case 3:
      digitalWrite(SHELL_1, LOW);
      digitalWrite(SHELL_2, LOW);
      digitalWrite(SHELL_3, HIGH);
      tone(SPEAKER, 523, 100);
    break;
    default:
      digitalWrite(SHELL_1, LOW);
      digitalWrite(SHELL_2, LOW);
      digitalWrite(SHELL_3, LOW);
    
  }
  
  
}
void youWin() {

    // Plays 'vitctory' tone and 'light show':
    for (counter = 0; counter < 3; counter++) {
      
        tone(SPEAKER, 330 * (counter + 1));
        digitalWrite(SHELL_1, HIGH);
        digitalWrite(SHELL_2, HIGH);
        digitalWrite(SHELL_3, HIGH);
        delay(250);
       
        hideShell(0);
        delay(250);
    }
    
    noTone(SPEAKER); // turns off speaker;
    game_started = false; // resets game state;

}

void youLose() {
  
  // plays 'defeated' tone and shows correct shell:
     tone(SPEAKER, 73, 250); 
     showShell(winning_shell);
  
  game_started = false; // resets game state;
  
}


void loop() {
  
 // Begins game when all buttons have been pressed and a game has not already started: 
  if (digitalRead(BUTTON_1) == HIGH && digitalRead(BUTTON_2) == HIGH && digitalRead(BUTTON_3) == HIGH && !game_started) {
    
    delay(200);   // mitigates debounce;
    showShell(1); // shows shell to be hidden;
    delay(250);   // pause before game begins;
    
    // Randomizes winnging shell for 15 'rounds':
       for (counter = 0; counter < 16; counter++) {
        
            winning_shell = random(3) + 1; // randomizes winning shell;
            hideShell(winning_shell);      // shows winning shell;
            delay(200);                    // pause before moving shell again;
        
       }
  
    hideShell(0); // hides all shells after winnig shell is selected;
    game_started = true; // sets game state;
      
  
  }

  // Handles button presses after game has begun:
  
  if (digitalRead(BUTTON_1) == HIGH && game_started) {
    
    if (winning_shell == 1) {
      
      youWin();
      
    } else {
      
      youLose();
      
    }
    
  }

  if (digitalRead(BUTTON_2) == HIGH && game_started) {
    
    if (winning_shell == 2) {
      
      youWin();
      
    } else {
      
      youLose();
      
    }
  }

  if (digitalRead(BUTTON_3) == HIGH && game_started) {
    
    if (winning_shell == 3) {
      
      youWin();
      
    } else {
      
      youLose();
      
    }
  }

}
