Cub3d is the first "big" 42 project. 

To sum up (you can also see the instructions in the attached subject pdf file), this is a graphic project which goal is to recreate a labyrinth using raycasting techniques. The minilibx is widely used to achieve it.

WHAT I LEARNT
I learnt A LOT with this project. 

HOW TO COMPUTE
You have to call make and a Cub3d program is created. You have then to call it with a ".cub" extension file which contains all the data needed to create the game (see below). Another (optional) argument ("--save") may be called to create a screenshot of the very first image of the game.

DIFFERENCE BETWEEN COMPULSORY AND BONUSES
The compulsory part is what was needed to validate the project and go further in the curriculum. 42 requires us to separate both.
The bonuses part is the compulsory part plus some bonuses.
Both parts are computable in their respective folders.
As I decided to get a bit zealous and realised much bonuses, the compulsory part and the bonuses part are then quite different. That is also due to the fact that I learnt much from the beggining of this project until the end and therefore, my coding "style" changed too.

WHAT YOU WILL FIND IN THIS GAME
-> In both parts :
	- In the ".cub" file you can (see the subject pdf to know how) :
		- determinate the window size. If it's bigger than your screen it is supposed to resize to your actual screen values. NB : another minilibx version has a function which gets the size of your screen. I do not use this version. Therefore, you have to check that the maximum values at the end of the resolution.c file are correct for your screen;
		- determinate the walls textures;
		- determinate different colors for floor and ceiling/sky;
		- set one sprite (object) in the map one or several times;
		- determinate the direction the player first looks at (N/S/E/W);
	- If the different elements of the cub file are not correctly set (once again, see the pdf file), the program will end cleanly without any segfault or leak and with an error message explaining why it ended;
	- You can travel in a map you created in the ".cub" file :
		- ZQSD keys move the player as usual;
		- Right and left arrow keys move the camera accordingly (and therefore allow to turn);
	- The P key creates and stores a screenshot of the game in the screenshot folder;
	- The ESC key and the red cross of the window close the game cleanly (no leak);

-> In the bonuses part only :
	- The scene can be a skybox if you call a ".cub" file named "[whatever]skybox.cub". The path used for the skybox image shall be the NO path. The other wall paths are not used but you still have to set correct images paths so you do not have a message error ;) . The result is sincerely not amazing (correct though) but I spent a lot of time on this item and decided to move on; 
	- The floor and the ceiling/sky are textured. You then need to set a path to an image in the ".cub" file and not a RGB color anymore;
	- A HUD has been set. It includes :
		- A life bar set to a 100 at the beginning of the game;
		- A map that displays the player's position and rotates accordingly;
	- Several sprites can now be set. In the ".cub" file, instead of just "S", write "S2" before the path for sprites "2" in the map, same for "S3" and so on until 9 included;
	- Sprites "2" hurt the player and then disappear;
	- Sprites "3" heel the player and then disappear if her/his life was not already 100;
	- If life gets to 0 or below the game is over. But I'm a nice dude and you are offered to start over ;) ;
	- New keys :
		- Up and down keys move the camera accordingly;
		- Holding V enables kneeling;
		- Pressing SPACE enables jumping;

I first wanted to add shadows, secret doors, animations, etc but it would have been more for fun than really to learn something at this point so I decided to stop it there and move on.

ENJOY :)
