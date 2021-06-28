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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
//#include "Include/Weigl.h"

/*ElieWWW Includes and libs*/

#include "include/debug.h"
//#include "include/HTMLParser.hpp"
//#include "include/doc.hpp"
#include "include/CpcSdk.h"


sg_pass_action pass_action;

#define FONT_WEIGL (1)
#define FONT_Z1013 (2)

void init(void) {
    //DEBUG->Log("Welcome to ElieWWW"); 
    printf("Welcome to ElieWWW\n");
    
    sg_desc desc = { };
    desc.context = sapp_sgcontext();
    sg_setup(&desc);
    __dbgui_setup(sapp_sample_count());

    pass_action.colors[0].action = SG_ACTION_CLEAR;
    pass_action.colors[0].val[0] = 1.0f;
    pass_action.colors[0].val[1] = 1.0f;
    pass_action.colors[0].val[2] = 1.0f;
    pass_action.colors[0].val[3] = 0.5f;

    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    //render();
    sg_end_pass();
    sg_commit();

    sdtx_desc_t sdtx_desc = {};

    sdtx_desc.fonts[FONT_Z1013] = sdtx_font_z1013();
    //sdtx_desc.fonts[FONT_WEIGL] = _elie_font_Weigl();
    sdtx_setup(&sdtx_desc);

}


static void frame(void) {

    // set virtual canvas size to half display size so that
    // glyphs are 16x16 display pixels
    sdtx_canvas(sapp_width()*0.5f, sapp_height()*0.5f);
    sdtx_origin(0.0f, 0.0f);
    sdtx_home();
    sdtx_font(2);
    sdtx_color3b(51, 51, 51); // Rouge, Vert, Bleu
    //sdtx_puts("Welcome to ElieWWW, E-Mode for Cpcdos OSx");

    FILE* html = std::fopen("files/test.html", "rb");

   if (html != NULL){
       printf("File loaded\n");
       char buffer[800000];
             fread(buffer,sizeof(buffer),1,html);
             sdtx_printf(buffer);

             //ElieWWWHTMLParser parser;
             //ElieDoc doc;
             
            // parser.HTMLParser();
             // parser.build_doc_from_string(html);
             //doc.Elie_Doc();
            
             // cpc_eval("/F:ELIE.MSGBOX(Hello!!!!,ElieOS,1,0)");
    }else{
		 sdtx_printf("Error Loading File test.html");
	}
      

    fclose (html);
    //  free (buffer);
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