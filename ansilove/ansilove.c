//
//  ansilove.c
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import "ansilove.h"
#else
#include <stdbool.h>
#include "ansilove.h"
#endif

// ANSi
void alAnsiLoader(char *input, char output[], char font[], char bits[], char icecolors[], char *fext)
{
    // ladies and gentlemen, it's type declaration time
    int32_t columns = 80;
    int32_t font_size_x;
    int32_t font_size_y;
    char *font_file;
    bool isAmigaFont = false;
    bool ced = false;
    bool transparent = false;
    bool workbench = false;
    
    // determine the font we use to render the output
    if (strcmp(font, "80x25") == 0) {
        font_file = "ansilove_font_pc_80x25.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "80x50") == 0) {
        font_file = "ansilove_font_pc_80x50.png";
        font_size_x = 9;
        font_size_y = 8;
    }
    else if (strcmp(font, "terminus") == 0) {
        font_file = "ansilove_font_pc_terminus.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "armenian") == 0) {
        font_file = "ansilove_font_pc_armenian.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "baltic") == 0) {
        font_file = "ansilove_font_pc_baltic.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "cyrillic") == 0) {
        font_file = "ansilove_font_pc_cyrillic.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "french-canadian") == 0) {
        font_file = "ansilove_font_pc_french_canadian.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek") == 0) {
        font_file = "ansilove_font_pc_greek.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek-869") == 0) {
        font_file = "ansilove_font_pc_greek_869.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "hebrew") == 0) {
        font_file = "ansilove_font_pc_hebrew.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "icelandic") == 0) {
        font_file = "ansilove_font_pc_icelandic.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin1") == 0) {
        font_file = "ansilove_font_pc_latin1.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin2") == 0) {
        font_file = "ansilove_font_pc_latin2.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "nordic") == 0) {
        font_file = "ansilove_font_pc_nordic.png";
        font_size_x = 9;
        font_size_y = 16; 
    }
    else if (strcmp(font, "persian") == 0) {
        font_file = "ansilove_font_pc_persian.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "portuguese") == 0) {
        font_file = "ansilove_font_pc_portuguese.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "russian") == 0) {
        font_file = "ansilove_font_pc_russian.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "turkish") == 0) {
        font_file = "ansilove_font_pc_turkish.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "amiga") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_topaz_1200.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "b-strict") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_b-strict.png";
        font_size_x = 8;
        font_size_y = 8;
    }
    else if (strcmp(font, "b-struct") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_b-struct.png";
        font_size_x = 8;
        font_size_y = 8;
    }
    else if (strcmp(font, "microknight") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_microknight.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight+") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_microknight+.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknightplus") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_microknight+.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "mosoul") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_mosoul.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "pot-noodle") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_pot-noodle.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_topaz_1200.png";
        font_size_x = 8;
        font_size_y = 16;   
    }
    else if (strcmp(font, "topaz+") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_topaz_1200+.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topazplus") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_topaz_1200+.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_topaz_500.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500+") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_topaz_500+.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500plus") == 0) {
        isAmigaFont = true;
        font_file = "ansilove_font_amiga_topaz_500+.png";
        font_size_x = 8;
        font_size_y = 16;
    }
    else {
        // in all other cases use the standard DOS font
        font_file = "ansilove_font_pc_80x25.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    
    // to deal with the bits flag, we declared handy bool types   
    if (strcmp(bits, "ced") == 0) {
        ced = true;
    }
    else if (strcmp(bits, "transparent") == 0) {
        transparent = true;
    }
    else if (strcmp(bits, "workbench") == 0) {
        workbench = true;
    }
    else if (strcmp(bits, "workbench-transparent") == 0) {
        workbench = true;
        transparent = true;
    }
    // force defaults if necessary
    else if ((strcmp(bits, "8") != 0 && strcmp(bits, "9") != 0) || isAmigaFont == true) {
        sprintf(bits, "%s", "8");
    }
    
    // purpose: surpressing Clang warnings of unused font / columns variables :)
    // gonna remove that pretty soon! 
    printf("font file: %s / ANSi columns: %d\n", font_file, columns);
    
    // this is for testing my explode() function I ported (and enhanced) from PHP.
    // will be wiped from the codebase again...!
    char **dizArray;
    int32_t dizCount, i;
    
    dizCount = explode(&dizArray, ',', DIZ_EXTENSIONS);
    
    for (i = 0; i < dizCount; ++i) {
        printf("DIZ-extension %d: %s\n", i+1, dizArray[i]);
    }
    
} // < -- REMINDER: Remove this when enabling the ANSi code below again!

    // load the input file
    
