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

/*ElieWWW Includes and libs*/
#include "include/debug.h"


sg_pass_action pass_action;


void init(void) {
    //DEBUG->Log("Welcome to ElieWWW"); 
    printf("Welcome to ElieWWW\n");
    
    sg_desc desc = { };
    desc.context = sapp_sgcontext();
    sg_setup(&desc);


    pass_action.colors[0].action = SG_ACTION_CLEAR;
    pass_action.colors[0].val[0] = 0.0f;
    pass_action.colors[0].val[1] = 0.5f;
    pass_action.colors[0].val[2] = 0.7f;
    pass_action.colors[0].val[3] = 0.5f;

    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    //render();
    sg_end_pass();
    sg_commit();
 
}


void cleanup(void) {
    __dbgui_shutdown();
    sg_shutdown();
}


#include <stdio.h>

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    sapp_desc desc = { };
    desc.init_cb = init;
    //desc.frame_cb = frame;
    desc.cleanup_cb = cleanup;
    //desc.event_cb = input;
    desc.width = 600;
    desc.height = 480;
    desc.gl_force_gles2 = true;
    desc.window_title = "ElieWWW";
    desc.ios_keyboard_resizes_canvas = false;

    return desc;
}