#ifndef GAME_CLASS_H
#define GAME_CLASS_H

enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
};

class Game
{
    public:
        // Game state
        GameState    State;
        bool         Keys[1024];
        unsigned int Width, Height;
        // Constructor
        Game(unsigned int width, unsigned int height);
        // Deconstructor
        ~Game();
        // Initialize game state
        void Init();
        // Game loop
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
};

#endif