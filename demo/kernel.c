/*******************************************************************************

 File Name: kernel.c
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月20日 星期三 14时01分32秒

*******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/ipv6.h>

#include <net/inet_common.h>
#include <net/ipv6.h>
#include <net/sock.h>
#include <net/protocol.h>

#include "ctable.h"
#include "csock.h"

MODULE_AUTHOR("lsp");
MODULE_LICENSE("LGPL");

static int content_rcv(struct sk_buff* skb)
{
	struct sock_chain* chain;
	struct content_sock* sk = NULL;
	__u8* label = NULL;
	printk(KERN_INFO "recv content skb\n");
	//checksum
	//label = skb->...
	chain = content_table_search(&content_table, label);
	//foreach sk in chain
	return csock_rcv_skb(sk, skb);
}

static struct inet6_protocol content_protocol = {
	.handler = content_rcv,
};

static int content_sendmsg(struct sock* sk, struct msghdr* msg,
						   size_t len)
{
	struct cmsghdr* cmsg = CMSG_FIRSTHDR(msg);
	if (!cmsg) {
		return -EOPNOTSUPP;
	}

	return csock_sendmsg(csock(sk), msg, len, cmsg);
}

static int content_recvmsg(struct sock* sk, struct msghdr* msg,
						   size_t len, int noblock, int flags, int *addr_len)
{
	struct cmsghdr* cmsg = CMSG_FIRSTHDR(msg);
	if (!cmsg) {
		return -EOPNOTSUPP;
	}

	return csock_recvmsg(csock(sk), msg, len, noblock, flags, addr_len);
}

static void content_hash(struct sock* sk)
{
	BUG();
}

static void content_unhash(struct sock* sk)
{
	printk(KERN_DEBUG "content_unhash\n");
}

static struct proto content_proto = {
	.name = "CONTENT",
	.owner = THIS_MODULE,
	.init = csock_init,
	.close = csock_fini,
	.connect = NULL,
	.disconnect = NULL,
	.ioctl = NULL,
	.destroy = NULL,
	.setsockopt = csock_setsockopt,
	.getsockopt = csock_getsockopt,
	.sendmsg = content_sendmsg,
	.recvmsg = content_recvmsg,
	.backlog_rcv = NULL,
	.no_autobind = 1,
	.hash = content_hash,
	.unhash = content_unhash,
	.rehash = NULL,
	.get_port = NULL,
	.memory_allocated = NULL,
	.sysctl_mem = NULL,
	.sysctl_rmem = NULL,
	.sysctl_wmem = NULL,
	.obj_size = sizeof(struct sock),
	.slab_flags = SLAB_DESTROY_BY_RCU,
	.h.hashinfo = (struct inet_hashinfo*)&content_table,
};

static struct proto_ops content_dgram_ops = {
	.family = PF_INET6,
	.owner = THIS_MODULE,
	.release	   = inet6_release,   //--> proto.close
	.bind		   = sock_no_bind,
	.connect	   = sock_no_connect,	/* ok		*/
	.socketpair	   = sock_no_socketpair,	/* a do nothing	*/
	.accept		   = sock_no_accept,		/* a do nothing	*/
	.getname	   = inet6_getname,
	.poll		   = sock_no_poll,			/* ok		*/
	.ioctl		   = inet6_ioctl,		/* must change  */
	.listen		   = sock_no_listen,		/* ok		*/
	.shutdown	   = inet_shutdown,		/* ok		*/
	.setsockopt	   = sock_common_setsockopt,	/* ok		*/
	.getsockopt	   = sock_common_getsockopt,	/* ok		*/
	.sendmsg	   = inet_sendmsg,		/* ok		*/
	.recvmsg	   = inet_recvmsg,		/* ok		*/
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
};

static struct inet_protosw content_protosw = {
	.type = SOCK_DGRAM,
	.protocol = IPPROTO_CONTENT,
	.prot = &content_proto,
	.ops = &content_dgram_ops,
};


static int __init content_sock_init(void)
{
	int ret;
	ret = proto_register(&content_proto, 1);
	if (ret) {
		return ret;
	}
	ret = inet6_add_protocol(&content_protocol, IPPROTO_CONTENT);
	if (ret) {
		goto unregister_proto;
	}
	ret = inet6_register_protosw(&content_protosw);
	if (ret) {
		goto del_protocol;
	}
	content_table_init(&content_table, "CONTENT");
	return ret;
	
 del_protocol:
	inet6_del_protocol(&content_protocol, IPPROTO_CONTENT);
 unregister_proto:
	proto_unregister(&content_proto);
	return ret;
}

static void __exit content_sock_exit(void)
{
	proto_unregister(&content_proto);
	inet6_unregister_protosw(&content_protosw);
	inet6_del_protocol(&content_protocol, IPPROTO_CONTENT);
}

module_init(content_sock_init);
module_exit(content_sock_exit);
