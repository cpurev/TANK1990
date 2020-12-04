# TANK1990
Battle City (1990)

* The code has 2 vectors, one shared among all classes and other only in game.cpp to draw on screen. 
* Moves with arrow keys{Up, Down, Right and Left}
* Space to shoot
* Enter to select
* Enemy tanks move randomly (It's lazy solution to bot pahtfinding)
* Bullets go in constant speed
* There are 3 lives; eagle, enemy lives and player lives
* Lose condition: lose all lives on either eagle or player
* Win condition: deplete enemy lives(destory all enemy)
* All the calcualtion is done on shared_ptr vector and drawing vector edited with passed index number
