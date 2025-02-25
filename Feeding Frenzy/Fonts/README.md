# Fonts 📚  
This folder contains all the custom fonts used in the Feeding Frenzy game for styling text elements, such as menus, scores, and in-game messages.  

## Included Fonts  
- **HTDaisyDelight-Regular-PersonalUse.otf** - Used for playful and whimsical text elements.  
- **GUMDROP.ttf** - Utilized for bold and prominent headers.  

## Usage  
Fonts are loaded in the game using SFML's `sf::Font` class. Make sure to correctly set the file paths when loading them in the code.  

Example:  
```cpp
Font font;
font.loadFromFile("Fonts/HTDaisyDelight-Regular-PersonalUse.otf");
