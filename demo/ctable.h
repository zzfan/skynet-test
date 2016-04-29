/*******************************************************************************

 File Name: ctable.h
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月27日 星期三 21时37分36秒

*******************************************************************************/

#ifndef __CTABLE_H__
#define __CTABLE_H__

#include <linux/types.h>
#include <net/sock.h>

#include "proto.h"

//label -> sock 映射表

struct sock_bucket {
	struct hlist_node node;
	struct sock* sk;
};

struct sock_chain {
	struct hlist_node node;
	__u8 label[LABEL_SIZE];

	struct hlist_nulls_head head; // -> sock_bucket
};

struct hslot {
	struct hlist_nulls_head head; // -> sock_chain
	int count;
	spinlock_t lock;
};

struct content_table {
	struct hslot *hash;
	struct hslot *hash2; //参考UDP的二级hash表
	unsigned int mask;
};

extern struct content_table content_table;

int content_hashfn(struct net* net, __u8* label, unsigned int mask);

void content_table_init(struct content_table* table, const char* name);
void content_table_fini(struct content_table* table);

void content_table_insert(struct content_table* table, __u8* label, struct sock* sk);
struct sock_chain* content_table_search(struct content_table* table, __u8* label);
void content_table_erase(struct content_table* table, struct sock* sk);

#endif
