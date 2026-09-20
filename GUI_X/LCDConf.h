/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDConf_1375_C8_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

#define LCD_CONTROLLER      43480472    //4.3 480x272
#define LCD_BITSPERPIXEL    (16)

#if defined(UT) || defined(UIDBG)
#define LCD_XSIZE           (640)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE           (480)   /* Y-resolution of LCD, Logical coor. */
#else
#define LCD_XSIZE           (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE           (240)   /* Y-resolution of LCD, Logical coor. */
#endif

#define LCD_SWAP_XY         (0)
#define LCD_SWAP_RB         (1)


#endif /* LCDCONF_H */

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
