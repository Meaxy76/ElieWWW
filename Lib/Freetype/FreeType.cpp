//This file is part of "GZE - GroundZero Engine"

//The permisive licence allow to use GZE for free or commercial project (Apache License, Version 2.0).
//For conditions of distribution and use, see copyright notice in Licence.txt, this license must be included with any distribution of the code.

//Though not required by the license agreement, please consider the following will be greatly appreciated:
//- We would like to hear about projects where GZE is used.
//- Include an attribution statement somewhere in your project.
//- If you want to see GZE evolve please help us with a donation.


////////////////////////////////////////////////////////////
///////////// GZE Freetype v2.6  integration ///////////////
////////////////////////////////////////////////////////////

// This file will include all definition in one file,  reducing
// the final file size, lot of gain in compilation speed,
// simplifie compilation process and direct build macro configuration
//
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

#ifndef GZ_tNo_FreeType

////USER DEFINED OPTIONS///
#include "ftoption.h"
////////////////////////////

#include "include\config\ftconfig.h"
#include "include\fttypes.h"

#include "include\fterrors.h"

//#include "include\internal\internal.h"
#include "ft2build.h"

//#include "include\config\ftheader.h"
#undef FT_ERR_BASE
#include "src\base\ftcalc.c"
#undef FT_ERR_BASE
#include "src\base\ftglyph.c"
#undef FT_ERR_BASE
#include "src\base\basepic.c"
#undef FT_ERR_BASE
#include "src\base\ftadvanc.c"
#undef FT_ERR_BASE
#include "src\base\ftapi.c"

//#include "src\base\ftbase.c" //Group
#undef FT_ERR_BASE
#include "src\base\ftbbox.c"
#undef FT_ERR_BASE
#include "src\base\ftbdf.c"
#undef FT_ERR_BASE
#include "src\base\ftbitmap.c"
#undef FT_ERR_BASE
#include "src\base\ftstream.c"
#undef FT_ERR_BASE
#include "src\base\ftstroke.c"
#undef FT_ERR_BASE
#include "src\base\ftsynth.c"
#undef FT_ERR_BASE
#include "src\base\ftsystem.c"
#undef FT_ERR_BASE
#include "src\base\fttrigon.c"
#undef FT_ERR_BASE
#include "src\base\fttype1.c"
#undef FT_ERR_BASE
#include "src\base\ftutil.c"
#undef FT_ERR_BASE
#include "src\base\ftwinfnt.c"

#undef FT_ERR_BASE
#include "src\autofit\afangles.c"
#undef FT_ERR_BASE
#include "src\autofit\afblue.c"

#undef FT_ERR_BASE
#include "src\autofit\afdummy.c"
#undef FT_ERR_BASE
#include "src\autofit\afglobal.c"
#undef FT_ERR_BASE
#include "src\autofit\afhints.c"
#undef FT_ERR_BASE
#include "src\autofit\afindic.c"
#undef FT_ERR_BASE
#include "src\autofit\aflatin.c"
#undef FT_ERR_BASE
#include "src\autofit\afloader.c"

#ifndef T1_CONFIG_OPTION_NO_AFM
#undef FT_ERR_BASE
#include "src\psaux\afmparse.c"
#endif

#undef FT_ERR_BASE
#include "src\autofit\afpic.c"
#undef FT_ERR_BASE
#include "src\autofit\afranges.c"
#undef FT_ERR_BASE
#include "src\autofit\afwarp.c"

//#include "src\bdf\bdf.c" //Group
#undef FT_ERR_BASE
#include "src\bdf\bdfdrivr.c"
#undef FT_ERR_BASE
#include "src\bdf\bdflib.c"
#undef FT_ERR_BASE
#include "src\cff\cf2arrst.c"
#undef FT_ERR_BASE
#include "src\cff\cf2blues.c"
#undef FT_ERR_BASE
#include "src\cff\cf2error.c"
#undef FT_ERR_BASE
#include "src\cff\cf2font.c"
#undef FT_ERR_BASE
#include "src\cff\cf2ft.c"
#undef FT_ERR_BASE
#include "src\cff\cf2hints.c"
#undef FT_ERR_BASE
#include "src\cff\cf2intrp.c"
#undef FT_ERR_BASE
#include "src\cff\cf2read.c"
#undef FT_ERR_BASE
#include "src\cff\cf2stack.c"


