
#include <stdio.h>
#include <string.h>
#include <math.h>


#include <ft2build.h>
//#include <freetype.h>
#include "include/freetype.h"

#define WIDTH   640
#define HEIGHT  480


unsigned char image[HEIGHT][WIDTH];


void
draw_bitmap( FT_Bitmap*  bitmap,
             FT_Int      x,
             FT_Int      y)
{
  FT_Int  i, j, p, q;
  FT_Int  x_max = x + bitmap->width;
  FT_Int  y_max = y + bitmap->rows;


  for ( i = x, p = 0; i < x_max; i++, p++ )
  {
    for ( j = y, q = 0; j < y_max; j++, q++ )
    {
      if ( i < 0      || j < 0       ||
           i >= WIDTH || j >= HEIGHT )
        continue;

      image[j][i] |= bitmap->buffer[q * bitmap->width + p];
    }
  }
}


void show_image( void )
{
  int  i, j;


  for ( i = 0; i < HEIGHT; i++ )
  {
    for ( j = 0; j < WIDTH; j++ )
      putchar( image[i][j] == 0 ? '`'
                                : image[i][j] < 128 ? '+'
                                                    : '*' );
    putchar( '\n' );
  }
}

int main( int     argc,
      char**  argv){
  FT_Library    library;
  FT_Face       face;

  FT_GlyphSlot  slot;
  FT_Matrix     matrix;                 // transformation matrix
  FT_Vector     pen;                    // untransformed origin
  FT_Error      error;

  char*         filename;
  char*         text;

  double        angle;
  int           target_height;
  int           n, num_chars;


  //filename      = argv[1];                           // first argument
  //text          = argv[2];                           // second argument

  filename = (char*)"c:/windows/fonts/arial.ttf";
  text = (char*)"GZE Embed FreeType!";


  num_chars     = strlen( text );
  angle         = ( 25.0 / 360 ) * 3.14159 * 2;      // use 25 degrees
  target_height = HEIGHT;

  error = FT_Init_FreeType( &library );              // initialize library
  // error handling omitted

  error = FT_New_Face( library, filename, 0, &face );// create face object
  // error handling omitted

  // use 50pt at 100dpi
  error = FT_Set_Char_Size( face, 50 * 64, 0,
                            100, 0 );                //set character size
  // error handling omitted

  slot = face->glyph;

  //set up matrix
  matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
  matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
  matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
  matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

  // the pen position in 26.6 cartesian space coordinates;
  // start at (300,200) relative to the upper left corner
  pen.x = 30 * 64;
  pen.y = ( target_height - 200 ) * 64 - 12000;

  for ( n = 0; n < num_chars; n++ )
  {
    // set transformation
    FT_Set_Transform( face, &matrix, &pen );

    //load glyph image into the slot (erase previous one)
    error = FT_Load_Char( face, text[n], FT_LOAD_RENDER );
    if ( error )
      continue;                 // ignore errors

    //now, draw to our target surface (convert position)
    draw_bitmap( &slot->bitmap,
                 slot->bitmap_left,
                 target_height - slot->bitmap_top );

    // increment pen position
    pen.x += slot->advance.x;
    pen.y += slot->advance.y;
  }

  show_image();

  FT_Done_Face    ( face );
  FT_Done_FreeType( library );

  return 0;
}