//   if (!$input_file = fopen($input,'r'))
//   {
//      error("Can't open file $input");
//   }
//
//   $input_file_sauce=load_sauce($input);
//
//   if ($input_file_sauce!=NULL)
//   {
//      $input_file_size=$input_file_sauce['FileSize'];
//   }
//   else
//   {
//      $input_file_size=filesize($input);
//   }
//
//   if (!$input_file_buffer = fread($input_file,$input_file_size))
//   {
//      error("Can't read file $input");
//   }
//
//   fclose($input_file);
//
//   $diz_extensions_exploded=explode(",",DIZ_EXTENSIONS);
//
//   for ($loop=0;$loop<sizeof($diz_extensions_exploded);$loop++)
//   {
//      $diz_extension_length=strlen($diz_extensions_exploded[$loop]);
//
//      if (strtolower(substr($input,(strlen($input)-$diz_extension_length),$diz_extension_length))==$diz_extensions_exploded[$loop] || strtolower(substr($input,strlen($input)-($diz_extension_length+9),($diz_extension_length+9)))==$diz_extensions_exploded[$loop].'.ansilove')
//      {
//         $input_file_buffer=preg_replace("/^(\s+[\r\n])+/","",$input_file_buffer);
//         $input_file_buffer=rtrim($input_file_buffer);
//         $input_file_size=strlen($input_file_buffer);
//      }
//   }
//
///*****************************************************************************/
///* LOAD BACKGROUND/FONT                                                      */
///*****************************************************************************/
//
//   if (!$background = imagecreatefrompng(dirname(__FILE__).'/fonts/ansilove_background.png'))
//   {
//      error("Can't open file ansilove_background.png");
//   }
//
//   if (!$font = imagecreatefrompng(dirname(__FILE__).'/fonts/'.font_file))
//   {
//      error("Can't open file font_file");
//   }
//
//   imagecolortransparent($font,20);
//
//
//
///*****************************************************************************/
///* PROCESS ANSI                                                              */
///*****************************************************************************/
//
//   $color_background=0;
//   $color_foreground=7;
//
//   $loop=0;
//
//   $position_x=0;
//   $position_y=0;
//
//   $position_x_max=0;
//   $position_y_max=0;
//
//   while ($loop<$input_file_size)
//   {
//      $current_character=ord($input_file_buffer[$loop]);
//      $next_character=ord($input_file_buffer[$loop+1]);
//
//      if ($position_x==80 && WRAP_COLUMN_80)
//      {
//         $position_y++;
//         $position_x=0;
//      }
//
///*****************************************************************************/
///* CR+LF                                                                     */
///*****************************************************************************/
//
//      if ($current_character==13)
//      {
//         if ($next_character==10)
//         {
//            $position_y++;
//            $position_x=0;
//            $loop++;
//         }
//      }
//
///*****************************************************************************/
///* LF                                                                        */
///*****************************************************************************/
//
//      if ($current_character==10)
//      {
//         $position_y++;
//         $position_x=0;
//      }
//
///*****************************************************************************/
///* TAB                                                                       */
///*****************************************************************************/
//
//      if ($current_character==9)
//      {
//         $position_x+=8;
//      }
//
///*****************************************************************************/
///* SUB                                                                       */
///*****************************************************************************/
//
//      if ($current_character==26 && SUBSTITUTE_BREAK)
//      {
//         break;
//      }
//
//
//
///*****************************************************************************/
///* ANSI SEQUENCE                                                             */
///*****************************************************************************/
//
//      if ($current_character==27 && $next_character==91)
//      {
//         unset($ansi_sequence);
//
//         for ($ansi_sequence_loop=0;$ansi_sequence_loop<12;$ansi_sequence_loop++)
//         {
//            $ansi_sequence_character=$input_file_buffer[$loop+2+$ansi_sequence_loop];
//
///*****************************************************************************/
///* CURSOR POSITION                                                           */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='H' || $ansi_sequence_character=='f')
//            {
//               $ansi_sequence_exploded=explode(";",$ansi_sequence);
//               $position_y=$ansi_sequence_exploded[0]-1;
//               $position_x=$ansi_sequence_exploded[1]-1;
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* CURSOR UP                                                                 */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='A')
//            {
//               if ($ansi_sequence=='')
//               {
//                  $ansi_sequence=1;
//               }
//
//               $position_y=$position_y-$ansi_sequence;
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* CURSOR DOWN                                                               */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='B')
//            {
//               if ($ansi_sequence=='')
//               {
//                  $ansi_sequence=1;
//               }
//
//               $position_y=$position_y+$ansi_sequence;
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* CURSOR FORWARD                                                            */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='C')
//            {
//               if ($ansi_sequence=='')
//               {
//                  $ansi_sequence=1;
//               }
//
//               $position_x=$position_x+$ansi_sequence;
//               if ($position_x>80)
//               {
//                  $position_x=80;
//               }
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* CURSOR BACKWARD                                                           */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='D')
//            {
//               if ($ansi_sequence=='')
//               {
//                  $ansi_sequence=1;
//               }
//
//               $position_x=$position_x-$ansi_sequence;
//               if ($position_x<0)
//               {
//                  $position_x=0;
//               }
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* SAVE CURSOR POSITION                                                      */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='s')
//            {
//               $saved_position_y=$position_y;
//               $saved_position_x=$position_x;
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* RESTORE CURSOR POSITION                                                   */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='u')
//            {
//               $position_y=$saved_position_y;
//               $position_x=$saved_position_x;
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* ERASE DISPLAY                                                             */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='J')
//            {
//               if ($ansi_sequence==2)
//               {
//                  unset($ansi_buffer);
//
//                  $position_x=0;
//                  $position_y=0;
//
//                  $position_x_max=0;
//                  $position_y_max=0;
//               }
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* SET GRAPHIC RENDITION                                                     */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='m')
//            {
//               $ansi_sequence_exploded=explode(";",$ansi_sequence);
//
//               sort($ansi_sequence_exploded);
//
//               for ($loop_ansi_sequence=0;$loop_ansi_sequence<sizeof($ansi_sequence_exploded);$loop_ansi_sequence++)
//               {
//                  $ansi_sequence_value=$ansi_sequence_exploded[$loop_ansi_sequence];
//
//                  if ($ansi_sequence_value==0)
//                  {
//                     $color_background=0;
//                     $color_foreground=7;
//                     $bold=FALSE;
//                     $underline=FALSE;
//                     $italics=FALSE;
//                     $blink=FALSE;
//                  }
//
//                  if ($ansi_sequence_value==1)
//                  {
//                     if (!$workbench)
//                     {
//                        $color_foreground+=8;
//					 }
//                     $bold=TRUE;
//                  }
//
//                  if ($ansi_sequence_value==3)
//                  {
//                     $italics=TRUE;
//                  }
//
//                  if ($ansi_sequence_value==4)
//                  {
//                     $underline=TRUE;
//                  }
//
//                  if ($ansi_sequence_value==5)
//                  {
//                     if (!$workbench)
//                     {
//                        $color_background+=8;
//					 }
//                     $blink=TRUE;
//                  }
//
//                  if ($ansi_sequence_value>29 && $ansi_sequence_value<38)
//                  {
//                     $color_foreground=$ansi_sequence_value-30;
//
//                     if ($bold)
//                     {
//                        $color_foreground+=8;
//                     }
//                  }
//
//                  if ($ansi_sequence_value>39 && $ansi_sequence_value<48)
//                  {
//                     $color_background=$ansi_sequence_value-40;
//
//                     if ($blink && $icecolors)
//                     {
//                        $color_background+=8;
//                     }
//                  }
//               }
//
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
///*****************************************************************************/
///* CURSOR DE/ACTIVATION (AMIGA ANSI)                                         */
///*****************************************************************************/
//
//            if ($ansi_sequence_character=='p')
//            {
//               $loop+=$ansi_sequence_loop+2;
//               break;
//            }
//
//            $ansi_sequence.=$ansi_sequence_character;
//         }
//      }
//      elseif ($current_character!=10 && $current_character!=13 && $current_character!=9)
//      {
//
///*****************************************************************************/
///* RECORD NUMBER OF COLUMNS AND LINES USED                                   */
///*****************************************************************************/
//
//         if ($position_x>$position_x_max)
//         {
//            $position_x_max=$position_x;
//         }
//
//         if ($position_y>$position_y_max)
//         {
//            $position_y_max=$position_y;
//         }
//
//
//
///*****************************************************************************/
///* WRITE CURRENT CHARACTER INFO IN A TEMPORARY ARRAY                         */
///*****************************************************************************/
//
//         if (!$font_amiga || ($current_character!=12 && $current_character!=13))
//         {
//            $ansi_buffer.=chr($color_background);
//            $ansi_buffer.=chr($color_foreground);
//            $ansi_buffer.=chr($current_character);
//            $ansi_buffer.=chr($bold);
//            $ansi_buffer.=chr($italics);
//            $ansi_buffer.=chr($underline);
//            $ansi_buffer.=chr($position_x);
//            $ansi_buffer.=chr($position_y & 0xFF);
//            $ansi_buffer.=chr($position_y>>8);
//
//            $position_x++;
//         }
//      }
//      $loop++;
//   }
//
//
//
///*****************************************************************************/
///* ALLOCATE IMAGE BUFFER MEMORY                                              */
///*****************************************************************************/
//
//   $position_x_max++;
//   $position_y_max++;
//
//   if ($ced)
//   {
//      $columns=78;
//   }
//
//   for ($loop=0;$loop<sizeof($diz_extensions_exploded);$loop++)
//   {
//      $diz_extension_length=strlen($diz_extensions_exploded[$loop]);
//
//      if (strtolower(substr($input,(strlen($input)-$diz_extension_length),$diz_extension_length))==$diz_extensions_exploded[$loop] || strtolower(substr($input,strlen($input)-($diz_extension_length+9),($diz_extension_length+9)))==$diz_extensions_exploded[$loop].'.ansilove')
//      {
//         $columns=min($position_x_max,80);
//      }
//   }
//
//   if (!$ansi = imagecreate($columns*$bits,($position_y_max)*font_size_y))
//   {
//      error("Can't allocate buffer image memory");
//   }
//
//   if ($ced)
//   {
//      $ced_background_color=explode(",",CED_BACKGROUND_COLOR);
//      $ced_foreground_color=explode(",",CED_FOREGROUND_COLOR);
//
//      imagecolorallocate($ansi,$ced_background_color[0],$ced_background_color[1],$ced_background_color[2]);
//
//      $ced_color=imagecolorallocate($ansi,$ced_background_color[0],$ced_background_color[1],$ced_background_color[2]);
//      $ced_color=imagecolorallocate($background,$ced_background_color[0],$ced_background_color[1],$ced_background_color[2]);
//
//      imagefill($ansi,0,0,$ced_color);
//      imagefilledrectangle($background,0,0,144,16,$ced_color);
//
//      for ($loop=0;$loop<16;$loop++)
//      {
//         imagecolorset($font,$loop,$ced_foreground_color[0],$ced_foreground_color[1],$ced_foreground_color[2]);
//      }
//   }
//   else if ($workbench)
//   {
//      $workbench_color[0]=explode(",",WORKBENCH_COLOR_0);
//      $workbench_color[1]=explode(",",WORKBENCH_COLOR_4);
//      $workbench_color[2]=explode(",",WORKBENCH_COLOR_2);
//      $workbench_color[3]=explode(",",WORKBENCH_COLOR_6);
//      $workbench_color[4]=explode(",",WORKBENCH_COLOR_1);
//      $workbench_color[5]=explode(",",WORKBENCH_COLOR_5);
//      $workbench_color[6]=explode(",",WORKBENCH_COLOR_3);
//      $workbench_color[7]=explode(",",WORKBENCH_COLOR_7);
//
//      imagecolorallocate($ansi,$workbench_color[0][0],$workbench_color[0][1],$workbench_color[0][2]);
//
//      $workbench_background=imagecolorallocate($ansi,$workbench_color[0][0],$workbench_color[0][1],$workbench_color[0][2]);
//      $workbench_background=imagecolorallocate($background,$workbench_color[0][0],$workbench_color[0][1],$workbench_color[0][2]);
//
//      imagefill($ansi,0,0,$workbench_background);
//
//      for ($loop=0; $loop<8; $loop++)
//      {
//         imagecolorset($background,$loop,$workbench_color[$loop][0],$workbench_color[$loop][1],$workbench_color[$loop][2]);
//         imagecolorset($background,$loop+8,$workbench_color[$loop][0],$workbench_color[$loop][1],$workbench_color[$loop][2]);
//         imagecolorset($font,$loop,$workbench_color[$loop][0],$workbench_color[$loop][1],$workbench_color[$loop][2]);
//         imagecolorset($font,$loop+8,$workbench_color[$loop][0],$workbench_color[$loop][1],$workbench_color[$loop][2]);
//      }
//   }
//   else
//   {
//      $background_canvas=imagecolorallocate($ansi,0,0,0);
//   }
//
//   for ($loop=0; $loop<16; $loop++)
//   {
//	  /* Generating ANSI colors array in order to be able to draw underlines */
//      $color_index=imagecolorsforindex($background,$loop);
//      $colors[$loop]=imagecolorallocate($ansi,$color_index['red'],$color_index['green'],$color_index['blue']);
//   }
//
//
//
///*****************************************************************************/
///* RENDER ANSI                                                               */
///*****************************************************************************/
//
//   for ($loop=0;$loop<strlen($ansi_buffer);$loop+=9)
//   {
//      $color_background=ord($ansi_buffer[$loop]);
//      $color_foreground=ord($ansi_buffer[$loop+1]);
//      $character=ord($ansi_buffer[$loop+2]);
//      $bold=ord($ansi_buffer[$loop+3]);
//      $italics=ord($ansi_buffer[$loop+4]);
//      $underline=ord($ansi_buffer[$loop+5]);
//      $position_x=ord($ansi_buffer[$loop+6]);
//      $position_y=ord($ansi_buffer[$loop+7])+(ord($ansi_buffer[$loop+8])<<8);
//
//      if (!$font_amiga)
//      {
//         imagecopy($ansi,$background,$position_x*$bits,$position_y*font_size_y,$color_background*9,0,$bits,font_size_y);
//         imagecopy($ansi,$font,$position_x*$bits,$position_y*font_size_y,$character*font_size_x,$color_foreground*font_size_y,$bits,font_size_y);
//      }
//      else
//      {
//         if ($color_background!=0 || !$italics)
//         {
//            imagecopy($ansi,$background,$position_x*$bits,$position_y*font_size_y,$color_background*9,0,$bits,font_size_y);
//         }
//
//         if (!$italics)
//         {
//            imagecopy($ansi,$font,$position_x*$bits,$position_y*font_size_y,$character*font_size_x,$color_foreground*font_size_y,$bits,font_size_y);
//         }
//         else
//         {
//            imagecopy($ansi,$font,$position_x*$bits+3,$position_y*font_size_y,$character*font_size_x,$color_foreground*font_size_y,$bits,2);
//            imagecopy($ansi,$font,$position_x*$bits+2,$position_y*font_size_y+2,$character*font_size_x,$color_foreground*font_size_y+2,$bits,4);
//            imagecopy($ansi,$font,$position_x*$bits+1,$position_y*font_size_y+6,$character*font_size_x,$color_foreground*font_size_y+6,$bits,4);
//            imagecopy($ansi,$font,$position_x*$bits,$position_y*font_size_y+10,$character*font_size_x,$color_foreground*font_size_y+10,$bits,4);
//            imagecopy($ansi,$font,$position_x*$bits-1,$position_y*font_size_y+14,$character*font_size_x,$color_foreground*font_size_y+14,$bits,2);
//         }
//            
//         if ($italics && $bold)
//         {
//            imagecopy($ansi,$font,$position_x*$bits+3+1,$position_y*font_size_y,$character*font_size_x,$color_foreground*font_size_y,$bits,2);
//            imagecopy($ansi,$font,$position_x*$bits+2+1,$position_y*font_size_y+2,$character*font_size_x,$color_foreground*font_size_y+2,$bits,4);
//            imagecopy($ansi,$font,$position_x*$bits+1+1,$position_y*font_size_y+6,$character*font_size_x,$color_foreground*font_size_y+6,$bits,4);
//            imagecopy($ansi,$font,$position_x*$bits+1,$position_y*font_size_y+10,$character*font_size_x,$color_foreground*font_size_y+10,$bits,4);
//            imagecopy($ansi,$font,$position_x*$bits-1+1,$position_y*font_size_y+14,$character*font_size_x,$color_foreground*font_size_y+14,$bits,2);
//         }
//
//         if ($bold && !$italics)
//         {
//            imagecopy($ansi,$font,1+$position_x*$bits,$position_y*font_size_y,$character*font_size_x,$color_foreground*font_size_y,$bits,font_size_y);
//         }
//
//         if ($underline)
//         {
//            $loop_column=0;
//            $character_size_x=8;
//
//            if ($bold)
//            {
//               $character_size_x++;
//            }
//
//            if ($italics)
//            {
//               $loop_column=-1;
//               $character_size_x=11;
//            }
//
//            while ($loop_column<$character_size_x)
//            {
//               if (imagecolorat($ansi,$position_x*$bits+$loop_column,$position_y*font_size_y+15)==$color_background && imagecolorat($ansi,$position_x*$bits+$loop_column+1,$position_y*font_size_y+15)==$color_background)
//               {
//                  imagesetpixel($ansi,$position_x*$bits+$loop_column,$position_y*font_size_y+14,$colors[$color_foreground]);
//                  imagesetpixel($ansi,$position_x*$bits+$loop_column,$position_y*font_size_y+15,$colors[$color_foreground]);
//               }
//               else if (imagecolorat($ansi,$position_x*$bits+$loop_column,$position_y*font_size_y+15)!=$color_background && imagecolorat($ansi,$position_x*$bits+$loop_column+1,$position_y*font_size_y+15)==$color_background)
//               {
//                  $loop_column++;
//               }
//               
//               $loop_column++;
//            }
//
//            if ($pixel_carry)
//            {
//               imagesetpixel($ansi,$position_x*$bits,$position_y*font_size_y+14,$colors[$color_foreground]);
//               imagesetpixel($ansi,$position_x*$bits,$position_y*font_size_y+15,$colors[$color_foreground]);
//               $pixel_carry=FALSE;
//            }
//
//            if (imagecolorat($font,$character*font_size_x,$color_foreground*font_size_y+15)!=20)
//            {
//               imagesetpixel($ansi,$position_x*$bits-1,$position_y*font_size_y+14,$colors[$color_foreground]);
//               imagesetpixel($ansi,$position_x*$bits-1,$position_y*font_size_y+15,$colors[$color_foreground]);
//            }
//
//            if (imagecolorat($font,$character*font_size_x+$character_size_x-1,$color_foreground*font_size_y+15)!=20)
//            {
//               $pixel_carry=TRUE;
//            }
//         }
//      }
//   }
//
//
//
///*****************************************************************************/
///* CREATE OUTPUT FILE                                                        */
///*****************************************************************************/
//
//   if ($transparent)
//   {
//      imagecolortransparent($ansi,$background_canvas);
//   }
//
//   if ($thumbnail)
//   {
//      thumbnail($ansi,$output,$columns,font_size_y,$position_y_max);
//   }
//   else
//   {
//      if ($output=='online')
//      {
//         Header("Content-type: image/png");
//         ImagePNG($ansi);
//      }
//      else
//      {
//         if (!SPLIT)
//         {
//            ImagePNG($ansi,$output);
//         }
//         else
//         {
//            $image_size_y=$position_y_max*font_size_y;
//            $split_size_y=SPLIT_HEIGHT;
//
//            $loop_max=($image_size_y/$split_size_y);
//
//            for ($loop=0; $loop<$loop_max; $loop++)
//            {
//               if (($image_size_y-($split_size_y*$loop))<$split_size_y)
//               {
//                  $height=($image_size_y-($split_size_y*$loop));
//               }
//               else
//               {
//                  $height=$split_size_y;
//               }
//
//               if (!$split = imagecreate($columns*$bits,$height))
//               {
//                  error("Can't allocate buffer image memory");
//               }
//
//               imagecolorallocate($split,0,0,0);
//               imagecopy($split,$ansi,0,0,0,($loop*$split_size_y),$columns*$bits,$height);
//
//               if ($loop_max>=1)
//               {
//                  $output_file=$output.SPLIT_SEPARATOR.str_pad($loop,4,"0",STR_PAD_LEFT).".png";
//               }
//               else
//               {
//                  $output_file=$output.".png";
//               }
//
//               $output_files[]=$output_file;
//
//               if ($transparent)
//               {
//                  imagecolortransparent($split,$background_canvas);
//               }
//
//               ImagePNG($split,$output_file);
//               imagedestroy($split);
//            }
//         }
//      }
//   }
//
//
//
///*****************************************************************************/
///* FREE MEMORY                                                               */
///*****************************************************************************/
//
//   imagedestroy($ansi);
//   imagedestroy($background);
//   imagedestroy($font);
//   
//   return $output_files;
//}
//
//
//
///*****************************************************************************/
///* LOAD PCBOARD                                                              */
///*****************************************************************************/
//
//function load_pcboard($input,$output,$font,$bits)
//{
//   check_libraries();
//
///*****************************************************************************/
///* CHECK PARAMETERS AND FORCE DEFAULT VALUES IF INVALID INPUT IS DETECTED    */
///*****************************************************************************/
//
//   $columns=80;
//
//   if ($bits=='thumbnail')
//   {
//      $thumbnail=TRUE;
//   }
//   if ($bits!=8 && $bits!=9)
//   {
//      $bits=8;
//   }
//
//   switch($font)
//   {
//   case '80x25':
//      font_file = "ansilove_font_pc_80x25.png';
//      font_size_x = 9;
//      font_size_y = 16;
//      break;
//
//   case '80x50':
//      font_file = "ansilove_font_pc_80x50.png';
//      font_size_x = 9;
//      font_size_y = 8;
//      break;
//
//   default:
//      font_file = "ansilove_font_pc_80x25.png';
//      font_size_x = 9;
//      font_size_y = 16;
//   }
//
//
//
///*****************************************************************************/
///* LOAD INPUT FILE                                                           */
///*****************************************************************************/
//
//   if (!$input_file = fopen($input,'r'))
//   {
//      error("Can't open file $input");
//   }
//
//   $input_file_sauce=load_sauce($input);
//
//   if ($input_file_sauce!=NULL)
//   {
//      $input_file_size=$input_file_sauce['FileSize'];
//   }
//   else
//   {
//      $input_file_size=filesize($input);
//   }
//
//   if (!$input_file_buffer = fread($input_file,$input_file_size))
//   {
//      error("Can't read file $input");
//   }
//
//   fclose($input_file);
//
//
//
///*****************************************************************************/
///* LOAD BACKGROUND/FONT                                                      */
///*****************************************************************************/
//
//   if (!$background = imagecreatefrompng(dirname(__FILE__).'/fonts/ansilove_background.png'))
//   {
//      error("Can't open file ansilove_background.png");
//   }
//
//   if (!$font = imagecreatefrompng(dirname(__FILE__).'/fonts/'.font_file))
//   {
//      error("Can't open file font_file");
//   }
//
//   imagecolortransparent($font,20);
//
//
//
///*****************************************************************************/
///* ALLOCATE BACKGROUND/FOREGROUND COLOR ARRAYS                               */
///*****************************************************************************/
//
//   $pcb_colors[48]=0; $pcb_colors[49]=4; $pcb_colors[50]=2; $pcb_colors[51]=6; $pcb_colors[52]=1; $pcb_colors[53]=5; $pcb_colors[54]=3; $pcb_colors[55]=7; $pcb_colors[56]=8; $pcb_colors[57]=12; $pcb_colors[65]=10; $pcb_colors[66]=14; $pcb_colors[67]=9; $pcb_colors[68]=13; $pcb_colors[69]=11; $pcb_colors[70]=15;
//
//
//
///*****************************************************************************/
///* STRIP UNWANTED PCBOARD CODES (DEFINED IN CONFIG FILE)                     */
///*****************************************************************************/
//
//   $pcboard_strip_codes_exploded=explode(",",PCBOARD_STRIP_CODES);
//
//   for ($loop=0;$loop<sizeof($pcboard_strip_codes_exploded);$loop++)
//   {
//      $input_file_buffer=preg_replace("/(".$pcboard_strip_codes_exploded[$loop].")/","",$input_file_buffer);
//   }
//
//
//
///*****************************************************************************/
///* PROCESS PCB                                                               */
///*****************************************************************************/
//
//   $color_background=0;
//   $color_foreground=7;
//
//   $loop=0;
//
//   $position_x=0;
//   $position_y=0;
//
//   $position_x_max=0;
//   $position_y_max=0;
//
//   while ($loop<$input_file_size)
//   {
//      $current_character=ord($input_file_buffer[$loop]);
//      $next_character=ord($input_file_buffer[$loop+1]);
//
//      if ($position_x==80)
//      {
//         $position_y++;
//         $position_x=0;
//      }
//
///*****************************************************************************/
///* CR+LF                                                                     */
///*****************************************************************************/
//
//      if ($current_character==13)
//      {
//         if ($next_character==10)
//         {
//            $position_y++;
//            $position_x=0;
//            $loop++;
//         }
//      }
//
///*****************************************************************************/
///* LF                                                                        */
///*****************************************************************************/
//
//      if ($current_character==10)
//      {
//         $position_y++;
//         $position_x=0;
//      }
//
///*****************************************************************************/
///* TAB                                                                       */
///*****************************************************************************/
//
//      if ($current_character==9)
//      {
//         $position_x+=8;
//      }
//
///*****************************************************************************/
///* SUB                                                                       */
///*****************************************************************************/
//
//      if ($current_character==26)
//      {
//         break;
//      }
//
///*****************************************************************************/
///* PCB SEQUENCE                                                              */
///*****************************************************************************/
//
//      if ($current_character==64 & $next_character==88)
//      {
//
///*****************************************************************************/
///* SET GRAPHIC RENDITION                                                     */
///*****************************************************************************/
//
//            $color_background=$pcb_colors[ord($input_file_buffer[$loop+2])];
//            $color_foreground=$pcb_colors[ord($input_file_buffer[$loop+3])];
//
//            $loop+=3;
//      }
//      elseif ($current_character==64 & $next_character==67 & $input_file_buffer[$loop+2]=='L' & $input_file_buffer[$loop+3]=='S')
//      {
//
///*****************************************************************************/
///* ERASE DISPLAY                                                             */
///*****************************************************************************/
//
//         unset($pcboard_buffer);
//
//         $position_x=0;
//         $position_y=0;
//
//         $position_x_max=0;
//         $position_y_max=0;
//
//         $loop+=4;
//      }
//      elseif ($current_character==64 & $next_character==80 & $input_file_buffer[$loop+2]=='O' & $input_file_buffer[$loop+3]=='S' & $input_file_buffer[$loop+4]==':')
//      {
//
///*****************************************************************************/
///* CURSOR POSITION                                                           */
///*****************************************************************************/
//
//         if ($input_file_buffer[$loop+6]=='@')
//         {
//            $position_x=(ord($input_file_buffer[$loop+5])-48)-1;
//            $loop+=5;
//         }
//         else
//         {
//            $position_x=(10*(ord($input_file_buffer[$loop+5])-48)+ord($input_file_buffer[$loop+6])-48)-1;
//            $loop+=6;
//         }
//      }     
//      elseif ($current_character!=10 && $current_character!=13 && $current_character!=9)
//      {
//
///*****************************************************************************/
///* RECORD NUMBER OF COLUMNS AND LINES USED                                   */
///*****************************************************************************/
//
//         if ($position_x>$position_x_max)
//         {
//            $position_x_max=$position_x;
//         }
//
//         if ($position_y>$position_y_max)
//         {
//            $position_y_max=$position_y;
//         }
//
//
//
///*****************************************************************************/
///* WRITE CURRENT CHARACTER INFO IN A TEMPORARY ARRAY                         */
///*****************************************************************************/
//
//         $pcboard_buffer[]=$position_x;
//         $pcboard_buffer[]=$position_y;
//         $pcboard_buffer[]=$color_background;
//         $pcboard_buffer[]=$color_foreground;
//         $pcboard_buffer[]=$current_character;
//
//         $position_x++;
//      }
//      $loop++;
//   }
//
//
//
///*****************************************************************************/
///* ALLOCATE IMAGE BUFFER MEMORY                                              */
///*****************************************************************************/
//
//   $position_x_max++;
//   $position_y_max++;
//
//   if (!$pcboard = imagecreate($columns*$bits,($position_y_max)*font_size_y))
//   {
//      error("Can't allocate buffer image memory");
//   }
//
//   imagecolorallocate($pcboard,0,0,0);
//
//
//
///*****************************************************************************/
///* RENDER PCB                                                                */
///*****************************************************************************/
//
//   for ($loop=0;$loop<sizeof($pcboard_buffer);$loop+=5)
//   {
//      $position_x=$pcboard_buffer[$loop];
//      $position_y=$pcboard_buffer[$loop+1];
//      $color_background=$pcboard_buffer[$loop+2];
//      $color_foreground=$pcboard_buffer[$loop+3];
//      $character=$pcboard_buffer[$loop+4];
//
//      imagecopy($pcboard,$background,$position_x*$bits,$position_y*font_size_y,$color_background*9,0,$bits,font_size_y);
//      imagecopy($pcboard,$font,$position_x*$bits,$position_y*font_size_y,$character*font_size_x,$color_foreground*font_size_y,$bits,font_size_y);
//   }
//
//
//
///*****************************************************************************/
///* CREATE OUTPUT FILE                                                        */
///*****************************************************************************/
//
//   if ($thumbnail)
//   {
//      thumbnail($pcboard,$output,$columns,font_size_y,$position_y_max);
//   }
//   else
//   {
//      if ($output=='online')
//      {
//         Header("Content-type: image/png");
//         ImagePNG($pcboard);
//      }
//      else
//      {
//         ImagePNG($pcboard,$output);
//      }
//   }
//
//
//
///*****************************************************************************/
///* FREE MEMORY                                                               */
///*****************************************************************************/
//
//   imagedestroy($pcboard);
//   imagedestroy($background);
//   imagedestroy($font);
//}

