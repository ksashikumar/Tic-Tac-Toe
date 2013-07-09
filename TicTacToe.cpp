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
const char  *symbol_name1  = "symbol1.png";
const char  *symbol_name2  = "symbol2.png";

SDL_Surface  *screen  = NULL;
SDL_Surface  *home    = NULL;
SDL_Surface  *board   = NULL;
SDL_Surface  *symbol1 = NULL;
SDL_Surface  *symbol2 = NULL;

SDL_Event     event;

int           check[9];

bool          ttt_init       (void);
bool          load_files     (void);
SDL_Surface  *load_image     (std::string filename);
void          apply_surface  (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
int           return_pos     (int x, int y);

class Game 
{

  public:

  SDL_Rect   box[9];
  bool       check_home;

  Game();

  void display_home_screen();

  void handle_home_event();

  void display_board();
  
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

  home    = load_image(home_name);
  board   = load_image(board_name);
  symbol1 = load_image(symbol_name1);
  symbol2 = load_image(symbol_name2);


  if(home == NULL || board == NULL || symbol1 == NULL || symbol2 == NULL)
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



Game::Game (void)
{
  check_home = true;
}


void Game::display_home_screen (void)
{

  apply_surface(0, 0, home, screen, NULL);
  
}


void Game::handle_home_event (void)
{
  
  int i = 0, j = 0;
  int width = 290, height = 87;
  int x = 180, y1 = 180, y2 = 320;

  if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      i = event.button.x;
      j = event.button.y;

      if( (i > x) && (i < x + width) && (j > y1) && (j < y1 + height) )
        {
          std::cout << "\nSINGLE PLAYER: Mouse Down\n";
          check_home = false;
        }
    
      if( (i > x) && (i < x + width) && (j > y2) && (j < y2 + height) )
        {
          std::cout << "\nTWO PLAYER: Mouse Down\n";
          check_home = false;
        }
    }

}


void Game::display_board (void)
{
  
  apply_surface(0, 0, board, screen, NULL);  
  handle_game_event();
  
}


void Game::handle_game_event (void)
{

  int i, j;
  int x1 = 0, x2 = 244, x3 = 420;  
  int y1 = 0, y2 = 174, y3 = 333;

  int width1 = 220, width2 = 150, height = 147;
  
  if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      i = event.button.x;
      j = event.button.y;
  
      if( (i > x1) && (i < x1 + width1) )
        {
          if( (j > y1) && (j < y1 + height) )
            std::cout << "\nCell 1: Mouse Down\n";
          if( (j > y2) && (j < y2 + height) )
            std::cout << "\nCell 4: Mouse Down\n";
          if( (j > y3) && (j < y3 + height) )
            std::cout << "\nCell 7: Mouse Down\n";              
        }

      if( (i > x2) && (i < x2 + width2) )
        {
          if( (j > y1) && (j < y1 + height) )
            std::cout << "\nCell 2: Mouse Down\n";
          if( (j > y2) && (j < y2 + height) )
            std::cout << "\nCell 5: Mouse Down\n";
          if( (j > y3) && (j < y3 + height) )
            std::cout << "\nCell 9: Mouse Down\n";              
        }

      if( (i > x3) && (i < x3 + width1) )
        {
          if( (j > y1) && (j < y1 + height) )
            std::cout << "\nCell 3: Mouse Down\n";
          if( (j > y2) && (j < y2 + height) )
            std::cout << "\nCell 6: Mouse Down\n";
          if( (j > y3) && (j < y3 + height) )
            std::cout << "\nCell 9: Mouse Down\n";              
        }

    }

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

  obj.display_home_screen(); 

  while ( SDL_WaitEvent(&event) >= 0 ) 
    {

      if(obj.check_home)
        obj.handle_home_event();
      else
        obj.display_board();            
    
      if(event.type == SDL_QUIT) 
        {
          std::cout << "\nQuit requested, quitting.\n";
          exit(0);
        }
      SDL_Flip(screen);
    }

  return 0;

}
