#include <Adafruit_NeoPixel.h>

// Hardware pin definitions
#define NEOPIXEL_PIN 4
#define JOYSTICK_UP_PIN 35
#define JOYSTICK_DOWN_PIN 34
#define JOYSTICK_LEFT_PIN 26
#define JOYSTICK_RIGHT_PIN 25
#define BUTTON_A_PIN 23
#define BUTTON_RESET 5

// Display settings
#define NUM_LEDS 128
#define WIDTH 16
#define HEIGHT 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Game settings
#define SNAKE_LENGTH 32 // maximum length of the snake
#define GAME_SPEED 200  // Slower speed of the game, increased from 150 to 200
int snake[SNAKE_LENGTH][2]; // snake segments {x, y}
int snakeLength = 3;        // initial snake length
int food[2] = {7, 4};       // initial food position
int direction = 1;          // initial direction: 0=up, 1=right, 2=down, 3=left
unsigned long lastUpdate = 0; // last update time

// Digit patterns for displaying numbers
const uint8_t digitPatterns[10][5] = {
    {0b111, 0b101, 0b101, 0b101, 0b111}, // 0
    {0b110, 0b010, 0b010, 0b010, 0b111}, // 1
    {0b111, 0b001, 0b111, 0b100, 0b111}, // 2
    {0b111, 0b001, 0b111, 0b001, 0b111}, // 3
    {0b101, 0b101, 0b111, 0b001, 0b001}, // 4
    {0b111, 0b100, 0b111, 0b001, 0b111}, // 5
    {0b111, 0b100, 0b111, 0b101, 0b111}, // 6
    {0b111, 0b001, 0b001, 0b001, 0b001}, // 7
    {0b111, 0b101, 0b111, 0b101, 0b111}, // 8
    {0b111, 0b101, 0b111, 0b001, 0b111}  // 9
};

void setup() {
    Serial.begin(115200);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    
    pinMode(JOYSTICK_UP_PIN, INPUT_PULLUP);
    pinMode(JOYSTICK_DOWN_PIN, INPUT_PULLUP);
    pinMode(JOYSTICK_LEFT_PIN, INPUT_PULLUP);
    pinMode(JOYSTICK_RIGHT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_RESET, INPUT_PULLUP);

    resetGame(); // Initialize the game state
}

void loop() {
    if (millis() - lastUpdate > GAME_SPEED) {
        lastUpdate = millis();
        updateGame();
        handleInput();
    }
}

void updateGame() {
    int newHeadX = snake[0][0];
    int newHeadY = snake[0][1];
    switch (direction) {
        case 0: newHeadY--; break;
        case 1: newHeadX++; break;
        case 2: newHeadY++; break;
        case 3: newHeadX--; break;
    }

    if (newHeadX < 0 || newHeadX >= WIDTH || newHeadY < 0 || newHeadY >= HEIGHT) {
        showScore(snakeLength - 3);
        resetGame();
        return;
    }
    for (int i = 1; i < snakeLength; i++) {
        if (snake[i][0] == newHeadX && snake[i][1] == newHeadY) {
            showScore(snakeLength - 3);
            resetGame();
            return;
        }
    }

    if (newHeadX == food[0] && newHeadY == food[1]) {
        snakeLength = snakeLength < SNAKE_LENGTH ? snakeLength + 1 : snakeLength;
        placeFood();
    }

    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }
    snake[0][0] = newHeadX;
    snake[0][1] = newHeadY;

    drawGame();
}

void handleInput() {
    if (!digitalRead(JOYSTICK_UP_PIN) && direction != 2) direction = 0;
    if (!digitalRead(JOYSTICK_RIGHT_PIN) && direction != 3) direction = 1;
    if (!digitalRead(JOYSTICK_DOWN_PIN) && direction != 0) direction = 2;
    if (!digitalRead(JOYSTICK_LEFT_PIN) && direction != 1) direction = 3;
    if (!digitalRead(BUTTON_RESET)) resetGame();
}

void drawGame() {
    strip.clear();
    for (int i = 0; i < snakeLength; i++) {
        strip.setPixelColor(snake[i][1] * WIDTH + snake[i][0], strip.Color(0, 255, 0)); // Snake in green
    }
    strip.setPixelColor(food[1] * WIDTH + food[0], strip.Color(255, 0, 0)); // Food in red
    strip.show();
}

void placeFood() {
    food[0] = random(WIDTH);
    food[1] = random(HEIGHT);
}

void resetGame() {
    snakeLength = 3;
    for (int i = 0; i < snakeLength; i++) {
        snake[i][0] = WIDTH / 2;
        snake[i][1] = HEIGHT / 2;
    }
    placeFood();
}

void showScore(int score) {
    strip.clear();
    displayDigit(score / 10, 3);  // Tens at column 3
    displayDigit(score % 10, 8);  // Ones at column 8, with a space in between
    strip.show();
    delay(3000); // Show score for 3 seconds before clearing
    strip.clear();
    strip.show();
}

void displayDigit(int digit, int startX) {
    if (digit < 0 || digit > 9) return; // Invalid digit
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
            if (digitPatterns[digit][row] & (1 << (2 - col))) {
                int pixelIndex = (row * WIDTH) + (startX + col); // Calculate the pixel index
                strip.setPixelColor(pixelIndex, strip.Color(0, 255, 0)); // Set color to green
            }
        }
    }
}