// BINARY
void alBinaryLoader(char *input, char output[], char columns[], char font[], char bits[], char icecolors[])
{
    // some type declarations
    int32_t font_size_x;
    int32_t font_size_y;
    char *font_file;
    
    // let's see what font we should use to render output
    if (strcmp(font, "80x25") == 0) {
        font_file = "ansilove_font_pc_80x25.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "80x50") == 0) {
        font_file = "ansilove_font_pc_80x50.png";
        font_size_x = 9;
        font_size_y = 8;
    }
    else if (strcmp(font, "terminus") == 0) {
        font_file = "ansilove_font_pc_terminus.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    else {
        // in all other cases use the standard DOS font
        font_file = "ansilove_font_pc_80x25.png";
        font_size_x = 9;
        font_size_y = 16;
    }
    
    // now set bits to 8 if not already value 8 or 9
    if (strcmp(bits, "8") != 0 && strcmp(bits, "9") != 0) {
        sprintf(bits, "%s", "8");
    }

    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) { 
        fputs("\nFile error.\n\n", stderr); exit (1);
    }
    
    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;
    
    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    size_t result;
    
    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }
    
    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer
    
    // close input file, we don't need it anymore
    rewind(input_file);
    fclose(input_file);
    
    // libgd image pointers
    gdImagePtr im_Binary, im_Backgrnd, im_Font;
            
    // additional libgd related declarations
    FILE *file_Backgrnd, *file_Font;
    char path_Backgrnd[1000] = { 0 };
    char path_Font[1000] = { 0 };
    
    // resolve paths for font and background image
    sprintf(path_Backgrnd, "%sansilove_background.png", ANSILOVE_FONTS_DIRECTORY);
    sprintf(path_Font, "%s%s", ANSILOVE_FONTS_DIRECTORY, font_file);
    
    // open font and background image, allocate libgd image pointers
    file_Backgrnd = fopen(path_Backgrnd, "rb");
    file_Font = fopen(path_Font, "rb");
    
    if (!file_Backgrnd) {
        fputs ("\nCan't open AnsiLove/C background image, aborted.\n\n", stderr); exit (4);
    }
    else {
        im_Backgrnd = gdImageCreateFromPng(file_Backgrnd);
    }
    
    if (!file_Font) {
        fputs ("\nCan't open AnsiLove/C font file, aborted.\n\n", stderr); exit (5);
    }
    else {
        im_Font = gdImageCreateFromPng(file_Font);
    }
    
    // set transparent color index for the font
    gdImageColorTransparent(im_Font, 20);

    // convert numeric command line flags to integer values
    int32_t int_columns = atoi(columns);
    int32_t int_bits = atoi(bits);
    int32_t int_icecolors = atoi(icecolors);
    
    // allocate buffer image memory
    im_Binary = gdImageCreate(int_columns * int_bits, 
                              ((input_file_size / 2) / int_columns * font_size_y));
    
    if (!im_Binary) {
        fputs ("\nError, can't allocate buffer image memory.\n\n", stderr); exit (6);
    }
    
    // allocate black color
    gdImageColorAllocate(im_Binary, 0, 0, 0);
    
    // background / forground color array
    int32_t binary_colors[16];
    
    // define binary colors
    binary_colors[0]  = 0; 
    binary_colors[1]  = 4; 
    binary_colors[2]  = 2; 
    binary_colors[3]  = 6; 
    binary_colors[4]  = 1; 
    binary_colors[5]  = 5; 
    binary_colors[6]  = 3; 
    binary_colors[7]  = 7; 
    binary_colors[8]  = 8; 
    binary_colors[9]  = 12; 
    binary_colors[10] = 10; 
    binary_colors[11] = 14; 
    binary_colors[12] = 9; 
    binary_colors[13] = 13; 
    binary_colors[14] = 11; 
    binary_colors[15] = 15;
    
    // process binary
    int32_t character, attribute, color_background, color_foreground;
    int32_t loop = 0, position_x = 0, position_y = 0;

    while (loop < input_file_size)
    {
        if (position_x == int_columns) 
        {
            position_x = 0;
            position_y++;
        }
        
        character = input_file_buffer[loop];
        attribute = input_file_buffer[loop+1];
        
        color_background = binary_colors[(attribute & 240) >> 4];
        color_foreground = binary_colors[attribute & 15];
        
        if (color_background > 8 && int_icecolors == 0)
        {
            color_background -= 8;
        }
        
        gdImageCopy(im_Binary, im_Backgrnd, position_x * int_bits, 
                    position_y * font_size_y, 
                    color_background * 9, 0, 
                    int_bits, font_size_y);
        
        gdImageCopy(im_Binary, im_Font, position_x * int_bits,
                    position_y * font_size_y, 
                    character * font_size_x, 
                    color_foreground * font_size_y,
                    int_bits, font_size_y);
        
        position_x++;
        loop+=2;
    }
  
    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_Binary, file_Out);
    fclose(file_Out);

    // free memory
    gdImageDestroy(im_Binary);
    gdImageDestroy(im_Backgrnd);
    gdImageDestroy(im_Font);
}