/*

//#include "src/raster/ftraster.c"
#include <fstream>

// Define an acorn-like shape to test with.
struct Vec2
{
  Vec2(float a, float b) : x(a), y(b) { }

  float x, y;
};

static Vec2 k_shape[] =
{ Vec2(-3, -18), Vec2(0, -12), Vec2(6, -10), Vec2(12, -6), Vec2(12, -4),
  Vec2(11, -4), Vec2(10, -5), Vec2(20, 1), Vec2(9, 6), Vec2(7, 10),
  Vec2(5, 12), Vec2(4, 15), Vec2(3, 14), Vec2(1, 13), Vec2(-1, 13),
  Vec2(-5, 11), Vec2(-8, 8), Vec2(-11, 2), Vec2(-11, -2), Vec2(-14, 0),
  Vec2(-14, -2), Vec2(-11, -7), Vec2(-9, -9), Vec2(-8, -9), Vec2(-5, -12),
  Vec2(-5, -14), Vec2(-7, -15), Vec2(-8, -14), Vec2(-9, -15), Vec2(-9, -17),
  Vec2(-7, -17), Vec2(-6, -18)
};

void*
MY_Alloc_Func(FT_Memory memory,
              long size)
{
  return malloc(size);
}

void
MY_Free_Func(FT_Memory memory,
             void *block)
{
  free(block);
}

void*
MY_Realloc_Func(FT_Memory memory,
                long cur_size,
                long new_size,
                void* block)
{
  return realloc(block, new_size);
}



FT_Memory mem;
// Render a shape and dump it out as out-mono.pbm (b/w) and
// out-gray.pgm (grayscale).
int
main()
{
  // Set up the memory management.
  mem = new FT_MemoryRec_;
  mem->alloc = MY_Alloc_Func;
  mem->free = MY_Free_Func;
  mem->realloc = MY_Realloc_Func;


  // Build an outline manually.
  FT_Outline_ outline;
  outline.n_contours = 1;
  outline.n_points = sizeof (k_shape) / sizeof (Vec2);
  outline.points = new FT_Vector[outline.n_points];
  for (int i = 0; i < outline.n_points; ++i)
  {
    FT_Vector v;
    // Offset it to fit in the image and scale it up 10 times.
    v.x = (20 + k_shape[i].x) * 10 * 64;
    v.y = (20 + k_shape[i].y) * 10 * 64;
    outline.points[i] = v;
  }
  outline.tags = new char[outline.n_points];
  for (int i = 0; i < outline.n_points; ++i)
    outline.tags[i] = 1;
  outline.contours = new short[outline.n_contours];
  outline.contours[0] = outline.n_points - 1;
  outline.flags = 0;


  const int width = 500;
  const int rows = 400;

  // 1 bit per pixel.
  const int pitch_mono = (width + 7) >> 3;
  // 8 bits per pixel; must be a multiple of four.
  const int pitch_gray = (width + 3) & -4;


  FT_Bitmap bmp;
  FT_Raster raster;
  FT_Raster_Params params;


  // Allocate a chunk of memory for the render pool.
  const int kRenderPoolSize = 1024 * 1024;
  unsigned char *renderPool = new unsigned char[kRenderPoolSize];


  // Set up a bitmap.
  bmp.buffer = new unsigned char[rows * pitch_mono];
  memset(bmp.buffer, 0, rows * pitch_mono);
  bmp.width = width;
  bmp.rows = rows;
  bmp.pitch = pitch_mono;
  bmp.pixel_mode = FT_PIXEL_MODE_MONO;

  // Set up the necessary raster parameters.
  memset(&params, 0, sizeof (params));
  params.source = &outline;
  params.target = &bmp;

  // Initialize the rasterer and get it to render into the bitmap.
  ft_standard_raster.raster_new(mem, &raster);
  ft_standard_raster.raster_reset(raster, renderPool, kRenderPoolSize);
  ft_standard_raster.raster_render(raster, &params);

  // Dump out the raw image data (in PBM format).
  std::ofstream out_mono("out-mono.pbm", std::ios::binary);
  out_mono << "P4 " << width << " " << rows << "\n";
  out_mono.write((const char *)bmp.buffer, rows * pitch_mono);

  delete[] bmp.buffer;


  // Set up a pixmap.
  bmp.buffer = new unsigned char[rows * pitch_gray];
  memset(bmp.buffer, 0, rows * pitch_gray);
  bmp.width = width;
  bmp.rows = rows;
  bmp.pitch = pitch_gray;
  bmp.pixel_mode = FT_PIXEL_MODE_GRAY;
  bmp.num_grays = 16;

  // Set up the necessary raster parameters.
  memset(&params, 0, sizeof (params));
  params.source = &outline;
  params.target = &bmp;
  params.flags = FT_RASTER_FLAG_AA;

  // Initialize the rasterer and get it to render into the pixmap.
  ft_standard_raster.raster_new(mem, &raster);
  ft_standard_raster.raster_reset(raster, renderPool, kRenderPoolSize);
  ft_standard_raster.raster_render(raster, &params);

  // Dump out the raw image data (in PBM format).
  std::ofstream out_gray("out-gray.pgm", std::ios::binary);
  out_gray << "P5 " << width << " " << rows << " 255\n";
  out_gray.write((const char *)bmp.buffer, rows * pitch_gray);


  // Cleanup.
  delete[] renderPool;
  delete[] bmp.buffer;
  delete[] outline.points;
  delete[] outline.tags;
  delete[] outline.contours;
  delete mem;

  return 0;
}*/

/*
//#include "src\gxvalid\gxvalid.c"To rem
#include "src\gxvalid\gxvbsln.c"
#include "src\gxvalid\gxvcommn.c"
//#include "src\gxvalid\gxvfeat.c"
#include "src\gxvalid\gxvfgen.c"
#include "src\gxvalid\gxvjust.c"
#include "src\gxvalid\gxvkern.c"
#include "src\gxvalid\gxvlcar.c"
#include "src\gxvalid\gxvmod.c"
#include "src\gxvalid\gxvmort.c"
#include "src\gxvalid\gxvmort0.c"
#include "src\gxvalid\gxvmort1.c"
#include "src\gxvalid\gxvmort2.c"
#include "src\gxvalid\gxvmort4.c"
#include "src\gxvalid\gxvmort5.c"
#include "src\gxvalid\gxvmorx.c"
#include "src\gxvalid\gxvmorx0.c"
#include "src\gxvalid\gxvmorx1.c"
#include "src\gxvalid\gxvmorx2.c"
#include "src\gxvalid\gxvmorx4.c"
#include "src\gxvalid\gxvmorx5.c"
#include "src\gxvalid\gxvopbd.c"
#include "src\gxvalid\gxvprop.c"
#include "src\gxvalid\gxvtrak.c"
*/
