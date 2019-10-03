#pragma once

class MouseController {
 public:
  // Initializes internal variables
  MouseController();

  // Sets top left position
  void setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
  }

  // Handles mouse event
  void handleEvent(SDL_Event *e);

  // Shows button sprite
  void render();

 private:
  // Top left position
  SDL_Point mPosition;

  // Currently used global sprite
  MouseControllerSprite mCurrentSprite;
};