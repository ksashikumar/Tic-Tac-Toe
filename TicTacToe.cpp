#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>
#include <time.h>

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

int           check_cell[9];

bool          ttt_init       (void);
bool          load_files     (void);
SDL_Surface  *load_image     (std::string filename);
void          apply_surface  (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

class Game 
{

  public:

  bool       check_home;
  bool       check_player; /* true for single player */
  int        check_turn;
  int        current_cell;

  static const Sint16 x1 = 70, x2 = 244, x3 = 420;  
  static const Sint16 y1 = 0, y2 = 175, y3 = 335;

  static const Uint16 width1 = 220, width2 = 150, height = 135;

  Game();

  void display_home_screen();

  void handle_home_event();

  void display_board();

  void apply_symbol(int, int);

  void handle_game_event();

  int  check_game_result();
  
  int turn();

};



bool 
ttt_init (void)
{

  int i;
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return false;

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

  if(screen == NULL)
      return false;

  SDL_WM_SetCaption(game_name, NULL);

  for(i = 0; i < 9; i++)
    check_cell[i] = -1;

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


Game::Game (void)
{

  int t;
  check_home = true;
  srand(time(NULL));
  check_turn = rand()%2;

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
          check_player = true;
          check_home   = false;
        }
    
      if( (i > x) && (i < x + width) && (j > y2) && (j < y2 + height) )
        {
          std::cout << "\nTWO PLAYER: Mouse Down\n";
          check_player = false;
          check_home   = false;
        }
    }

}


void Game::display_board (void)
{
  int i;

  apply_surface(0, 0, board, screen, NULL);  

  if(current_cell != -1)
  {
    if((i = check_game_result()) == -1)
      handle_game_event();
    else
    {
      std::cout <<"\nPlayer:" << i << "wins!\n";
      exit(0);    
    }
  }
  else 
    handle_game_event();
  
}


void Game::apply_symbol (int flag, int check)
{

  SDL_Rect     rectangle;
  SDL_Surface *source = NULL;

  if(check == 0)
    source = symbol1;
  else if(check == 1) 
    source = symbol2;

  switch(flag)
    {
      case 0:  
        rectangle.x = x1;
        rectangle.y = y1;
        rectangle.w = width1;
        rectangle.h = height;
      break;
      
      case 1:               
        rectangle.x = x2;
        rectangle.y = y1;
        rectangle.w = width2;
        rectangle.h = height;
      break;

      case 2:               
        rectangle.x = x3;
        rectangle.y = y1;
        rectangle.w = width1;
        rectangle.h = height;
      break;

      case 3:               
        rectangle.x = x1;
        rectangle.y = y2;
        rectangle.w = width2;
        rectangle.h = height;
      break;

      case 4:               
        rectangle.x = x2;
        rectangle.y = y2;
        rectangle.w = width2;
        rectangle.h = height;
      break;

      case 5:               
        rectangle.x = x3;
        rectangle.y = y2;
        rectangle.w = width1;
        rectangle.h = height;
      break;

      case 6:               
        rectangle.x = x1;
        rectangle.y = y3;
        rectangle.w = width2;
        rectangle.h = height;
      break;

      case 7:               
        rectangle.x = x2;
        rectangle.y = y3;
        rectangle.w = width2;
        rectangle.h = height;
      break;

      case 8:               
        rectangle.x = x3;
        rectangle.y = y3;
        rectangle.w = width1;
        rectangle.h = height;
      break;
    }

  SDL_BlitSurface(source, NULL, board, &rectangle);


}