// ADF
void alArtworxLoader(char *input, char output[], char bits[])
{
    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) { 
        fputs("\nFile error.\n\n", stderr); exit (1);
    }
    
    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;
    
    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    size_t result;
    
    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }
    
    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer
    
    // close input file, we don't need it anymore
    rewind(input_file);
    fclose(input_file);
    
    // libgd image pointers
    gdImagePtr im_ADF, im_Backgrnd, im_Font, im_InvertFont;

    // create gd image instances
    im_Backgrnd = gdImageCreate(128, 16);
    im_Font = gdImageCreate(2048, 256);
    im_InvertFont = gdImageCreate(2048, 16);
    
    // error output
    if (!im_Backgrnd) {
        fputs ("\nCan't allocate background buffer image memory.\n\n", stderr); exit (4);
    }
    if (!im_Font) {
        fputs ("\nCan't allocate font buffer image memory.\n\n", stderr); exit (5);
    }
    if (!im_InvertFont) {
        fputs ("\nCan't allocate temporary font buffer image memory.\n\n", stderr); exit (6);
    }
    
    // ADF color palette array
    int32_t adf_colors[16] = { 0, 1, 2, 3, 4, 5, 20, 7, 56, 57, 58, 59, 60, 61, 62, 63 };
    
    // process ADF palette
    int32_t loop;
    int32_t index;
    int32_t colors[21];
    
    for (loop = 0; loop < 16; loop++)
    {
        index = (adf_colors[loop] * 3) + 1;
        colors[loop] = gdImageColorAllocate(im_Backgrnd, (input_file_buffer[index] << 2 | input_file_buffer[index] >> 4), 
                                            (input_file_buffer[index + 1] << 2 | input_file_buffer[index + 1] >> 4), 
                                            (input_file_buffer[index + 2] << 2 | input_file_buffer[index + 2] >> 4));
    }
    gdImagePaletteCopy(im_Font, im_Backgrnd);
    gdImagePaletteCopy(im_InvertFont, im_Backgrnd);
    
    // get and apply RGB values
    int32_t Red = gdImageRed(im_Backgrnd, 0);
    int32_t Green = gdImageGreen(im_Backgrnd, 0);
    int32_t Blue = gdImageBlue(im_Backgrnd, 0);
    
    colors[16] = gdImageColorAllocate(im_Font, Red, Green, Blue);
    colors[20] = gdImageColorAllocate(im_InvertFont, 200, 220, 169);
    
    for (loop = 0; loop < 16; loop++)
    {
        gdImageFilledRectangle(im_Backgrnd, loop << 3, 0, 
                               (loop << 3) + 8, 16, colors[loop]);
    }
    
    // process ADF font
    gdImageFilledRectangle(im_InvertFont, 0, 0, 2048, 16, colors[20]);
    gdImageColorTransparent(im_InvertFont, colors[20]);
    
    int32_t adf_font_size_y, adf_character_line = 0, adf_character_column = 0, loop_column;
    
    for (loop = 0; loop < 256; loop++)
    {
        for (adf_font_size_y = 0; adf_font_size_y < 16; adf_font_size_y++)
        {
            adf_character_line = input_file_buffer[193 + adf_font_size_y + (loop * 16)];
            
            for (loop_column = 0; loop_column < 8; loop_column++)
            {
                adf_character_column = 0x80 >> loop_column;
                
                if ((adf_character_line & adf_character_column) != adf_character_column)
                {
                    gdImageSetPixel(im_InvertFont, (loop * 8) + loop_column, adf_font_size_y, colors[0]);
                }
            }
        }
    }
    
    for (loop = 1; loop < 16; loop++)
    {
        gdImageFilledRectangle(im_Font, 0, loop * 16, 2048,(loop * 16) + 16, colors[loop]);
    }
    gdImageFilledRectangle(im_Font, 0, 0, 2048, 15, colors[16]);
    
    for (loop = 0; loop < 16; loop++)
    {
        gdImageCopy(im_Font, im_InvertFont, 0, loop * 16, 0, 0, 2048, 16);
    }
    gdImageColorTransparent(im_Font, colors[0]);
    
    // create ADF instance
    im_ADF = gdImageCreate(640,(((input_file_size - 192 - 4096 -1) / 2) / 80) * 16);
    
    // error output
    if (!im_ADF) {
        fputs ("\nCan't allocate buffer image memory.\n\n", stderr); exit (7);
    }
    
    gdImageColorAllocate(im_ADF, 0, 0, 0);
       
    // process ADF
    int32_t position_x = 0, position_y = 0; 
    int32_t character, attribute, color_foreground, color_background;
    loop = 192 + 4096 + 1;
    
    while(loop < input_file_size)
    {
        if (position_x == 80)
        {
            position_x = 0;
            position_y++;
        }
        
        character = input_file_buffer[loop];
        attribute = input_file_buffer[loop+1];
        
        color_background = (attribute & 240) >> 4;
        color_foreground = attribute & 15;
        
        gdImageCopy(im_ADF, im_Backgrnd, position_x * 8, position_y * 16, color_background * 8, 0, 8, 16);
        gdImageCopy(im_ADF, im_Font, position_x * 8, position_y * 16, character * 8, color_foreground * 16, 8, 16);
        
        position_x++;
        loop+=2;
    }
    
    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_ADF, file_Out);
    fclose(file_Out);
    
    // nuke garbage
    gdImageDestroy(im_ADF);
    gdImageDestroy(im_Backgrnd);
    gdImageDestroy(im_Font);
    gdImageDestroy(im_InvertFont); 
}