//#include "src\cff\cff.c" //Group
#undef FT_ERR_BASE
#include "src\cff\cffcmap.c"
#undef FT_ERR_BASE
#include "src\cff\cffdrivr.c"
#undef FT_ERR_BASE
#include "src\cff\cffgload.c"
#undef FT_ERR_BASE
#include "src\cff\cffload.c"
#undef FT_ERR_BASE
#include "src\cff\cffobjs.c"
#undef FT_ERR_BASE
#include "src\cff\cffparse.c"
#undef FT_ERR_BASE
#include "src\cff\cffpic.c"

#undef FT_ERR_BASE
#include "src\cid\cidgload.c"
#undef FT_ERR_BASE
#include "src\cid\cidload.c"
#undef FT_ERR_BASE
#include "src\cid\cidobjs.c"
#undef FT_ERR_BASE
#include "src\cid\cidparse.c"
#undef FT_ERR_BASE
#include "src\cid\cidriver.c"

#undef FT_ERR_BASE
#include "src\bzip2\ftbzip2.c"
//#include "src\cache\ftcache.c" //Group

#undef FT_ERR_BASE
#undef FT_COMPONENT
#include "src\cache\ftcbasic.c"

#undef FT_ERR_BASE
#include "src\cache\ftccache.c"
#undef FT_ERR_BASE
#include "src\cache\ftccmap.c"
#undef FT_ERR_BASE
#include "src\cache\ftcglyph.c"

#undef FT_ERR_BASE
#include "src\base\ftcid.c"
#undef FT_ERR_BASE
#include "src\cache\ftcimage.c"
#undef FT_ERR_BASE
#include "src\cache\ftcmanag.c"
#undef FT_ERR_BASE
#include "src\cache\ftcmru.c"
#undef FT_ERR_BASE
#include "src\cache\ftcsbits.c"
#undef FT_ERR_BASE
#include "src\base\ftdbgmem.c"
#undef FT_ERR_BASE
#include "src\base\ftdebug.c"
#undef FT_ERR_BASE
#include "src\base\ftfntfmt.c"
#undef FT_ERR_BASE
#include "src\base\ftfstype.c"
#undef FT_ERR_BASE
#include "src\base\ftgasp.c"
#undef FT_ERR_BASE
#include "src\base\ftgloadr.c"

#undef FT_ERR_BASE
#include "src\smooth\ftgrays.c"
#undef FT_ERR_BASE
#include "src\smooth\ftspic.c"
#undef FT_ERR_BASE
#include "src\base\ftgxval.c"
#undef FT_ERR_BASE
#include "src\gzip\ftgzip.c"
#undef FT_ERR_BASE
#include "src\base\ftinit.c"
#undef FT_ERR_BASE
#include "src\base\ftlcdfil.c"
#undef FT_ERR_BASE
#include "src\lzw\ftlzw.c"
//#include "src\base\ftmac.c"
#undef FT_ERR_BASE
#include "src\base\ftmm.c"
#undef FT_ERR_BASE
#include "src\base\ftobjs.c"
#undef FT_ERR_BASE
#include "src\base\ftotval.c"
#undef FT_ERR_BASE
#include "src\base\ftoutln.c"
#undef FT_ERR_BASE
#include "src\base\ftpatent.c"
#undef FT_ERR_BASE
#include "src\base\ftpfr.c"
#undef FT_ERR_BASE
#include "src\base\ftpic.c"

#undef FT_ERR_BASE
#undef bits
#include "src\raster\ftraster.c"

#undef FT_ERR_BASE
#include "src\raster\ftrend1.c"
#undef FT_ERR_BASE
#include "src\smooth\ftsmooth.c"
#undef FT_ERR_BASE
#include "src\base\ftsnames.c"
#include "src\base\ftrfork.c"

#undef FT_ERR_BASE
#include "src\autofit\hbshim.c"

//#include "src\pcf\pcf.c" //Group
#undef FT_ERR_BASE
#include "src\pcf\pcfdrivr.c"

#include "src\pcf\pcfread.c"
#include "src\pcf\pcfutil.c"

//#include "src\pfr\pfr.c" //Group
#undef FT_ERR_BASE
#include "src\pfr\pfrcmap.c"
#include "src\pfr\pfrdrivr.c"
#include "src\pfr\pfrgload.c"

#undef FT_ERR_BASE
#undef local
#include "src\pfr\pfrload.c"

