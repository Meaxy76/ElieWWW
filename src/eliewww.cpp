/* 
 ElieWWW for Cpcdos OSx Beta 1.5
 We will try to open a html page from local 
 We will use Cpcdos Shell to download web page and load them in ElieWWW
  _____ _ _    __        ____        ____        __
 | ____| (_) __\ \      / /\ \      / /\ \      / /
 |  _| | | |/ _ \ \ /\ / /  \ \ /\ / /  \ \ /\ / / 
 | |___| | |  __/\ V  V /    \ V  V /    \ V  V /  
 |_____|_|_|\___| \_/\_/      \_/\_/      \_/\_/   
 */



#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


// Sokol Includes and defines
#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_NO_SSE
#include "Include/HandmadeMath.h"
#define SOKOL_GLCORE33
#define SOKOL_IMPL
#include "../Sokol/sokol_app.h"
#include "../Sokol/sokol_gfx.h"
#include "../Sokol/sokol_glue.h"
#include "../Lib/dbgui/dbgui.h"

#include "eliewww.glsl.h"
#define SOKOL_DEBUGTEXT_IMPL
#include "../Sokol/util/sokol_debugtext.h"
/*ElieWWW Includes and libs*/
#include "include/debug.h"


sg_pass_action pass_action;

#define FONT_KC853 (0)
#define FONT_KC854 (1)
#define FONT_Z1013 (2)
#define FONT_CPC   (3)
#define FONT_C64   (4)
#define FONT_ORIC  (5)




void init(void) {
    //DEBUG->Log("Welcome to ElieWWW"); 
    printf("Welcome to ElieWWW\n");
    
    sg_desc desc = { };
    desc.context = sapp_sgcontext();
    sg_setup(&desc);
__dbgui_setup(sapp_sample_count());
   pass_action.colors[0].action = SG_ACTION_CLEAR;
   pass_action.colors[0].val[0] = 0.0f;
   pass_action.colors[0].val[1] = 0.5f;
   pass_action.colors[0].val[2] = 0.7f;
   pass_action.colors[0].val[3] = 0.5f;

    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    //render();
    sg_end_pass();
    sg_commit();


    // setup sokol-debugtext
    // setup sokol-debugtext

sdtx_desc_t sdtx_desc = {};

sdtx_desc.fonts[FONT_Z1013] = sdtx_font_z1013();
sdtx_setup(&sdtx_desc);

}


static void print_font(int font_index, const char* title, uint8_t r, uint8_t g, uint8_t b) {
    sdtx_font(font_index);
    sdtx_color3b(r, g, b);
    sdtx_puts(title);
    for (int c = 32; c < 256; c++) {
        sdtx_putc(c);
        if (((c + 1) & 63) == 0) {
            sdtx_crlf();
        }
    }
    sdtx_crlf();
}

static void frame(void) {

    // set virtual canvas size to half display size so that
    // glyphs are 16x16 display pixels
    sdtx_canvas(sapp_width()*0.5f, sapp_height()*0.5f);
    sdtx_origin(0.0f, 2.0f);
    sdtx_home();
    print_font(FONT_Z1013, "Welcome to ElieWWW, E-Mode\n",       0x4c, 0xaf, 0x50);

    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    sdtx_draw();
    __dbgui_draw();
    sg_end_pass();
    sg_commit();
}



void cleanup(void) {
    sdtx_shutdown();
    __dbgui_shutdown();
    sg_shutdown();
}


#include <stdio.h>

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    sapp_desc desc = { };
    desc.init_cb = init;
    desc.frame_cb = frame;
    desc.cleanup_cb = cleanup;
    //desc.event_cb = input;
    desc.width = 600;
    desc.height = 480;
    desc.gl_force_gles2 = true;
    desc.window_title = "ElieWWW";
    desc.ios_keyboard_resizes_canvas = false;

    return desc;
}