# opengles20-minigame-starter
Starter framework to create a minigame with OpenGL ES 2.0
Contact author: HMH (whalebeat@gmail.com)
==============================
* CONTENTS:
- Projects:
	+ TrainingFramework: Startup project
	+ Utilities: Provide utilities to initialize OpenGL context as well as vector/matrix calculations, TGA loading
	+ freetype: Lib to render text
- TrainingFramework.cpp: Main entry point
- Classes:
	+ Application: Singleton. Provide main game flow
	+ ResourceManagers: Singleton. Handle resources such as shaders, models, textures and fonts
	+ Camera: Used to create camera for the application. Use look-at method & ortho projection
	+ Shader, Model, Texture, Font: Manage corresponding components
	+ BaseObject: Base class for objects, derive into Sprite2D, Sprite3D, Text class
	+ Sprite2D: Used to handle 2D sprites. Derive into GameButton class
	+ Sprite3D: Used to handle 3D objects
	+ Text: Used to handle text objects
	+ GameButton: Handle game buttons
	+ GameStateBase: Base class for handling game states. Derive into other state classes as needed (GSIntro, GSMenu, GSPlay, ...)
	+ GameStateMachine: Manage state stack
==============================
* HOW TO BUILD:
- Open solution with Visual Studio Community 2019
- Build using Debug-Angle or Release-Angle
- If it's not working, try other configurations