#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>

//#include "renderer.h"
//#include "renderer_data.h"
//#include "text_data.h"


//text rendering vars
#define NUM_ROWS 5
#define NUM_COLS 5
#define DIGIT_WIDTH 6
#define RECT_SIZE 4
#define MAX_DIGITS 3


int nums[10][NUM_ROWS][NUM_COLS] = {
    // Number 0
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 1
    {
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}},
    // Number 2
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}},
    // Number 3
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 4
    {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}},
    // Number 5
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 6
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 7
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}},
    // Number 8
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 9
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}}};


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TILE_SIZE 32

#define MAX_PIPES 10
#define SPEED 2


int speed = 5;
int char_pos[2] = {100, 100};

int draw_x[SCREEN_WIDTH] = {};
int draw_y[SCREEN_HEIGHT] = {};


typedef struct {
    int x, y; // Player position
    int speed; // Player movement speed
} Player;

typedef struct {
    int tiles[SCREEN_HEIGHT / TILE_SIZE][SCREEN_WIDTH / TILE_SIZE]; // 2D array to store tile data
} Level;


typedef struct {
    int x, y, x1, y1, x2, y2, x3, y3;
    int speed;
    int pipe_type;
} Pipe;

Pipe pipes[MAX_PIPES] = {};

// Function to check if a struct is empty
int isPipeEmpty(Pipe p) {
    return (p.x == 0 && p.y == 0 && p.x1 == 0 && p.y1 == 0 && p.speed == 0 && p.pipe_type == 0);
}

struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool quit;
} state;

//player initalization
Player player1;

#define PIPE_WIDTH 60
#define PIPE_HEIGHT 100
#define DIST 90

int score = 0;

Pipe set_new_pipes(Pipe p, int pos) {
    int random_number = rand();
    //printf("%d\n", random_number);
    int random_l = random_number % (SCREEN_HEIGHT - 2 * PIPE_HEIGHT - DIST) + DIST;
    p.x = pos;
    p.y = 0;
    p.x1 = p.x + PIPE_WIDTH;
    p.y1 = random_l;

    p.x2 = pos;
    p.y2 = random_l + DIST;
    p.x3 = p.x + PIPE_WIDTH;
    p.y3 = SCREEN_HEIGHT;

    return p;
}

void init(){
    //x, y
    player1.x = SCREEN_WIDTH/2;
    player1.y = SCREEN_HEIGHT/2;

    player1.speed = 50;

    int i;
    int start_pos[10] = { 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200 };


    for (i = 0; i < MAX_PIPES; i++){
        Pipe p;
        pipes[i] = set_new_pipes(p, start_pos[i]);
    }
}

void drawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(state.renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(state.renderer, x, y);
}

void handleKeyPress(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
            printf("Up arrow key pressed\n");
            //char_pos[1] = char_pos[1] - speed;
            player1.y -= player1.speed;
            break;
        //case SDLK_DOWN:
        //    printf("Down arrow key pressed\n");
        //    //char_pos[1] = char_pos[1] + speed;
        //    player1.y += player1.speed;
        //    break;
        //case SDLK_LEFT:init()sed\n");
        //    //char_pos[0] = char_pos[0] + speed;
        //    break;
        case SDLK_ESCAPE:
            state.quit = true;
            break;
        }
    }
}

void draw_rect(int x, int y, int x1, int y1, Uint8 r, Uint8 g, Uint8 b)
{
    // Ensure the coordinates are within the screen boundaries
    x = (x < 0) ? 0 : x;
    y = (y < 0) ? 0 : y;
    x1 = (x1 >= SCREEN_WIDTH) ? SCREEN_WIDTH - 1 : x1;
    y1 = (y1 >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : y1;

    // Draw the rectangle within the updated boundaries
    for (int i = x; i <= x1; i++)
    {
        for (int z = y; z <= y1; z++)
        {
            drawPixel(i, z, r, g, b);
        }
    }
}


void clear_area(int x, int y, int width, int height) {
    // Set the render color to the background color (black)
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // Fill the specified area with the background color
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(state.renderer, &rect);
}

void draw_digit(int digit, int x, int y) {
    // Draw the given digit at the specified position (x, y)
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (nums[digit][i][j] == 1) {
                // Calculate coordinates for the pixel
                int px = x + j * RECT_SIZE;
                int py = y + i * RECT_SIZE;
                // Draw the enlarged rectangle
                draw_rect(px, py, px + RECT_SIZE - 1, py + RECT_SIZE - 1, 255, 255, 255);
            }
        }
    }
}

