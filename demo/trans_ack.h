/*******************************************************************************

 File Name: trans_ack.h
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月28日 星期四 10时58分59秒

*******************************************************************************/

#ifndef __TRANS_ACK_H__
#define __TRANS_ACK_H__

#include "csock.h"

int xmit_hsyn(struct content_sock* sk, struct content_chunk* chunk);

int xmit_ack(struct content_sock* sk, struct content_chunk* chunk);

int xmit_reject(struct content_sock* sk, struct content_chunk* chunk);

int xmit_needmore(struct content_sock* sk, struct content_chunk* chunk);

#endif
