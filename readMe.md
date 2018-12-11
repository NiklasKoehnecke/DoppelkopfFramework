### Doppelkopf
The game expects to be run from a subdirectory (for ex. `/bin/doppelkopf.exe`). In order to achieve this either: 
 - run cmake out of source (See [this](https://stackoverflow.com/questions/11143062/getting-cmake-to-build-out-of-source-without-wrapping-scripts))
 - use an IDE that already supports this (CLion, Visual Studio)
#### Functionality
 - All core functionality can be found under `src/core/`  
 - The main game loop can be found in `src/main` 

### Test
Tests are off by default. To enable them follow these steps:
 1. Run `git submodule init` and `git submodule update` to get the gtest test framework in `libs/googletest`
 2. Pass `-DADD_TESTS=ON` to cmake when loading the cmake project(for ex. in the gui or when running the cmake command)

### Adding a Bot
The source already includes an ExampleBot, giving you an example of how to code a simple bot. 

 - Write the Bot and add it to a seperate Folder
 - Add the Folder in src/cmakelists.txt as subdirectory
 - Include a cmakelist (see ExampleBot)
 - Go to main.cpp and add under createPlayerMapping():
 ```    
 map.insert(std::make_pair("BotName", &createInstance<BotClass>));
```
 - The "BotName" has to be added in the player.csv together with a int in the same lane and an adjustment of the first number
