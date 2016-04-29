/*******************************************************************************

 File Name: trans_ack.c
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月28日 星期四 10时59分01秒

*******************************************************************************/

#include "trans_ack.h"


int xmit_hsyn(struct content_sock* sk, struct content_chunk* chunk)
{
	return 0;
}

int xmit_ack(struct content_sock* sk, struct content_chunk* chunk)
{
	return 0;
}

int xmit_reject(struct content_sock* sk, struct content_chunk* chunk)
{
	return 0;
}

int xmit_needmore(struct content_sock* sk, struct content_chunk* chunk)
{
	return 0;
}