// IDF
void alIcedrawLoader(char *input, char output[], char bits[], bool fileHasSAUCE)
{
    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) { 
        fputs("\nFile error.\n\n", stderr); exit (1);
    }
    
    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;
    
    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    size_t result;
    
    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }
    
    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer
    
    // just like a tape, you know?
    rewind(input_file);

    // IDF related: file contains a SAUCE record? adjust the file size
    if(fileHasSAUCE == true) {
        sauce *saucerec = sauceReadFile(input_file);
        input_file_size -= 128 - ( saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
        rewind(input_file);
    }
    
    // close input file, we don't need it anymore
    fclose(input_file);

    // extract IDF header, four 16-bit little endian unsigned shorts    
    int32_t x1 = (input_file_buffer[5] << 8) + input_file_buffer[4];
    int32_t y1 = (input_file_buffer[7] << 8) + input_file_buffer[6];
    int32_t x2 = (input_file_buffer[9] << 8) + input_file_buffer[8];
    int32_t y2 = (input_file_buffer[11] << 8) + input_file_buffer[10];

    // libgd image pointers
    gdImagePtr im_IDF, im_Backgrnd, im_Font, im_InvertFont;

    // create gd image instances
    im_Backgrnd = gdImageCreate(128, 16);
    im_Font = gdImageCreate(2048, 256);
    im_InvertFont = gdImageCreate(2048, 16);

    // error output
    if (!im_Backgrnd) {
        fputs ("\nCan't allocate background buffer image memory.\n\n", stderr); exit (4);
    }
    if (!im_Font) {
        fputs ("\nCan't allocate font buffer image memory.\n\n", stderr); exit (5);
    }
    if (!im_InvertFont) {
        fputs ("\nCan't allocate temporary font buffer image memory.\n\n", stderr); exit (6);
    }

    // process IDF palette
    int32_t loop;
    int32_t index;
    int32_t colors[21];
    
    for (loop = 0; loop < 16; loop++)
    {
        index = (loop * 3) + input_file_size - 48;
        colors[loop] = gdImageColorAllocate(im_Backgrnd, (input_file_buffer[index] << 2 | input_file_buffer[index] >> 4), 
                                            (input_file_buffer[index + 1] << 2 | input_file_buffer[index + 1] >> 4), 
                                            (input_file_buffer[index + 2] << 2 | input_file_buffer[index + 2] >> 4));
    }
    gdImagePaletteCopy(im_Font, im_Backgrnd);
    gdImagePaletteCopy(im_InvertFont, im_Backgrnd);
    
    // get and apply RGB values
    int32_t Red = gdImageRed(im_Backgrnd, 0);
    int32_t Green = gdImageGreen(im_Backgrnd, 0);
    int32_t Blue = gdImageBlue(im_Backgrnd, 0);
    
    colors[16] = gdImageColorAllocate(im_Font, Red, Green, Blue);
    colors[20] = gdImageColorAllocate(im_InvertFont, 200, 220, 169);
    
    for (loop = 0; loop < 16; loop++)
    {
        gdImageFilledRectangle(im_Backgrnd, loop << 3, 0, 
                               (loop << 3) + 8, 16, colors[loop]);
    }
    
    // process IDF font
    gdImageFilledRectangle(im_InvertFont, 0, 0, 2048, 16, colors[20]);
    gdImageColorTransparent(im_InvertFont, colors[20]);
    
    int32_t idf_font_size_y, idf_character_line = 0, idf_character_column = 0, loop_column;
    
    for (loop = 0; loop < 256; loop++)
    {
        for (idf_font_size_y = 0; idf_font_size_y < 16; idf_font_size_y++)
        {
            idf_character_line = input_file_buffer[input_file_size - 48 - 4096 + idf_font_size_y + (loop * 16)];
            
            for (loop_column = 0; loop_column < 8; loop_column++)
            {
                idf_character_column = 0x80 >> loop_column;
                
                if ((idf_character_line & idf_character_column) != idf_character_column)
                {
                    gdImageSetPixel(im_InvertFont, (loop * 8) + loop_column, idf_font_size_y, colors[0]);
                }
            }
        }
    }
    
    for (loop = 1; loop < 16; loop++)
    {
        gdImageFilledRectangle(im_Font, 0, loop * 16, 2048,(loop * 16) + 16, colors[loop]);
    }
    gdImageFilledRectangle(im_Font, 0, 0, 2048, 15, colors[16]);
    
    for (loop = 0; loop < 16; loop++)
    {
        gdImageCopy(im_Font, im_InvertFont, 0, loop * 16, 0, 0, 2048, 16);
    }
    gdImageColorTransparent(im_Font, colors[0]); 
    
    // process IDF
    loop = 12;
    int32_t idf_sequence_length, idf_sequence_loop, i = 0;
    
    // dynamic IDF buffer
    unsigned char *idf_buffer;

//    idf_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    idf_buffer = (unsigned char *) malloc(16640);
    
    uint16_t idf_data, idf_data_length;

    while (loop < input_file_size - 4096 - 48) 
    {
        memcpy(&idf_data,input_file_buffer+loop,2);
        
        if (idf_data==1) // RLE compressed data
        {
            memcpy(&idf_data_length,input_file_buffer+loop+2,2);
            
            idf_sequence_length = idf_data_length & 255;
            
            for (idf_sequence_loop = 0; idf_sequence_loop < idf_sequence_length; idf_sequence_loop++) 
            {
                idf_buffer[i] = input_file_buffer[loop + 4];
                idf_buffer[i+1] = input_file_buffer[loop + 5];
                i+=2;
            }
            
            loop += 4;
        }
        else { // Normal character
            idf_buffer[i] = input_file_buffer[loop];
            idf_buffer[i+1] = input_file_buffer[loop + 1];
            i+=2;
        }
        loop += 2;
    }
    
    // create IDF instance
    im_IDF = gdImageCreate((x2 + 1) * 8, i / 2 / 80 * 16);
    
    // error output
    if (!im_IDF) {
        fputs ("\nCan't allocate buffer image memory.\n\n", stderr); exit (7);
    }
    gdImageColorAllocate(im_IDF, 0, 0, 0);
    
    // render IDF    
    int32_t position_x = 0, position_y = 0; 
    int32_t character, attribute, color_foreground, color_background;
    
    for (loop = 0; loop < i ; loop +=2) 
    {
        if (position_x == x2 + 1)
        {
            position_x = 0;
            position_y++;
        }
        
        character = idf_buffer[loop];
        attribute = idf_buffer[loop+1];
        
        color_background = (attribute & 240) >> 4;
        color_foreground = attribute & 15;
        
        gdImageCopy(im_IDF, im_Backgrnd, position_x * 8, position_y * 16, color_background * 8, 0, 8, 16);
        gdImageCopy(im_IDF, im_Font, position_x *8, position_y * 16, character * 8, color_foreground * 16, 8, 16);
        
        position_x++;
    }
    
    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_IDF, file_Out);
    fclose(file_Out);
    
    // nuke garbage
    gdImageDestroy(im_IDF);
    gdImageDestroy(im_Backgrnd);
    gdImageDestroy(im_Font);
    gdImageDestroy(im_InvertFont); 
}