#undef FT_ERR_BASE
#include "src\pfr\pfrobjs.c"
#undef FT_ERR_BASE
#include "src\pfr\pfrsbit.c"

#undef FT_ERR_BASE
#include "src\sfnt\ttcmap.c"
#ifdef TT_CONFIG_OPTION_EMBEDDED_BITMAPS
#undef FT_ERR_BASE
#include "src\sfnt\ttsbit.c"
#undef FT_ERR_BASE
#include "src\sfnt\pngshim.c"
#endif
#ifdef TT_CONFIG_OPTION_POSTSCRIPT_NAMES
#undef FT_ERR_BASE
#include "src\sfnt\ttpost.c"
#endif
#ifdef TT_CONFIG_OPTION_BDF
#undef FT_ERR_BASE
#include "src\sfnt\ttbdf.c"
#endif

#undef FT_ERR_BASE
//#include "src\psaux\psaux.c" //Group
#include "src\psaux\psauxmod.c"
#include "src\psaux\psconv.c"
#include "src\pshinter\pshalgo.c"
#include "src\pshinter\pshglob.c"

#undef FT_ERR_BASE
//#include "src\pshinter\pshinter.c" //Group
#include "src\pshinter\pshmod.c"
#include "src\pshinter\pshpic.c"
#include "src\pshinter\pshrec.c"
#include "src\psnames\psmodule.c"

#define FT_MAKE_OPTION_SINGLE_OBJECT
//#include "src\psnames\psnames.c" //Group

#undef FT_ERR_BASE
#include "src\psaux\psobjs.c"
#include "src\psnames\pspic.c"

#undef FT_ERR_BASE
//#include "src\raster\raster.c" //Group
#include "src\raster\rastpic.c"
#include "src\sfnt\sfdriver.c"

#undef FT_ERR_BASE
#include "src\sfnt\sfntpic.c"
#include "src\sfnt\sfobjs.c"

#include "src\psaux\t1cmap.c"
#include "src\psaux\t1decode.c"
#undef FT_ERR_BASE
#include "src\type1\t1driver.c"
#include "src\type1\t1gload.c"
#include "src\type1\t1load.c"
#include "src\type1\t1objs.c"
#include "src\type1\t1parse.c"

#undef FT_ERR_BASE
//#include "src\truetype\truetype.c" //Group
#ifdef TT_USE_BYTECODE_INTERPRETER
#include "src\truetype\ttinterp.c"
#include "src\truetype\ttsubpix.c"
#endif

#undef FT_ERR_BASE
#include "src\truetype\ttdriver.c"
#include "src\truetype\ttgload.c"

#undef FT_ERR_BASE
#include "src\sfnt\ttkern.c"
#include "src\sfnt\ttload.c"
#include "src\sfnt\ttmtx.c"
#include "src\truetype\ttobjs.c"
#include "src\truetype\ttpic.c"
#include "src\truetype\ttpload.c"

#undef FT_ERR_BASE
//#include "src\type1\type1.c"  //Group
#ifndef T1_CONFIG_OPTION_NO_AFM
#include "src\type1\t1afm.c"
#endif

#undef FT_ERR_BASE
#include "src\type42\t42drivr.c"
#include "src\type42\t42objs.c"
#include "src\type42\t42parse.c"

#include "src\winfonts\winfnt.c"

//Remplacement bug in zutil.c
//voidpf zcalloc (voidpf opaque,unsigned items, unsigned size){
//    if (opaque) items += size - size;
//    return (voidpf)ft_scalloc(items, size);
//}
//void  zcfree (voidpf opaque,voidpf ptr){
//    ft_sfree(ptr);
//    if (opaque) return;
//}
#include "src\gzip\zutil.c"

#include "src\autofit\afcjk.c"
#include "src\autofit\afmodule.c"

#include "src\otvalid\otvbase.c"
#include "src\otvalid\otvcommn.c"
#include "src\otvalid\otvgdef.c"
#include "src\otvalid\otvgpos.c"
#include "src\otvalid\otvgsub.c"
#include "src\otvalid\otvjstf.c"
#include "src\otvalid\otvmath.c"
#include "src\otvalid\otvmod.c"

#ifdef TT_CONFIG_OPTION_GX_VAR_SUPPORT
#include "src\truetype\ttgxvar.c"   // gx distortable font
#endif

#endif
