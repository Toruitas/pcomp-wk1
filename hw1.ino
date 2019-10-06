// This Sketch is for Week 1's game homework.
// It will implement a simplified rendition of the hand game 0, 5, 10, 15, 20
// The computer is always player 1, and will light up 0, 1, or 2 LEDs, adding to 0, 5, or 10 points.
// There will be a countdown 4, 3, 2, 1, then a flash of up to 4 lights for the "bet" plus 1 white light signifying that it is a bet and a second flash. 
// Second flash signifies what the CPU has played.
// Player has 150ms to respond by pressing 0, 1, or 2 buttons. The amount must NOT add up to what was thrown.
// Green lights flash for a WIN. Red for a loss. 
// After 3 rounds, winner is announced. Green for User or red for CPU.


// initialize variables

int playing = 0;
int winsPlayer = 0;
int winsCPU = 0;
int targetVal = 0;
int gameRound = 0;
int validValues[5] = {0, 5, 10, 15, 20};
int cpuValidHand[3] = {0, 5, 10};
int cpuValidHand1[2] {5, 10};
int cpuValidHand2[2] = {0, 5};
int numLights = 0;
int cpuHand = 0;
int playerHand[2] = {0,0};
int maxRounds = 7;
int awaitingCPU = 0;
int awaitingUser = 0;
int roundPlayed = 0;
int playingRound = 0;
int cpuLights = 0;
int roundTimer = 500;
unsigned long roundStartTimer = 0;
unsigned long now = 0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);

}

void loop() { 

  if (!playing){
      // signal light saying: you should hit this button to start the game.
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      pinMode(13, OUTPUT);
      delay(5);
      digitalWrite(13, HIGH);
      delay(5);
      pinMode(13, INPUT);
      delay(50);
      pinMode(13, OUTPUT);
      digitalWrite(13, LOW);
      delay(5);
      pinMode(13, INPUT);
      
      if(digitalRead(13) == HIGH){
        playing = 1;
        pinMode(13, OUTPUT);
      }
  }else if (playing){
    // make sure we only do this part on a new round, when the user hasn't provided any input
    if (!playingRound){
      playingRound = 1;
      awaitingCPU = 1;
      awaitingUser = 0;

      // set the table for the round. (lights off!)
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      pinMode(11, OUTPUT);
      pinMode(12, OUTPUT);
      pinMode(13, OUTPUT);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

      delay(100);
    }else if(playingRound){
      if (awaitingCPU && !awaitingUser){
        digitalWrite(13, LOW);
        // generate a target from validValues
        targetVal = validValues[rand() % 5];

        // determine how many lights to show (divide by 5). Will be 4, 3, 2, 1, 0
        numLights = targetVal / 5;
        // illuminate the lights
        if (numLights >= 1){
          digitalWrite(8, HIGH);
        }
        if (numLights >= 2){
          digitalWrite(11, HIGH);
        }
        if (numLights >=3){
          digitalWrite(9, HIGH);
        }
        if (numLights == 4){
          digitalWrite(12, HIGH);
        }
        delay(500);
        // set all competitors' lights to low before the game is played. Redundant.
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        
        delay(100);

        // flash the white light as a sort of countdown
        digitalWrite(13, HIGH);
        delay(700);
        digitalWrite(13, LOW);
        delay(300);
        digitalWrite(13, HIGH);
        delay(700);
        // get these pins ready for input
        pinMode(11, INPUT);  
        pinMode(12, INPUT);
        digitalWrite(13, LOW);
        delay(300);
        digitalWrite(13, HIGH);  // This last one means GAME ON

        // Computer hands
        // If 10 or more points on the table, computer can choose 0, 5, 10
        // If 5, can do 0, 5
        // If 0, can only bet 0
        if (numLights >= 3){
          cpuHand = cpuValidHand1[rand() % 2];
        }else if (numLights == 2){
          cpuHand = cpuValidHand[rand() % 3];
        }else if (numLights == 1){
          cpuHand = cpuValidHand2[rand() % 2];
        }else{
          cpuHand = 0;
        }
        // convert cpuHand into cpuLights for embrightening the red lights.
        // Probably could refactor the lights display functionality into its own function, but, since there's one global, one red, and one green usage of each, this way is simpler and more readable.
        cpuLights = cpuHand / 5;
        if (cpuLights >= 1){
          digitalWrite(8, HIGH);
        }
        if (cpuLights==2){
          digitalWrite(9, HIGH);
        }

        // CPU is finished, so now we must mark that it's the user's turn for the next loops.
        // so we set the user response timer and set the flag signifying it's the user's turn.
        // Realistically, this happens concurrently w/ CPU player.
        awaitingUser = 1;
        awaitingCPU = 0;
        roundStartTimer = millis();
      // If we're waiting for the user in this round.
      }else if(awaitingUser){
        now = millis();
        if (now - roundStartTimer > roundTimer){
          // round is short enough we can get away with not tracking whether or not the user hits the buttons.
          // for a longer round, have to track and compare priorState v currentState. buttonUnpressed, buttonPressing, buttonPressed
          // and for that, can short-circuit the round on user input.
          awaitingUser = 0;
          digitalWrite(13, LOW);
        }else{
          if (digitalRead(12) == HIGH){
            playerHand[0] = 5;
          }
          if (digitalRead(11) == HIGH){
            playerHand[1] = 5;
          }
        }
      // round should be over now. Do the math to see who won. Then reset the game.
      }else{
        // turn the lights down low
        pinMode(11, OUTPUT);
        pinMode(12, OUTPUT);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        delay(1000);
        digitalWrite(13, HIGH);  // except this, which shines to show that it's not game time?
        int playerSum = playerHand[0] + playerHand[1];
        if (playerSum + cpuHand == targetVal){
          // CPU wins
          winsCPU += 1;
        }else{
          // player wins
          winsPlayer += 1;
        }
        delay(1000);
        // flash lights to show scores first for CPU and then for user.
        if(winsCPU){
          for (int i=0; i<winsCPU; i++){
            digitalWrite(8, HIGH);
            digitalWrite(9, HIGH);
            delay(250);
            digitalWrite(8, LOW);
            digitalWrite(9, LOW);
            delay(250);
          }
        }
        if(winsPlayer){
          for (int i=0; i<winsPlayer; i++){
            digitalWrite(11, HIGH);
            digitalWrite(12, HIGH);
            delay(250);
            digitalWrite(11, LOW);
            digitalWrite(12, LOW);
            delay(250);
          }
        }
        playingRound = 0;  // round complete
        awaitingUser = 0;  // not waiting for the user anymore
        gameRound ++;
        // C++ has no array assignments, and I can't seem to import C++ libraries that'll compile for the Arduino, so here's a loop
        // that resets playerHand to 0,0! playerHand = [0,0] # in python
        for (int i=0; i<2; i++){
          playerHand[i] = 0;
        }  
        delay(1000);
      }
    } 
    
    if(gameRound >= maxRounds){
      playing = 0;
      gameRound = 0;
      winsCPU = 0;
      winsPlayer = 0;

      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      pinMode(11, OUTPUT);
      pinMode(12, OUTPUT);
      pinMode(13, INPUT);
    }
  }

  // put a bit of lag in everything, to make it more human-speed
  delay(500);

 
}