//    $loop=12;
//    
//    while ($loop<$input_file_size-4096-48)
//    {
//        $idf_data=unpack('vdata',substr($input_file_buffer,$loop,2));
//        if ($idf_data['data']==1)
//        {
//            $idf_data=unpack('vlength',substr($input_file_buffer,$loop+2,2));
//            
//            $idf_sequence_length=$idf_data['length'] & 255;
//            $idf_data=unpack('Ccharacter/Cattribute',substr($input_file_buffer,$loop+4,2));
//            
//            for ($idf_sequence_loop=0;$idf_sequence_loop<$idf_sequence_length;$idf_sequence_loop++)
//            {
//                $idf_buffer[]=$idf_data['character'];
//                $idf_buffer[]=$idf_data['attribute'];
//            }
//            
//            $loop+=4;
//        }
//        else
//        {
//            $idf_data=unpack('Ccharacter/Cattribute',substr($input_file_buffer,$loop,2));
//            
//            $idf_buffer[]=$idf_data['character'];
//            $idf_buffer[]=$idf_data['attribute'];
//        }
//        
//        $loop+=2;
//    }
//    
//    
//    
//    /*****************************************************************************/
//    /* ALLOCATE IMAGE BUFFER MEMORY                                              */
//    /*****************************************************************************/
//    
//    if (!$idf = imagecreate(($idf_header['x2']+1)*8,(sizeof($idf_buffer)/2/80)*16))
//    {
//        error("Can't allocate buffer image memory");
//    }
//    
//    imagecolorallocate($idf,0,0,0);
//    
//    
//    
//    /*****************************************************************************/
//    /* RENDER IDF                                                                */
//    /*****************************************************************************/
//    
//    for ($loop=0;$loop<sizeof($idf_buffer);$loop+=2)
//    {
//        if ($position_x==$idf_header['x2']+1)
//        {
//            $position_x=0;
//            $position_y++;
//        }
//        
//        $character=$idf_buffer[$loop];
//        $attribute=$idf_buffer[$loop+1];
//        
//        $color_background=($attribute & 240)>>4;
//        $color_foreground=$attribute & 15;
//        
//        imagecopy($idf,$background,$position_x*8,$position_y*16,$color_background*8,0,8,16);
//        imagecopy($idf,$font,$position_x*8,$position_y*16,$character*8,$color_foreground*16,8,16);
//        
//        $position_x++;
//    }
//    
//    
//    
//    /*****************************************************************************/
//    /* CREATE OUTPUT FILE                                                        */
//    /*****************************************************************************/
//    
//    if ($thumbnail)
//    {
//        $position_y_max=$position_y;
//        $columns=80;
//        font_size_y = 16;
//        
//        thumbnail($idf,$output,$columns,font_size_y,$position_y_max);
//    }
//    else
//    {
//        if ($output=='online')
//        {
//            Header("Content-type: image/png");
//            ImagePNG($idf);
//        }
//        else
//        {
//            ImagePNG($idf,$output);
//        }
//    }
//
//
//
///*****************************************************************************/
///* FREE MEMORY                                                               */
///*****************************************************************************/
//
//   imagedestroy($idf);
//   imagedestroy($background);
//   imagedestroy($font);
//   imagedestroy($font_inverted);
//}
//
//
//
///*****************************************************************************/
///* LOAD TUNDRA                                                               */
///*****************************************************************************/
//
//function load_tundra($input,$output,$font,$bits)
//{
//   check_libraries();
//
///*****************************************************************************/
///* CHECK PARAMETERS AND FORCE DEFAULT VALUES IF INVALID INPUT IS DETECTED    */
///*****************************************************************************/
//
//   $columns=80;
//
//   if ($bits=='thumbnail')
//   {
//      $thumbnail=TRUE;
//   }
//   if ($bits!=8 && $bits!=9)
//   {
//      $bits=8;
//   }
//
//   switch($font)
//   {
//   case '80x25':
//      font_file = "ansilove_font_pc_80x25.png';
//      font_size_x = 9;
//      font_size_y = 16;
//      break;
//
//   case '80x50':
//      font_file = "ansilove_font_pc_80x50.png';
//      font_size_x = 9;
//      font_size_y = 8;
//      break;
//
//   default:
//      font_file = "ansilove_font_pc_80x25.png';
//      font_size_x = 9;
//      font_size_y = 16;
//   }
//
//
//
///*****************************************************************************/
///* LOAD INPUT FILE                                                           */
///*****************************************************************************/
//
//   if (!$input_file = fopen($input,'r'))
//   {
//      error("Can't open file $input");
//   }
//
//   $input_file_sauce=load_sauce($input);
//
//   if ($input_file_sauce!=NULL)
//   {
//      $input_file_size=$input_file_sauce['FileSize'];
//   }
//   else
//   {
//      $input_file_size=filesize($input);
//   }
//
//   if (!$input_file_buffer = fread($input_file,$input_file_size))
//   {
//      error("Can't read file $input");
//   }
//
//   fclose($input_file);
//
//
//
///*****************************************************************************/
///* EXTRACT TUNDRA HEADER                                                     */
///*****************************************************************************/
//
//   $tundra_header['value']=$input_file_buffer[0];
//   $tundra_header['string']=substr($input_file_buffer,1,8);
//
//   if (ord($tundra_header['value'])!=24 || $tundra_header['string']!='TUNDRA24')
//   {
//      error("$input is not a TUNDRA file");
//   }
//
//
//
///*****************************************************************************/
///* LOAD BACKGROUND/FONT AND ALLOCATE IMAGE BUFFER MEMORY                     */
///*****************************************************************************/
//
//   if (!$background = imagecreatefrompng(dirname(__FILE__).'/fonts/ansilove_background.png'))
//   {
//      error("Can't open file ansilove_background.png");
//   }
//
//   if (!$font = imagecreatefrompng(dirname(__FILE__).'/fonts/'.font_file))
//   {
//      error("Can't open file font_file");
//   }
//
//   imagecolorset($font,20,0,0,0);
//
//
//
///*****************************************************************************/
///* READ TUNDRA FILE A FIRST TIME TO FIND THE IMAGE SIZE                      */
///*****************************************************************************/
//
//   $loop=9;
//
//   while ($loop<$input_file_size)
//   {
//      if ($position_x==80)
//      {
//         $position_x=0;
//         $position_y++;
//      }
//
//      $character=ord($input_file_buffer[$loop]);
//
//      if ($character==1)
//      {
//         $tundra_position_array=unpack('Nposition_y/Nposition_x',substr($input_file_buffer,$loop+1,8));
//         $position_y=$tundra_position_array['position_y'];
//         $position_x=$tundra_position_array['position_x'];
//
//         $loop+=8;
//      }
//
//      if ($character==2)
//      {
//         $loop+=5;
//      }
//
//      if ($character==4)
//      {
//         $loop+=5;
//      }
//
//      if ($character==6)
//      {
//         $loop+=9;
//      }
//
//      if ($character!=1 && $character!=2 && $character!=4 && $character!=6)
//      {
//         $position_x++;
//      }
//
//      $loop++;
//   }
//
//   $position_y++;
//
//
//
///*****************************************************************************/
///* ALLOCATE IMAGE BUFFER MEMORY                                              */
///*****************************************************************************/
//
//   if (!$tundra = imagecreate($columns*$bits,($position_y)*font_size_y))
//   {
//      error("Can't allocate buffer image memory");
//   }
//
//   imagecolorallocate($tundra,0,0,0);
//
//
//
///*****************************************************************************/
///* PROCESS TUNDRA FILE                                                       */
///*****************************************************************************/
//
//   $position_x=0;
//   $position_y=0;
//
//   $loop=9;
//
//   while ($loop<$input_file_size)
//   {
//      if ($position_x==$columns)
//      {
//         $position_x=0;
//         $position_y++;
//      }
//
//      $character=ord($input_file_buffer[$loop]);
//
//      if ($character==1)
//      {
//         $tundra_position_array=unpack('Nposition_y/Nposition_x',substr($input_file_buffer,$loop+1,8));
//         $position_y=$tundra_position_array['position_y'];
//         $position_x=$tundra_position_array['position_x'];
//
//         $loop+=8;
//      }
//
//      if ($character==2)
//      {
//         $tundra_color_array=unpack('Ncolor_foreground',substr($input_file_buffer,$loop+2,4));
//         $color_foreground=$tundra_color_array['color_foreground'];
//         $red=($color_foreground>>16) & 0x000000FF;
//         $green=($color_foreground>>8) & 0x000000FF;
//         $blue=$color_foreground & 0x000000FF;
//         imagecolorset($font,0,$red,$green,$blue);
//
//         $character=ord($input_file_buffer[$loop+1]);
//
//         $loop+=5;
//      }
//
//
//      if ($character==4)
//      {
//         $tundra_color_array=unpack('Ncolor_background',substr($input_file_buffer,$loop+2,4));
//         $color_background=$tundra_color_array['color_background'];
//         $red=($color_background>>16) & 0x000000FF;
//         $green=($color_background>>8) & 0x000000FF;
//         $blue=$color_background & 0x000000FF;
//         imagecolorset($font,20,$red,$green,$blue);
//
//         $character=ord($input_file_buffer[$loop+1]);
//
//         $loop+=5;
//      }
//
//      if ($character==6)
//      {
//         $tundra_color_array=unpack('Ncolor_foreground/Ncolor_background',substr($input_file_buffer,$loop+2,8));
//         $color_foreground=$tundra_color_array['color_foreground'];
//         $red=($color_foreground>>16) & 0x000000FF;
//         $green=($color_foreground>>8) & 0x000000FF;
//         $blue=$color_foreground & 0x000000FF;
//         imagecolorset($font,0,$red,$green,$blue);
//
//         $color_background=$tundra_color_array['color_background'];
//         $red=($color_background>>16) & 0x000000FF;
//         $green=($color_background>>8) & 0x000000FF;
//         $blue=$color_background & 0x000000FF;
//         imagecolorset($font,20,$red,$green,$blue);
//
//         $character=ord($input_file_buffer[$loop+1]);
//
//         $loop+=9;
//      }
//
//      if ($character!=1 && $character!=2 && $character!=4 && $character!=6)
//      {
//         imagecopy($tundra,$font,$position_x*$bits,$position_y*font_size_y,$character*font_size_x,0,$bits,font_size_y);
//
//         $position_x++;
//      }
//
//      $loop++;
//   }
//
//
//
///*****************************************************************************/
///* CREATE OUTPUT FILE                                                        */
///*****************************************************************************/
//
//   if ($thumbnail)
//   {
//      $position_y_max=$position_y;
//
//      thumbnail($tundra,$output,$columns,font_size_y,$position_y_max);
//   }
//   else
//   {
//      if ($output=='online')
//      {
//         Header("Content-type: image/png");
//         ImagePNG($tundra);
//      }
//      else
//      {
//         ImagePNG($tundra,$output);
//      }
//   }
//
//
//
///*****************************************************************************/
///* FREE MEMORY                                                               */
///*****************************************************************************/
//
//   imagedestroy($tundra);
//   imagedestroy($background);
//   imagedestroy($font);
//}