void Game::handle_game_event (void)
{

  int i, j;
  
  if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      i = event.button.x;
      j = event.button.y;
  
      if( (i > x1) && (i < x1 + width2) )
        {
          if( (j > y1) && (j < y1 + height) && (check_cell[0] == -1) )
            { 
              check_cell[0] = turn();
              current_cell  = 0;
              apply_symbol(0, check_cell[0]);
              std::cout << "\nCell 1: Mouse Down\n";
            }
          if( (j > y2) && (j < y2 + height) && (check_cell[3] == -1) )
            {
              check_cell[3] = turn();
              current_cell  = 3;
              apply_symbol(3, check_cell[3]);
              std::cout << "\nCell 4: Mouse Down\n";
            }
          if( (j > y3) && (j < y3 + height) && (check_cell[6] == -1) )
            {  
              check_cell[6] = turn();
              current_cell  = 6;
              apply_symbol(6, check_cell[6]);
              std::cout << "\nCell 7: Mouse Down\n";              
            }
        }

      if( (i > x2) && (i < x2 + width2) )
        {
          if( (j > y1) && (j < y1 + height) && (check_cell[1] == -1) )
            {
              check_cell[1] = turn();
              current_cell  = 1;
              apply_symbol(1, check_cell[1]);              
              std::cout << "\nCell 2: Mouse Down\n";
            }
          if( (j > y2) && (j < y2 + height) && (check_cell[4] == -1) )
            {
              check_cell[4] = turn();
              current_cell  = 4;
              apply_symbol(4, check_cell[4]);
              std::cout << "\nCell 5: Mouse Down\n";
            }
          if( (j > y3) && (j < y3 + height) && (check_cell[7] == -1) )
            {
              check_cell[7] = turn();
              current_cell  = 7;
              apply_symbol(7, check_cell[7]);
              std::cout << "\nCell 8: Mouse Down\n";
            }              
        }

      if( (i > x3) && (i < x3 + width1) )
        {
          if( (j > y1) && (j < y1 + height) && (check_cell[2] == -1) )
            {
              check_cell[2] = turn();
              current_cell  = 2;
              apply_symbol(2, check_cell[2]);
              std::cout << "\nCell 3: Mouse Down\n";
            }
          if( (j > y2) && (j < y2 + height) && (check_cell[5] == -1) )
            {
              check_cell[5] = turn();
              current_cell  = 5;
              apply_symbol(5, check_cell[5]);
              std::cout << "\nCell 6: Mouse Down\n";
            }
          if( (j > y3) && (j < y3 + height) && (check_cell[8] == -1) )
            {
              check_cell[8] = turn();
              current_cell  = 8;
              apply_symbol(8, check_cell[8]);        
              std::cout << "\nCell 9: Mouse Down\n";
            }              
        }

    }

}

int Game::check_game_result (void)
{

  int i, j;
  int ref_row, ref_col;
  int flag   = -1;

  if((current_cell >= 0) && (current_cell <= 2)) 
    ref_row = 0;

  else if((current_cell >= 3) && (current_cell <= 5))
    ref_row = 3;

  else if((current_cell >= 6) && (current_cell <= 8))
    ref_row = 6;

  for(i = 0; i < 3; i++)
  {
    if((current_cell == i) || (current_cell == (i+3)) || (current_cell == (i+6)))
    {    
      ref_col = i;
      break;
    }
  }

  for(i = ref_row; i < ref_row + 2; i++)
  {
    if(check_cell[i] == check_cell[i+1])
      flag = check_cell[i];
    else
    {
      flag = -1;
      break;
    }
  }
  
  if(flag != -1)
    return flag;

  for(i = ref_col; i < ref_col + 4; i = i + 3)
  {
    if(check_cell[i] == check_cell[i+3])
      flag = check_cell[i];
    else
    {
      flag = -1;
      break;
    }
  }

  if(flag != -1)
    return flag;

  for(i = 0; i < 5; i = i + 4)
  {
    if(check_cell[i] == check_cell[i+4])
      flag = check_cell[i];
    else
    {
      flag = -1;
      break;
    }
  }

  if(flag != -1)
    return flag;

  for(i = 2; i < 5; i = i + 2)
  {
    if(check_cell[i] == check_cell[i+2])
      flag = check_cell[i];
    else
    {
      flag = -1;
      break;
    }
  }

  if(flag != -1)
    return flag;
      
  return flag;
    
}


int Game::turn (void)
{

  if(check_turn == 0)
    check_turn = 1;
  else if(check_turn == 1)
    check_turn = 0;

  return check_turn;

}



int main (int argc, char* args[])
{
  
  bool quit = false;

  if(ttt_init() == false)
    return 1;

  if(load_files() == false)
    return 1;

  Game obj;

  obj.current_cell = -1;

  obj.display_home_screen(); 

  while ( SDL_WaitEvent(&event) >= 0 ) 
    {

      if(obj.check_home)
        obj.handle_home_event();
      else
        obj.display_board();            
    
      if(event.type == SDL_QUIT) 
          exit(0);

      SDL_Flip(screen);
    }

  return 0;

}
