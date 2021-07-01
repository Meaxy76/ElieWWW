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
#include "../Sokol/sokol_fetch.h"
#include "../Lib/dbgui/dbgui.h"

#include "eliewww.glsl.h"
//#include "loadpng-sapp.glsl.h"

#define SOKOL_DEBUGTEXT_IMPL
#include "../Sokol/util/sokol_debugtext.h"
//#include "Include/Weigl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Lib/stb/stb_image.h"
/*ElieWWW Includes and libs*/

#include "include/debug.h"
//#include "include/ElieHTMLParser.hpp"
//#include "include/doc.hpp"
#include "include/CpcSdk.h"
#include "Include/ElieHTMLParser.hpp"

#define SLOT_tex (0)
#define ATTR_vs_pos (0)
#define ATTR_vs_texcoord0 (1)

typedef struct {
    float x, y, z;
    int16_t u, v;
} vertex_t;


sg_pass_action pass_action;
uint8_t file_buffer[256 * 1024];
sg_bindings bind = {};
sg_pipeline pip;

#define FONT_WEIGL (1)
#define FONT_Z1013 (2)


static void fetch_callback(const sfetch_response_t*);


void init(void) {
    //DEBUG->Log("Welcome to ElieWWW"); 
    printf("Welcome to ElieWWW\n");

    
    sg_desc desc = { };
    desc.context = sapp_sgcontext();
    sg_setup(&desc);
    __dbgui_setup(sapp_sample_count());


    sfetch_desc_t okeydokey = {};
        okeydokey.max_requests = 1;
        okeydokey.num_channels = 1;
        okeydokey.num_lanes = 1;
    sfetch_setup(okeydokey);


    pass_action.colors[0].action = SG_ACTION_CLEAR;
    pass_action.colors[0].val[0] = 1.0f;
    pass_action.colors[0].val[1] = 1.0f;
    pass_action.colors[0].val[2] = 1.0f;
    pass_action.colors[0].val[3] = 0.5f;
   

    bind.fs_images[SLOT_tex] = sg_alloc_image(); 

        const vertex_t vertices[] = {
        /* pos                  uvs */
        { -1.0f, -1.0f, -1.0f,      0,     0 },
        {  1.0f, -1.0f, -1.0f,  32767,     0 },
        {  1.0f,  1.0f, -1.0f,  32767, 32767 },
        { -1.0f,  1.0f, -1.0f,      0, 32767 },

            };

            sg_buffer_desc ohmy = {};
    
        ohmy.size = sizeof(vertices);
        ohmy.content = vertices;
        ohmy.label = "face";
        bind.vertex_buffers[0] = sg_make_buffer(ohmy);

        /* a pipeline state object */

         sg_pipeline_desc letsgo = {};
    
         letsgo.shader = sg_make_shader(loadpng_shader_desc());

         letsgo.layout.attrs[ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT3;
         letsgo.layout.attrs[ATTR_vs_texcoord0].format = SG_VERTEXFORMAT_SHORT2N;

         letsgo.index_type = SG_INDEXTYPE_UINT16;

         letsgo.depth_stencil.depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL;
         letsgo.depth_stencil.depth_write_enabled = true;

         letsgo.rasterizer.cull_mode = SG_CULLMODE_BACK;

         letsgo.label = "cube-pipeline";
         pip = sg_make_pipeline(&letsgo );

      sfetch_request_t fetchernya = {};
          fetchernya.path = "files/nko.png";
          fetchernya.callback = fetch_callback;
          fetchernya.buffer_ptr = file_buffer;
          fetchernya.buffer_size = sizeof(file_buffer);
      sfetch_send(fetchernya);



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
    sfetch_dowork();
    // set virtual canvas size to half display size so that
    // glyphs are 16x16 display pixels
    sdtx_canvas(sapp_width()*0.5f, sapp_height()*0.5f);
    sdtx_origin(0.0f, 0.0f);
    sdtx_home();
    sdtx_font(2);
    sdtx_color3b(51, 51, 51); // Rouge, Vert, Bleu
    //sdtx_puts("Welcome to ElieWWW, E-Mode for Cpcdos OSx");

    FILE* html = std::fopen("files/test.html", "rb");

   // sfetch_send blabka; 
   


       
    //sfetch_send(&(sfetch_request_t){
      //  .path = "files/nko.png",
      //  .callback = fetch_callback,
      //  .buffer_ptr = file_buffer,
      //  .buffer_size = sizeof(file_buffer)
    //});

   if (html != NULL){
       printf("File loaded\n");
       char buffer[4096];
             fread(buffer,sizeof(buffer),1,html);
             //sdtx_printf(buffer);
            
            string test = (buffer);
             //sdtx_printf(test);
            // printf(test);
         
            test = HTMLReader(test);
            sdtx_printf( (test).c_str() );
            
            // cpc_eval("write/ /bin test.txt = ok");
    }else{
		 sdtx_printf("Error Loading File test.html");
	}
      

    fclose (html);
    //  free (buffer);
    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    sg_apply_bindings(&bind);
    sg_apply_pipeline(pip);
    sdtx_draw();
    __dbgui_draw();
    sg_end_pass();
    sg_commit();
}

static void fetch_callback(const sfetch_response_t* response) {

    
    if (response->fetched) {
        /* the file data has been fetched, since we provided a big-enough
           buffer we can be sure that all data has been loaded here
        */
        int png_width, png_height, num_channels;
        const int desired_channels = 4;
        stbi_uc* pixels = stbi_load_from_memory(
            (stbi_uc*)response->buffer_ptr,
            (int)response->fetched_size,
            &png_width, &png_height,
            &num_channels, desired_channels);
        if (pixels) {
            /* ok, time to actually initialize the sokol-gfx texture */
           
            sg_image_desc sg_img = {};
            sg_img.width = png_width;
            sg_img.height = png_height;
            sg_img.pixel_format = SG_PIXELFORMAT_RGBA8;
            sg_img.min_filter = SG_FILTER_LINEAR;
            sg_img.mag_filter = SG_FILTER_LINEAR;
            sg_img.content.subimage[0][0].ptr = pixels;
            sg_img.content.subimage[0][0].size = png_width * png_height * 4;

            sg_init_image(bind.fs_images[SLOT_tex], &sg_img);

            stbi_image_free(pixels);
        }
    }
    else if (response->failed) {
        // if loading the file failed, set clear color to red
       pass_action.colors[0].action = SG_ACTION_CLEAR;
       pass_action.colors[0].val[0] = 1.0f;
       pass_action.colors[0].val[1] = 0.0f;
       pass_action.colors[0].val[2] = 0.0f;
       pass_action.colors[0].val[3] = 1.0f;
    }
}

//GDB will automaticly break here (with Cwc compiler)
extern "C" void GDB_Func_Break(){}
extern "C" void GDB_Func_ExecuteCmds(){} 

void GDB_BreakAssert(){
    fprintf(stderr,"Cmd[GDB]:break _assert\n");
    fflush(stderr);
    GDB_Func_ExecuteCmds();
}


void cleanup(void) {
    sdtx_shutdown();
    sfetch_shutdown();
    __dbgui_shutdown();
    sg_shutdown();
}





sapp_desc sokol_main(int argc, char* argv[]) {

    GDB_BreakAssert();


    (void)argc; (void)argv;
    sapp_desc desc = { };
    desc.init_cb = init;
    desc.frame_cb = frame;
    desc.cleanup_cb = cleanup;
    //desc.event_cb = input;
    desc.width = 800;
    desc.height = 600;
    desc.gl_force_gles2 = true;
    desc.window_title = "ElieWWW";
    desc.ios_keyboard_resizes_canvas = false;

    return desc;
}