// XBin
void alXbinLoader(char *input, char output[], char bits[])
{
    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) { 
        fputs("\nFile error.\n\n", stderr); exit (1);
    }
    
    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;
    
    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    size_t result;
    
    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }
    
    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer
    
    // close input file, we don't need it anymore
    rewind(input_file);
    fclose(input_file);

    if (strcmp(strndup((char *)input_file_buffer, 5), "XBIN\x1a") != 0) {
        fputs("\nNot an XBin.\n\n", stderr); exit (4);
    }

    int32_t xbin_width = (input_file_buffer[ 6 ] << 8) + input_file_buffer[ 5 ];
    int32_t xbin_height = (input_file_buffer[ 8 ] << 8) + input_file_buffer[ 7 ];
    int32_t xbin_fontsize = input_file_buffer[ 9 ];
    int32_t xbin_flags = input_file_buffer[ 10 ];

    fputs("\nXBin OK!\n\n", stderr); exit (0);
}

//   check_libraries();
//
//   if ($bits=='thumbnail')
//   {
//      $thumbnail=TRUE;
//   }
//
///*****************************************************************************/
///* LOAD INPUT FILE                                                           */
///*****************************************************************************/
//
//   if (!$input_file = fopen($input,'r'))
//   {
//      error("Can't open file $input");
//   }
//
//   $input_file_sauce=load_sauce($input);
//
//   if ($input_file_sauce!=NULL)
//   {
//      $input_file_size=$input_file_sauce['FileSize'];
//   }
//   else
//   {
//      $input_file_size=filesize($input);
//   }
//
//   if (!$input_file_buffer = fread($input_file,$input_file_size))
//   {
//      error("Can't read file $input");
//   }
//
//   fclose($input_file);
//
//
//
///*****************************************************************************/
///* EXTRACT XBIN HEADER                                                       */
///*****************************************************************************/
//
//   $xbin_header['ID']=substr($input_file_buffer,0,4);
//
//   if ($xbin_header['ID']!='XBIN')
//   {
//      error("$input is not a XBiN file");
//   }
//
//   $xbin_header=array_merge($xbin_header,unpack('CEofChar/vWidth/vHeight/CFontsize/CFlags',substr($input_file_buffer,4,7)));
//
//   if (($xbin_header['Flags'] & 1)==1)
//   {
//      $xbin_flags['palette']=1;
//   }
//
//   if (($xbin_header['Flags'] & 2)==2)
//   {
//      $xbin_flags['font']=1;
//   }
//
//   if (($xbin_header['Flags'] & 4)==4)
//   {
//      $xbin_flags['compress']=1;
//   }
//
//   if (($xbin_header['Flags'] & 8)==8)
//   {
//      $xbin_flags['nonblink']=1;
//   }
//
//   if (($xbin_header['Flags'] & 16)==16)
//   {
//      $xbin_flags['512chars']=1;
//   }
//
//
//
///*****************************************************************************/
///* PROCESS XBIN PALETTE                                                      */
///*****************************************************************************/
//
//   if ($xbin_flags['palette']==1)
//   {
//      if (!$background = imagecreate(128,16))
//      {
//         error("Can't allocate background buffer image memory");
//      }
//
//      for ($loop=0;$loop<16;$loop++)
//      {
//         $index=($loop*3)+11;
//         $colors[$loop]=imagecolorallocate($background,(ord($input_file_buffer[$index])<<2 | ord($input_file_buffer[$index])>>4),(ord($input_file_buffer[$index+1])<<2 | ord($input_file_buffer[$index+1])>>4),(ord($input_file_buffer[$index+2])<<2 | ord($input_file_buffer[$index+2])>>4));
//      }
//
//      for ($loop=0;$loop<16;$loop++)
//      {
//         imagefilledrectangle($background,$loop<<3,0,($loop<<3)+8,16,$colors[$loop]);
//      }
//
//      $background_size_x=8;
//   }
//   else
//   {
//      if (!$background = imagecreatefrompng(dirname(__FILE__).'/fonts/ansilove_background.png'))
//      {
//         error("Can't open file ansilove_background.png");
//      }
//
//      $background_size_x=9;
//   }
//
//
//
///*****************************************************************************/
///* PROCESS XBIN FONT                                                         */
///*****************************************************************************/
//
//   if ($xbin_flags['font']==1)
//   {
//      if (!$font = imagecreate(2048,$xbin_header['Fontsize']*16))
//      {
//         error("Can't allocate font buffer image memory");
//      }
//
//      if (!$font_inverted = imagecreate(2048,$xbin_header['Fontsize']))
//      {
//         error("Can't allocate temporary font buffer image memory");
//      }
//
//      imagepalettecopy($font,$background);
//      imagepalettecopy($font_inverted,$background);
//
//      $color_index=imagecolorsforindex($background,0);
//      $colors[16]=imagecolorallocate($font,$color_index['red'],$color_index['green'],$color_index['blue']);
//      $colors[20]=imagecolorallocate($font_inverted,200,220,169);
//
//      imagefilledrectangle($font_inverted,0,0,2048,$xbin_header['Fontsize'],$colors[20]);
//      imagecolortransparent($font_inverted,$colors[20]);
//
//      for ($loop=0;$loop<256;$loop++)
//      {
//         for ($xbin_font_size_y = 0;$xbin_font_size_y<$xbin_header['Fontsize'];$xbin_font_size_y++)
//         {
//            $xbin_character_line=ord($input_file_buffer[11+$xbin_flags['palette']*48+$xbin_font_size_y+($loop*$xbin_header['Fontsize'])]);
//
//            for ($loop_column=0;$loop_column<8;$loop_column++)
//            {
//               $xbin_character_column=128/pow(2,$loop_column);
//
//               if (($xbin_character_line & $xbin_character_column)!=$xbin_character_column)
//               {
//                  imagesetpixel($font_inverted,($loop*8)+$loop_column,$xbin_font_size_y,$colors[0]);
//               }
//            }
//         }
//      }
//
//      for ($loop=1;$loop<16;$loop++)
//      {
//         imagefilledrectangle($font,0,$loop*$xbin_header['Fontsize'],2048,($loop*$xbin_header['Fontsize'])+$xbin_header['Fontsize'],$loop);
//      }
//      imagefilledrectangle($font,0,0,2048,$xbin_header['Fontsize']-1,$colors[16]);
//
//      for ($loop=0;$loop<16;$loop++)
//      {
//         imagecopy ($font, $font_inverted, 0,$loop*$xbin_header['Fontsize'],0,0,2048,$xbin_header['Fontsize']);
//      }
//      imagecolortransparent($font,$colors[0]);
//
//      font_size_x = 8;
//      font_size_y = $xbin_header['Fontsize'];
//   }
//   else
//   {
//      if (!$font = imagecreatefrompng (dirname(__FILE__).'/fonts/ansilove_font_pc_80x25.png'))
//      {
//         error("Can't open file font_file");
//      }
//
//      font_size_x = 9;
//      font_size_y = 16;
//
//      imagecolortransparent($font,20);
//   }
//
//
//
///*****************************************************************************/
///* PROCESS XBIN                                                              */
///*****************************************************************************/
//
//   $loop=11+$xbin_flags['palette']*48+$xbin_flags['font']*256*$xbin_header['Fontsize'];
//
//   if ($xbin_flags['compress']==1)
//   {
//      while ($loop<$input_file_size)
//      {
//         $character=ord($input_file_buffer[$loop]);
//
//         $compression=$character & 192;
//         $repeat=1+($character & 63);
//
//         if ($compression==0)
//         {
//            for ($i=0;$i<$repeat*2;$i++)
//            {
//               $xbin_buffer[]=ord($input_file_buffer[$loop+1+$i]);
//            }
//
//            $loop=$loop+1+($repeat*2);
//         }
//
//         if ($compression==64)
//         {
//            for ($i=0;$i<$repeat;$i++)
//            {
//               $xbin_buffer[]=ord($input_file_buffer[$loop+1]);
//               $xbin_buffer[]=ord($input_file_buffer[$loop+2+$i]);
//            }
//
//            $loop=$loop+2+$repeat;
//         }
//
//         if ($compression==128)
//         {
//            for ($i=0;$i<$repeat;$i++)
//            {
//               $xbin_buffer[]=ord($input_file_buffer[$loop+2+$i]);
//               $xbin_buffer[]=ord($input_file_buffer[$loop+1]);
//            }
//
//            $loop=$loop+2+$repeat;
//         }
//
//         if ($compression==192)
//         {
//            for ($i=0;$i<$repeat;$i++)
//            {
//               $xbin_buffer[]=ord($input_file_buffer[$loop+1]);
//               $xbin_buffer[]=ord($input_file_buffer[$loop+2]);
//            }
//
//            $loop+=3;
//         }
//      }
//   }
//   else
//   {
//      while ($loop<$input_file_size)
//      {
//         $xbin_buffer[]=ord($input_file_buffer[$loop]);
//         $loop++;
//      }
//   }
//
//
//
///*****************************************************************************/
///* ALLOCATE IMAGE BUFFER MEMORY                                              */
///*****************************************************************************/
//
//   if (!$xbin = imagecreatetruecolor($xbin_header['Width']*8,$xbin_header['Height']*font_size_y))
//   {
//      error("Can't allocate buffer image memory");
//   }
//
//   imagecolorallocate($xbin,0,0,0);
//
//
//
///*****************************************************************************/
///* RENDER XBIN                                                               */
///*****************************************************************************/
//
//   for ($loop=0;$loop<sizeof($xbin_buffer);$loop+=2)
//   {
//      if ($position_x==$xbin_header['Width'])
//      {
//         $position_x=0;
//         $position_y++;
//      }
//
//      $character=($xbin_buffer[$loop]);
//      $attribute=($xbin_buffer[$loop+1]);
//
//      $color_background=($attribute & 240)>>4;
//      $color_foreground=$attribute & 15;
//
//      imagecopy($xbin, $background,$position_x*8,$position_y*font_size_y,$color_background*$background_size_x,0,8,font_size_y);
//      imagecopy($xbin,$font,$position_x*8,$position_y*font_size_y,$character*font_size_x,$color_foreground*font_size_y,8,font_size_y);
//
//      $position_x++;
//   }
//
//
//
///*****************************************************************************/
///* CREATE OUTPUT FILE                                                        */
///*****************************************************************************/
//
//   if ($thumbnail)
//   {
//      $position_y_max=$xbin_header['Height'];
//      $columns=$xbin_header['Width'];
//
//      thumbnail($xbin,$output,$columns,font_size_y,$position_y_max);
//   }
//   else
//   {
//      if ($output=='online')
//      {
//         Header("Content-type: image/png");
//         ImagePNG($xbin);
//      }
//      else
//      {
//         ImagePNG($xbin,$output);
//      }
//   }
//
///*****************************************************************************/
///* FREE MEMORY                                                               */
///*****************************************************************************/
//
//   imagedestroy($xbin);
//   imagedestroy($background);
//   imagedestroy($font);
//
//   if ($xbin_flags['font']==1)
//   {
//      imagedestroy($font_inverted);
//   }
//}

