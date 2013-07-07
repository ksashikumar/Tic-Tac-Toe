#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

const int    SCREEN_WIDTH  = 640;
const int    SCREEN_HEIGHT = 480;
const int    SCREEN_BPP    = 32;

static   SDL_Surface  *screen = NULL;
static   SDL_Surface  *board  = NULL;
static   SDL_Surface  *symbol = NULL;

static   SDL_Event     event;
static   SDL_Rect      clips[2];

static   int           check[9];

static   int           return_pos (int x, int y);
static   SDL_Surface  *load_image(std::string filename);
static   void          apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
static   bool          load_files();
static   void          set_clips();
static   bool          ttt_init();

class Game 
{
  public:

	SDL_Rect box[9];

  UI_ttt();
  
  void handle_events();

  void update_display();

};

