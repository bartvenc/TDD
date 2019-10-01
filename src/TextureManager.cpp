
#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
  SDL_Surface* tempSurface = IMG_Load(texture);
  // printf("LoadTexture(const char* texture): %s\n",texture);
  SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,
                          double angle,
                          SDL_RendererFlip flip) {  // printf("%s\n","tried to
                                                    // draw TextureManager " );
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, NULL, flip);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,
                          SDL_RendererFlip flip) {  // printf("%s\n","tried to
                                                    // draw TextureManager " );
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}