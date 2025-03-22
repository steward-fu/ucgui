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
File        : GUI_X.C
Purpose     : COnfig / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef unsigned int U32;

/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime
*                 GUI_X_Delay

  Some timing dependent routines of emWin require a GetTime
  and delay funtion. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime(void) {
  struct timeval tv;
  int            tm;
  gettimeofday(&tv, NULL);
  tm = tv.tv_usec/1024 + tv.tv_sec*1024;
  return tm;
}

void GUI_X_Delay(int Period) {
  while(Period--){
    usleep(1000);
  }
  return;
}

/*********************************************************************
*
*       GUI_X_ExecIdle()
*/

void GUI_X_ExecIdle(void) {
  usleep(1000);
  return;
}


/*********************************************************************
*
*      Multitasking:
*
*                 GUI_X_InitOS()
*                 GUI_X_GetTaskId()
*                 GUI_X_Lock()
*                 GUI_X_Unlock()

Note:
  The following routines are required only if emWin is used in a
  true multi task environment, which means you have more than one
  thread using the emWin API.
  In this case the
                      #define GUI_OS 1
  needs to be in GUIConf.h
*/

U32  GUI_X_GetTaskId(void) { 
  pthread_t   id;
  id = pthread_self();
  return (*(U32*)&id);
}

void GUI_X_InitOS(void)    { 
  return;
}

void GUI_X_Unlock(void)    { 
  pthread_mutex_unlock(&mutex);
  return;
}

void GUI_X_Lock(void)      {
  pthread_mutex_lock(&mutex);
  return;
}

/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*     If not required, leave this routine blank.
*/

void GUI_X_Init(void) {}
void GUI_X_Log(const char *s) {}
void GUI_X_Warn(const char *s) {}
void GUI_X_ErrorOut(const char *s) {}