void render_nums(int num, int x, int y) {
    // Calculate the maximum possible width for the numbers to clear
    int numDigits = 0;
    int temp = num;
    while (temp != 0) {
        temp /= 10;
        numDigits++;
    }
    if (numDigits == 0) {
        numDigits = 1; // If num is 0, it still has one digit
    }
    int max_width = numDigits * DIGIT_WIDTH * RECT_SIZE;

    // Clear the area where numbers will be rendered
    clear_area(x - max_width / 2, y, max_width, NUM_ROWS * RECT_SIZE);

    // Store digits in an array
    int digits[MAX_DIGITS] = {0}; // Initialize array with 0s
    temp = num;
    int i = MAX_DIGITS - 1; // Start from the end of the array
    while (temp != 0 && i >= 0) {
        digits[i] = temp % 10; // Store the last digit in the array
        temp /= 10; // Remove the last digit from the number
        i--; // Move to the next position in the array
    }

    // Calculate initial x position
    int xPos = x - DIGIT_WIDTH * RECT_SIZE * numDigits / 2;

    // Render each digit
    for (int u = MAX_DIGITS - numDigits; u < MAX_DIGITS; u++) {
        draw_digit(digits[u], xPos, y);
        // Update x position for the next digit
        xPos += DIGIT_WIDTH * RECT_SIZE;
    }
}


void draw_char()
{
    int x = char_pos[0];
    int y = char_pos[1];
    int i;
    draw_rect(x, y, x + 5, y + 5, 255, 0, 0);
}

void render_player(){
    int x = player1.x; // Use player1.x to access the player's x position
    int y = player1.y; // Use player1.y to access the player's y position

    if (x > SCREEN_WIDTH){
        player1.x -= player1.x - SCREEN_WIDTH;
    }
    if (x < 0){
        player1.x = 0;
    }
    if (y > SCREEN_HEIGHT){
        player1.y -= player1.y - SCREEN_HEIGHT;
    }
    if (y < 0){
        player1.y = 0;
    }
    //printf("X: %d Y: %d\n",x, y);
    draw_rect(x, y, x + 10, y + 10, 0, 255, 0);
}

void check_col(int){
    int x = player1.x; // Use player1.x to access the player's x position
    int y = player1.y; // Use player1.y to access the player's y position


    
}

void render_pipes(){
    for(int i = 0; i < MAX_PIPES; i++){
        int x = pipes[i].x;
        int x1 = pipes[i].x1;
        int y = pipes[i].y;
        int y1 = pipes[i].y1;
        int x2 = pipes[i].x2;
        int x3 = pipes[i].x3;
        int y2 = pipes[i].y2;
        int y3 = pipes[i].y3;

        if (x + PIPE_WIDTH < 0){
            Pipe p;
            int prev_x = pipes[(i == 0) ? MAX_PIPES - 1 : i - 1].x; // Get the x-coordinate of the previous pipe
            int random_number = prev_x + rand() % (150 - 100 + 1) + 100; // Adjust the range here
            printf("%d\n", random_number);
            int size1 = random_number - (prev_x + PIPE_WIDTH);
            if (size1 < 200){
                random_number += 50;
            }
            pipes[i] = set_new_pipes(p, random_number);
            score = score + 1;

        }

        bool isCollision = false;

        // Top pipe collision check
        if (player1.x + 10 >= x && player1.x <= x2 && player1.y + 10 >= y && player1.y <= y1) {
            isCollision = true;
        }
        // Bottom pipe collision check
        if (player1.x + 10 >= x && player1.x <= x2 && player1.y + 10 >= y2 && player1.y <= y3) {
            isCollision = true;
        }

        

        if (isCollision) {
            printf("Collision detected!\n");

            SDL_DestroyRenderer(state.renderer);
            SDL_DestroyWindow(state.window);
            SDL_Quit();
        }  

        draw_rect(x, y, x1, y1, 255, 0, 0);
        draw_rect(x2, y2, x3, y3, 255, 0, 0);

        pipes[i].x -= SPEED;
        pipes[i].x1 -= SPEED;
        pipes[i].x2 -= SPEED;
        pipes[i].x3 -= SPEED;
    }
}





void render()
{
    // Clear the screen
    SDL_SetRenderDrawColor(state.renderer, 115, 206, 225, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state.renderer);


    render_player();


    render_pipes();
    
    player1.y += 2;

    

    render_nums(score, 70, 10);
    // Update the screen
    SDL_RenderPresent(state.renderer);

}


double floor(double x) {
    if (x >= 0.0) {
        return (double)((int)x);
    } else {
        double int_part = (double)((int)x);
        return (int_part == x) ? int_part : int_part - 1.0;
    }
}



int main(int argc, char *argv[])
{
    srand(time(NULL));
    init();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window and renderer
    state.window = SDL_CreateWindow("Fun Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state.window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit(); // Clean up before exiting
        return 1;
    }
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);
    if (state.renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(state.window); // Clean up before exiting
        SDL_Quit(); // Clean up before exiting
        return 1;
    }
    //pipes[i] = set_new_pipes(pipes[i], 40);
    //pipes[i]1 = set_new_pipes(pipes[i]1, 200);

    bool running = true;
    while (running) {
        Uint64 start = SDL_GetPerformanceCounter();

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                state.quit = true;
                running = false; // Set running to false to exit the loop
            }
            handleKeyPress(&event);
        }

        // Game logic and rendering
        render();

        // Calculate elapsed time since the frame started
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // Cap to 60 FPS
        SDL_Delay(floor(16.666f - elapsedMS));
    }

    // Clean up and exit
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return 0;
}
