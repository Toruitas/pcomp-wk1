# Homework 1 - A simple game with Arduino
Msc Creative Computing 2019
Physical Computing 1 w/ Phoenix Perry
By Stuart Leitch

### Homework brief
Get playful with buttons and LEDS. Make a simple timing game such as Simon Says with at least 3 levels and a clear start and end. Have 3 buttons for interaction and make it so you press the first botton to start the game. When the game is over, all 3 LEDS should come on and stay in until the start button is pressed again. If you have an idea for a better game, give it a go. I'm open to you editing these briefs. This is graduate school, have fun.

### Alteration
The homework as assigned seemed easy, at first blush, so I seized on the idea of coding a better game. Brainstorming led me to an unnamed 2-player game I learned in China. 

#### Game rules
Human version
---
0. Players face each other. The middle between them is where action takes place.
1. One player calls out a number in {0, 5, 10, 15, 20}.
2. Roughly simultaneously, both players throw their hands into the middle of the space between them.
3. A hand can be a closed fist (0 points) or open with fingers splayed (5 points). If the sum of all the hands matches the number from step 1, the player who called the number wins and gets to call again. 
4. If the calling player loses, the other player gets to call.

Arduino version
---
In this game, the CPU is always the one calling. So as the player, your goal is to make the number NOT match the target number. If 3 lights show as the target, your job is to try NOT to let there be 3 lights between you and the CPU.

0. Press the button next to the flashing white light to begin. Hold it down until all the lights turn off.
1. The red and green buttons will light up, between 0 and 4 of them. Each light is worth 5 points, like a hand. This is the "called" number.
2. The white light will flash 3 times. This is the countdown timer. When the 3rd flash happens, that's the signal to play. The round ends when the light turns off. Think Mario Kart, and hit the button as soon as the light goes, since rounds are short. The CPU has some very rudimentary decision making if() logic to play a better game.
3. After the round, lights flash showing how many wins each player has. Red for CPU, green for Player.
4. Next round begins. Current default is 7 rounds.


How-to-play images
---

Video of a play-through (Click to view on YouTube):

[![GAMEPLAY VIDEO](https://i9.ytimg.com/vi/gqpZJV6mhek/mqdefault.jpg?time=1570394857301&sqp=CMyk6ewF&rs=AOn4CLBayOu7qrWswHx5CyTSdRDnxaQSyA)](https://youtu.be/gqpZJV6mhek "GAMEPLAY VIDEO")

1. Click to start
![Click start](https://github.com/Toruitas/pcomp-wk1/blob/master/1_press_start.JPG)

2. Target lights display (white light off)
![Target](https://github.com/Toruitas/pcomp-wk1/blob/master/2_target.JPG)

3. Players make their moves
![Moves](https://github.com/Toruitas/pcomp-wk1/blob/master/3_player_move.JPG)

4. Scores flash after each round
![Scores](https://github.com/Toruitas/pcomp-wk1/blob/master/4_display_scores.JPG)

5. Another round starts automatically up to the max number of rounds - default is 7.