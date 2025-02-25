
# Sound 🔊  
This folder contains all the sound effects and background music used in Feeding Frenzy to enhance the gaming experience.  

## Included Sounds  
- **playerSpawn.wav** - Sound effect when the player spawns.  
- **crunch1.wav, crunch2.wav, crunch3.wav** - Eating sound effects for different fish types.  
- **feedingFrenzy.wav** - Audio for frenzy mode activation.  
- **mainmenu.ogg** - Background music for the main menu.  

## Usage  
Sounds are loaded in the game using SFML's `sf::SoundBuffer` and `sf::Sound` classes. Make sure to correctly set the file paths when loading them in the code.  

Example:  
```cpp
SoundBuffer buffer;
buffer.loadFromFile("Sound/playerSpawn.wav");
Sound sound;
sound.setBuffer(buffer);
sound.play();
