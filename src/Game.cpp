//
// Created by yot on 23/02/23.
//

#include "Game.h"

bool Game::Initialize()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << std::endl;
        return false;
    }

    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
        return false;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    //Create window
    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set logical size of renderer
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Set the scale mode to preserve aspect ratio
    SDL_RenderSetScale(renderer, (float)SDL_GetWindowSurface(window)->w / SCREEN_WIDTH, (float)SDL_GetWindowSurface(window)->h / SCREEN_HEIGHT);

    // Load config
    ConfigHelper::getInstance().Initialize();

    // Load config data
    bestScore = ConfigHelper::getInstance().GetBestScore();
    PIPE_GAP = ConfigHelper::getInstance().GetPipeGap();
    PIPE_WIDTH = ConfigHelper::getInstance().GetPipeWidth();
    PIPE_SPEED = ConfigHelper::getInstance().GetPipeSpeed();

    // Initialize inputs
    InputHandler::getInstance().Initialize();

    // Load font
    font = TTF_OpenFont("Assets/OpenSans-Regular.ttf", 60);

    if (font == NULL)
    {
        std::cout << TTF_GetError() << std::endl;
    }

    // Load ground/background/pipes textures
    bgSurface = IMG_Load("Assets/background.png");
    bg = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    groundSurface = IMG_Load("Assets/ground.png");
    ground = SDL_CreateTextureFromSurface(renderer, groundSurface);
    SDL_FreeSurface(groundSurface);
    pipeSurface = IMG_Load("Assets/pipe.png");
    pipeT = SDL_CreateTextureFromSurface(renderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);

    // randomness for pipes
    srand((unsigned) time(NULL));

    // Generate 10 pipes before
    for (int i = 0; i < 10; i++) {
        int topHeight = rand() % (800 - PIPE_GAP);
        int bottomHeight = SCREEN_HEIGHT - PIPE_GAP - topHeight;
        int x = SCREEN_WIDTH + i * (PIPE_WIDTH + PIPE_GAP) + 40;
        pipes.emplace_back(SCREEN_HEIGHT, PIPE_GAP, PIPE_WIDTH, x);
    }

    bird.LoadFromJson();

    return true;
}

void Game::Update()
{
    while (SDL_PollEvent(&event)) {
        // Handle quit event
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

    }

    if (bird.GetRect()->y > SCREEN_HEIGHT - bird.GetRect()->h - 102) {
        bird.Dead();
    }

    if (bird.GetRect()->y < -100) {
        bird.Dead();
    }

    //reset
    if (InputHandler::getInstance().isKeyPressed(SDL_SCANCODE_R)){
        pipes.clear();
        bird.Reset();
        score = 0;
        // Generate 10 pipes before
        for (int i = 0; i < 10; i++) {
            int topHeight = rand() % (800 - PIPE_GAP);
            int bottomHeight = SCREEN_HEIGHT - PIPE_GAP - topHeight;
            int x = SCREEN_WIDTH + i * (PIPE_WIDTH + PIPE_GAP) + 40;
            pipes.emplace_back(SCREEN_HEIGHT, PIPE_GAP, PIPE_WIDTH, x);
        }
    }

    if (!bird.IsDead()) {
        // Move the pipes across the screen
        for (auto & pipe : pipes) {
            pipe.move(PIPE_SPEED);

            // Check collisions with pipes
            if (!bird.IsGodMode())
            {
                if (SDL_HasIntersection(pipe.getTopRect(), bird.GetRect())) {
                    bird.Dead();
                }
                if (SDL_HasIntersection(pipe.getBottomRect(), bird.GetRect())) {
                    bird.Dead();
                }
            }

            // Check if bird has passed pipe
            if (!pipe.isPassed() && bird.GetRect()->x > pipe.getTopRect()->x + PIPE_WIDTH) {
                pipe.setPassed(true);
                score += 1; // Add one point to score
            }

        }
    }

    // Reset isScored flag when the bird moves past the pipe
    if (isScored && bird.GetRect()->x > pipes[0].getTopRect()->x + PIPE_WIDTH + 10) {
        isScored = false;
    }

    // Remove pipes that have gone off the screen
    while (!pipes.empty() && pipes[0].getTopRect()->x + PIPE_WIDTH < 0) {
        pipes.erase(pipes.begin());

        if (!pipes.empty()) {
            Pipe lastPipe = pipes.back();
            int newX = lastPipe.getTopRect()->x + 260;
            Pipe newPipe(SCREEN_HEIGHT, PIPE_GAP, PIPE_WIDTH, newX);
            pipes.push_back(newPipe);
        }

    }

    bird.Update();

    if (score > bestScore)
        bestScore = score;



    // Update key states
    InputHandler::getInstance().updateKeyStates();

    // Increment the frame count
    frameCount++;
}

void Game::Draw()
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color White = { 255, 255, 255 };

    // Draw background
    SDL_RenderCopy(renderer, bg, nullptr, nullptr);

    // Render the pipes
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (auto & pipe : pipes) {
        SDL_RenderCopyEx(renderer, pipeT, nullptr, pipe.getTopRect(), 0.0, nullptr, SDL_FLIP_VERTICAL);
        SDL_RenderCopyEx(renderer, pipeT, nullptr, pipe.getBottomRect(), 0.0, nullptr, SDL_FLIP_NONE);
    }

    // Draw ground
    SDL_Rect groundRect = { 0, SCREEN_HEIGHT - 100, 168*3, 56*3 };
    SDL_RenderCopy(renderer, ground, nullptr, &groundRect);

    bird.Draw(renderer);

    int textWidth, textHeight;
    TTF_SizeText(font, std::to_string(score).c_str(), &textWidth, &textHeight);

    TTFManager::getInstance().WriteText(renderer, font, 60, std::to_string(score), White, SCREEN_WIDTH/2-textWidth, 70);

    std::string text = "Best Score: ";
    text += std::to_string(bestScore);
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    TTFManager::getInstance().WriteText(renderer, font, 40, text, White, SCREEN_WIDTH-textWidth, 10);

    if (bird.IsDead())
    {
        text = "Press R to restart";
        TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
        TTFManager::getInstance().WriteText(renderer, font, 40, text, White, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT/2 - textHeight);
    }

    // Render the screen
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{

    // Save best score
    ConfigHelper::getInstance().SetBestScore(bestScore);
    ConfigHelper::getInstance().SaveJson();

    //Destroy window/renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}
