/*******************************************************************************

 File Name: csock.h
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月28日 星期四 08时56分32秒

*******************************************************************************/

#ifndef __CSOCK_H__
#define __CSOCK_H__

#include <linux/types.h>
#include <linux/timer.h>
#include <net/inet_sock.h>

struct content_chunk {
	struct hlist_node node;
	struct timer_list timer;  //发送方Hsyn定时器 or 接收方free/time_wait定时器
	size_t count;
	struct sk_buff* array[];
};

enum chunk_type {
	CHUNK_SEND,
	CHUNK_RECV,
};

struct content_chunk* content_chunk_alloc(size_t count, enum chunk_type t);

void content_chunk_free(struct content_chunk* chunk);

//hsyn 定时器触发
void hsyn_timer_emit(unsigned long chunk);

//free 定时器触发
void free_timer_emit(unsigned long chunk);

//time_wait 定时器触发
void time_wait_timer_emit(unsigned long chunk);


struct content_sock {
	struct inet_sock inet;
	
	struct hlist_nulls_head* rbuf; // -> recv_content_chunk
	size_t rbuf_len;
	size_t rbuf_num;
	
	struct hlist_nulls_head* wbuf; // -> send_content_chunk 
	size_t wbuf_len;
	size_t wbuf_num;
	
	int FP; // getsockopt/setsockopt ->是否逐条确认?
};

static inline struct content_sock* csock(struct sock* sk)
{
	return (struct content_sock*)sk;
}

int csock_init(struct sock* sk);
void csock_fini(struct sock* sk, long timeout);

unsigned char send_data_packet(const struct in6_addr sip, const struct in6_addr dip,
                                      const unsigned char* label, const unsigned char label_len,
                                      const unsigned char* buffer, const unsigned int size);

int csock_sendmsg(struct content_sock* sk, struct msghdr* msg,
				  size_t len, struct cmsghdr* cmsg);

int csock_recvmsg(struct content_sock* sk, struct msghdr* msg,
				  size_t len, int noblock, int flags, int *addr_len);

int csock_rcv_skb(struct content_sock* sk, struct sk_buff* skb);

int csock_setsockopt(struct sock* sk, int level, int optname,
					 char __user *optval, unsigned int optlen);

int csock_getsockopt(struct sock* sk, int level, int optname,
					 char __user *optval, int __user *optlen);

#endif
