### Doppelkopf

All core functionality can be found under src/core/...
The main game loop is in src/main

### Adding a Bot
The source already includes an ExampleBot, giving you an example of how to code a simple bot. 

 - Write the Bot and add it to a seperate Folder
 - Add the Folder in src/cmakelists.txt as subdirectory
 - Include a cmakelist (see ExampleBot)
 - Go to main.cpp and insert :
 '''    map.insert(std::make_pair("ExampleBot", &createInstance<ExampleBot>));
'''
