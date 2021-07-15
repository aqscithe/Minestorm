# Project Minestorm
# Cours GP1

By Leon Thompson

## DESCRIPTION
You control a spaceship in either a single player or a two-player mode where the goal is to destroy all of the mines that spawn in the level.
You will face mines making their wayward and unerring journey through space, mines that seem to be quite attracted to you and even those that 
shoot fireballs. You win upon destruction of the final mine on the final level. Go nuts!!

## INSTALLATION

To simply play the game:
- Download the latest build: https://game-project-assets.s3.amazonaws.com/Minestorm/build.zip
- Extract the zip
- Launch from "game.exe"

To launch from Visual Studio:
- Download ZIP of code & extract.
- Download assets here: https://game-project-assets.s3.amazonaws.com/Minestorm/assets.zip
- Extract assets
- Place the assets folder 

### CONTROLS:

Main Menu
- ESC:  Exit the game
- F:   Play solo
- K:   Play 2-player

Pause Screen
- P:   Unpause the game
- ESC: Quit the level

In Game
- P:   Pause the game
- C:   Toggle collision lines

	PLAYER 1:
		R:   Thrust
		D:   Rotate Left
		G:   Rotate Right
		F:   Fire Bullets
		E/T: Teleport to Random Location

	PLAYER 2:
		I:   Thrust
		H:   Rotate Left
		K:   Rotate Right
		J:   Fire Bullets
		U/O: Teleport to Random Location


### Project Structure
* src
	* MathToolbox
	* Entity
		* Mine
			* FireballMine
			* FloatingMine
			* HybridMine
			* MagneticMine
		* Minelayer
		* Projectile
			* Bullet
			* Fireball
		* Spaceship
		* Spawn


### Math-Related Files & Directories

- (Primitive Definitions)Vector2, Line, Segment, Circle, Rectangle, OrientedRectangle, etc.
	* $(ProjectDir)/src/MathToolbox/primitives.hpp

- Methods Applying Newtonian Laws
	* $(ProjectDir)/src/Entity/Spaceship/Spaceship.cpp | Method: Spaceship::update(float elapsedTime) | Line: 164

- Local <-> World Reference Change Methods
    * $(ProjectDir)/src/MathToolbox/geo_calculs.cpp
        - localToGlobalOPWorld() | Line 176
        - localToGlobalVectorWorld() | Line 193
        - globalToLocalPPrime() | Line 202
        - globalToLocalVectorPrime() | 221
        
- SAT Collision Detection Methods
    * $(ProjectDir)/src/MathToolbox/geo_calculs.cpp
        - circleToPoint(const circle cir, const Vector2f& point) | Line 419
        - circleToLine(const circle cir, const line _line) | Line 426
        - circleToSegment(const circle cir, const segment seg) | Line 431
        - boxToCircle(const rectangle rect, const circle cir) | Line 465
        - convexPolyToConvexPoly(convexPolygon cp1, convexPolygon cp2) |  Line 527
        - convexPolyToPoint(const convexPolygon cp, const Vector2f& point) | Line 554
        
- Methods Applying Collision Detection
    * $(ProjectDir)/src/Level.cpp 
        - Level::testCollisions() | Lines 268, 288
        
- Important Math Methods
	- Defined in $(ProjectDir)/src/MathToolbox/geo_calculs.cpp 
		- rotatePoint() | Line 151 
			- Applied at $(ProjectDir)/src/Entity/Entity.cpp | Lines 136, 168
		- getVector() | Line 17
		- vecMagnitude() | Line 22
		- getDistance() | Line 27, 32, 53
		- getDirShortestDistance() | Line 37
			- Applied at $(ProjectDir)/src/Level.cpp | Line 346
			- Applied at $(ProjectDir)/Entity/Mine/Mine.cpp | Line 59
		-  dotProduct() | Line 94
			- Applied at $(ProjectDir)/src/MathToolbox/geo_calculs.cpp | Lines 134, 208, 225, 503, 522
		- normal() | Line 110
			- Applied at $(ProjectDir)/src/MathToolbox/geo_calculs.cpp | Lines 360, 369, 428, 487
		- getAngle() | Line 125
		- angleClamp() | Line 456
			- Applied at $(ProjectDir)/Entity/Entity.cpp | Line 98
		- getPolyNormals() | Line 482
			- $(ProjectDir)/src/MathToolbox/geo_calculs.cpp | Line 539 
		- getPolyRanges() | Line 493
			-  $(ProjectDir)/src/MathToolbox/geo_calculs.cpp | Line 542

### UNFINISHED:

* For now all objects are just using the AABB collision box for collisions.
* Not yet implemented ability to replay after successfully compeleting all the levels.
* No Player <-> Fireball projectile implemented
* No visual cues indicating the end of one level and the beginning of the next.


### BUGS
* Hybrid and Fireball mines shoot a fireball projectile at an extremely high speed upon destruction.
* Upon death, if the player is pressing any button the ship begins to do that action(firing, turning, etc) at a very fast rate until the player regains control of the ship. This is more obvious when the collision lines are activated. When the ship explodes, it first enters an exploding phase where the player does not have control of the ship. As there is no control during this phase, I'm not quite sure what the probleme is here.
* The more precise collision lines that have been implemented(on the ship and magnetic mine) show on their respective objects but also in seemingly random places on the screen. It appears that these lines are being drawn multiple times.
