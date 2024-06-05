# SnakeCade
A dynamic Snake game built with an ESP32 microcontroller and a NeoPixel LED matrix, controlled via a joystick.


# ESP32 Snake Game

## Project Description
This project is a recreation of the classic Snake game using modern electronics. It runs on an ESP32 microcontroller and displays on a NeoPixel LED matrix, with user input provided by a joystick. The game challenges players to navigate a growing snake around a grid, eating food to gain points while avoiding collisions with the snake's tail and the grid boundaries.

## Hardware Requirements
- **ESP32 Microcontroller**: Acts as the brain for the game, processing inputs and controlling outputs.
- **NeoPixel LED Matrix**: Displays the game state visually.
- **Joystick**: Allows the player to control the direction of the snake.
- **Power Supply**: Ensures adequate power to the ESP32 and the LED matrix.
- **Miscellaneous**: Connecting wires, breadboard, and resistors for setup.

## Software Requirements
- **Arduino IDE**: Used to write and upload the game code to the ESP32.
- **Adafruit NeoPixel Library**: Manages the operations of the NeoPixel LED matrix.

## Setup Instructions
1. **Assemble the Hardware**: Connect the ESP32 to the NeoPixel matrix and the joystick according to the circuit diagram provided in the repository.
2. **Install Software**: Install the Arduino IDE and include the Adafruit NeoPixel library.
3. **Upload the Game**: Open the `ESP32Snake.ino` file with Arduino IDE, connect the ESP32 via USB, and upload the code.

## How to Play
- Use the joystick to navigate the snake around the grid.
- Eat food that appears randomly to increase your score.
- Avoid hitting the walls or the snake's own tail.
- The game speeds up as the snake's length increases.

## Contributing
Contributions to this project are welcome! You can contribute in several ways:
- **Bug Reports**: File an issue if you find a bug.
- **Feature Suggestions**: Have an idea to make this game better? File an issue with your suggestion.
- **Code Contributions**: Submit a pull request with improvements or new features.

  
![Side](https://github.com/DefaultBanda/SnakeCade/assets/98918477/7c12de02-d51f-4649-9ac4-b7c05fd40998)
![Front](https://github.com/DefaultBanda/SnakeCade/assets/98918477/bce83ce0-5322-449d-a157-37ca481ca07e)
![Cabinet](https://github.com/DefaultBanda/SnakeCade/assets/98918477/8be710df-b460-4dfa-b7ce-657c5ed3f196)
![CabinetDF](https://github.com/DefaultBanda/SnakeCade/assets/98918477/aa38d0d5-e407-424b-a145-9bb78c38b496)
![Circuit](https://github.com/DefaultBanda/SnakeCade/assets/98918477/e9fbf9c8-6d5e-445a-9fe3-1046581e1200)
![Schematic](https://github.com/DefaultBanda/SnakeCade/assets/98918477/fe7952a1-1bc9-400a-b833-7004182766b0)




## License
This project is released under the MIT License. See the LICENSE file for more details.
