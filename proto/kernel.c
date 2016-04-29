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
#include <net/udp.h>
#include <net/sock.h>
#include <net/protocol.h>

MODULE_AUTHOR("lsp");
MODULE_LICENSE("LGPL");

#define IPPROTO_CONTENT 55

static int content_rcv(struct sk_buff* skb)
{
	printk(KERN_INFO "recv content skb\n");
	return 0;
}

static struct inet6_protocol content_protocol = {
	.handler = content_rcv,
};

static struct proto content_proto = {
	.name = "CONTENT",
	.owner = THIS_MODULE,
	.obj_size = sizeof(struct sock),
	.slab_flags = SLAB_DESTROY_BY_RCU,
	.close = udp_lib_close,
	.hash = udp_lib_hash,
	.unhash = udp_lib_unhash,
};

static struct proto_ops fake_inet6_dgram_ops = {
	.family = PF_INET6,
	.owner = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = inet6_bind,
	.connect	   = inet_dgram_connect,	/* ok		*/
	.socketpair	   = sock_no_socketpair,	/* a do nothing	*/
	.accept		   = sock_no_accept,		/* a do nothing	*/
	.getname	   = inet6_getname,
	//.poll		   = udp_poll,			/* ok		*/
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
	.ops = &fake_inet6_dgram_ops,
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
	return ret;

 unregister_proto:
	proto_unregister(&content_proto);
 del_protocol:
	inet6_del_protocol(&content_protocol, IPPROTO_CONTENT);
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
