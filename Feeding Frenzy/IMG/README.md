
### 2. **Images/README.md**  
```markdown
# Images 🖼️  
This folder contains all the custom graphics, sprites, and textures used in the Feeding Frenzy game.  

## Included Graphics  
- **NEW GAME.png, GAME OPTIONS.png, EXIT.png** - Menu buttons.  
- **unmute.png, mute.png** - Sound control icons.  
- **Minnow.png, Lionfish.png, Surgeonfish.png** - Sprites for different types of fish in the game.  
- **background.png** - Background images for various levels.  

## Usage  
Images are loaded in the game using SFML's `sf::Texture` class. Make sure to correctly set the file paths when loading them in the code.  

Example:  
```cpp
Texture texture;
texture.loadFromFile("Images/Minnow.png");
