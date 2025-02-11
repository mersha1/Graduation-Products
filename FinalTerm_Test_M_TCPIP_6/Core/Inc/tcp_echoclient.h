/**
  ******************************************************************************
  * @file    LwIP/LwIP_TCP_Echo_Client/Inc/tcp_echoclient.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    31-July-2015 
  * @brief   Header file for tcp_echoclient.c
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TCP_ECHOCLIENT_H__
#define __TCP_ECHOCLIENT_H__


void tcp_echoclient_connect(void);
void key_send(int);

#endif /* __TCP_ECHOCLIENT_H__ */

extern int message_flag;
extern int mfront, mback, mleft, mright, mstop;
extern int mEmer;
extern int mStep_onoff;
extern int mStep_dir;