// Reads SAUCE via a filename.
sauce *sauceReadFileName(char *fileName) 
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }
    
    sauce *record = sauceReadFile(file);
    fclose(file);
    return record;
}

// Read SAUCE via a FILE pointer.
sauce *sauceReadFile(FILE *file) 
{
    sauce *record;
    record = malloc(sizeof *record);
    
    if (record != NULL) {
        readRecord(file, record);
    }
    return record;
}

void readRecord(FILE *file, sauce *record) 
{
    if (fseek(file, 0 - RECORD_SIZE, SEEK_END) != EXIT_SUCCESS) {
        free(record);
        return;
    }
    
    size_t read_status = fread(record->ID, sizeof(record->ID) - 1, 1, file);
    record->ID[sizeof(record->ID) - 1] = '\0';
    
    if (read_status != 1 || strcmp(record->ID, SAUCE_ID) != 0) {
        free(record);
        return;
    }
    fread(record->version, sizeof(record->version) - 1, 1, file);
    record->version[sizeof(record->version) - 1] = '\0';
    fread(record->title, sizeof(record->title) - 1, 1, file);    
    record->title[sizeof(record->title) - 1] = '\0';
    fread(record->author, sizeof(record->author) - 1, 1, file);
    record->author[sizeof(record->author) - 1] = '\0';
    fread(record->group, sizeof(record->group) - 1, 1, file);    
    record->group[sizeof(record->group) - 1] = '\0';
    fread(record->date, sizeof(record->date) - 1, 1, file);
    record->date[sizeof(record->date) - 1] = '\0';
    fread(&(record->fileSize), sizeof(record->fileSize), 1, file);    
    fread(&(record->dataType), sizeof(record->dataType), 1, file);    
    fread(&(record->fileType), sizeof(record->fileType), 1, file);
    fread(&(record->tinfo1), sizeof(record->tinfo1), 1, file);
    fread(&(record->tinfo2), sizeof(record->tinfo2), 1, file);
    fread(&(record->tinfo3), sizeof(record->tinfo3), 1, file);
    fread(&(record->tinfo4), sizeof(record->tinfo4), 1, file);
    fread(&(record->comments), sizeof(record->comments), 1, file);
    fread(&(record->flags), sizeof(record->flags), 1, file);
    fread(record->filler, sizeof(record->filler) - 1, 1, file);
    record->filler[sizeof(record->filler) - 1] = '\0';
    
    if (ferror(file) != EXIT_SUCCESS) {
        free(record);
        return;
    }
    
    if (record->comments > 0) {
        record->comment_lines = malloc(record->comments *sizeof(*record->comment_lines));
        
        if (record->comment_lines != NULL) {
            readComments(file, record->comment_lines, record->comments);
        }
        else {
            free(record);
            return;
        }
    }
}

void readComments(FILE *file, char **comment_lines, int32_t comments) 
{
    int32_t i;
    
    if (fseek(file, 0 - (RECORD_SIZE + 5 + COMMENT_SIZE *comments), SEEK_END) == EXIT_SUCCESS) {
        char ID[6];
        fread(ID, sizeof(ID) - 1, 1, file);
        ID[sizeof(ID) - 1] = '\0';
        
        if (strcmp(ID, COMMENT_ID) != 0) {
            free(comment_lines);
            return;
        }
        
        for (i = 0; i < comments; i++) {
            char buf[COMMENT_SIZE + 1] = "";
            
            fread(buf, COMMENT_SIZE, 1, file);
            buf[COMMENT_SIZE] = '\0';
            
            if (ferror(file) == EXIT_SUCCESS) {
                comment_lines[i] = strdup(buf);
                if (comment_lines[i] == NULL) {
                    free(comment_lines);
                    return;
                }
            }
            else {
                free(comment_lines);
                return;
            }
        }
        return;
    }    
    free(comment_lines);
    return;
}
