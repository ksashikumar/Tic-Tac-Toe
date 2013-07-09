#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>

const int    SCREEN_WIDTH  = 640;
const int    SCREEN_HEIGHT = 480;
const int    SCREEN_BPP    = 32;

const char  *game_name     = "Tic Tac Toe"; 
const char  *home_name     = "home.png";
const char  *board_name    = "board.png";
const char  *symbol_name   = "symbol.png";

SDL_Surface  *screen = NULL;
SDL_Surface  *home   = NULL;
SDL_Surface  *board  = NULL;
SDL_Surface  *symbol = NULL;

SDL_Event     event;
SDL_Rect      clips[2];

int           check[9];

bool          ttt_init       (void);
bool          load_files     (void);
SDL_Surface  *load_image     (std::string filename);
void          apply_surface  (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
int           return_pos     (int x, int y);
void          set_clips      (void);

class Game 
{

  public:

  SDL_Rect   box[9];
  bool       check_home;

  Game();

  void render_home_screen();

  bool handle_home_event();

  void render_board();
  
  void handle_game_event();

  void update_display();

};



bool 
ttt_init (void)
{

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return false;

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

  if(screen == NULL)
      return false;

  SDL_WM_SetCaption(game_name, NULL);

  for(int i = 0; i < 9; i++)
    check[i] = -1;

  return true;

}


bool 
load_files (void)
{

  home   = load_image(home_name);
  board  = load_image(board_name);
  symbol = load_image(symbol_name);

  if(home == NULL || board == NULL || symbol == NULL)
    return false;

  return true;

}


SDL_Surface* 
load_image (std::string filename)
{

  SDL_Surface* loadedImage = NULL;

  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load( filename.c_str() );

  if(loadedImage != NULL)
    {
      optimizedImage = SDL_DisplayFormat(loadedImage);

      SDL_FreeSurface(loadedImage);

      if(optimizedImage != NULL)
        SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
    }

  return optimizedImage;

}


void 
apply_surface (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{

  SDL_Rect offset;

  offset.x = x;
  offset.y = y;

  SDL_BlitSurface(source, clip, destination, &offset);

}


int
return_pos (int x, int y)
{


}


void
set_clips (void)
{


}


Game::Game (void)
{
  check_home = true;
}


void Game::render_home_screen (void)
{

  apply_surface(0, 0, home, screen, NULL);
  
}


bool Game::handle_home_event (void)
{
  
  int i = 0, j = 0;
  int width = 290, height = 87;
  int x = 180, y1 = 180, y2 = 320;

  if(check_home)
    {
      if(event.type == SDL_MOUSEBUTTONDOWN)
        {
      
          if(event.button.button == SDL_BUTTON_LEFT)
            {
              i = event.button.x;
              j = event.button.y;
    
              if( (i > x) && (i < x + width) && (j > y1) && (j < y1 + height) )
                {
                  std::cout << "\nSINGLE PLAYER: Mouse Down\n";
                }
    
              if( (i > x) && (i < x + width) && (j > y2) && (j < y2 + height) )
                {
                  std::cout << "\nTWO PLAYER: Mouse Down\n";
                }
            }

        }

      if(event.type == SDL_MOUSEBUTTONUP)
        {

          if( event.button.button == SDL_BUTTON_LEFT )
            {
              i = event.button.x;
              j = event.button.y;
    
              if( (i > x) && (i < x + width) && (j > y1) && (j < y1 + height) )
                {
                  std::cout << "\nSINGLE PLAYER: Mouse Up\n";
                  check_home = false;
                  return true;
                }
  
              if( (i > x) && (i < x + width) && (j > y2) && (j < y2 + height) )
                {
                  std::cout << "\nTWO PLAYER: Mouse Up\n";
                  check_home = false;
                  return true;
                }
            }

        }
    }
  return false;
  
}


void Game::render_board (void)
{
  
  apply_surface(0, 0, board, screen, NULL);  

  handle_game_event();
  
}


void Game::handle_game_event (void)
{


}


void Game::update_display (void)
{


}



int main (int argc, char* args[])
{
  
  bool quit = false;

  if(ttt_init() == false)
    return 1;

  if(load_files() == false)
    return 1;

  Game obj;

  obj.render_home_screen(); 

  while( quit == false )
    {
     
      if(SDL_PollEvent(&event))
        {
          if(obj.handle_home_event())
            obj.render_board();

          if(event.type == SDL_QUIT)
            quit = true;
        }


      if(SDL_Flip(screen) == -1)
            return 1;
    }

  return 0;
}
