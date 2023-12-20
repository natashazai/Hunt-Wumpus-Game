Natalia Zaitseva 
Date: 26th of November 2023
Description: Hunt Wumpus game
The game about the Wumpus, where the main point is to
kill the monster or steal golden treasure and escape from the same 
room that you enreted the Wumpus cave. The user has a grid to see
where the player is, and if they will input 'T', they can see the 
debugging mode, so see the characters of events on a grid. The user
can use WASD to move 4 directions, and it can fire an arrow, using 
f as an input. The arrow can go through 3 rooms and if it missed,
there is a 75% chance that the Wumpus will wake up and change the room
that it was previously, or the user can kill the wumpus using an arrow.
Then the user wins. There are 4 different events: 
-bats, which confuses the direction of the motion, so if the user 
inputted 'w', it will go not up, but down
-stalactites, which have 50% chance that they will fall on a player
and they will die
-wumpus, if the user enters the wumpus room, it dies
-gold, if the user enter the gold room, it automatically takes
the treasure and they need to find escape rope (so the room they appeared)
to win the game 
** Input: user input for the size of the grid, direction of motion,
fire an arrow, or true or false ofr debugging mode
** Output: printed grid, different statements depending on an event
type
