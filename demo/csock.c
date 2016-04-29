/*******************************************************************************

 File Name: csock.c
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月28日 星期四 08时56分34秒

*******************************************************************************/

#include "proto.h"
#include "csock.h"

#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/init.h>
#include <linux/in6.h>
#include <linux/ipv6.h>
#include <linux/ipv6_route.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/skbuff.h>
#include <net/dst.h>
#include <net/ipv6.h>
#include <net/ip6_route.h>

#define LINK_LEN 16
#define IPv6_HEAD_LEN 40
#define CACHE_HEAD_CODE 55
#define EX_IP_LEN 48
#define LABEL_LEN 40
#define CHUNK_SIZE 10

/*
int msg_to_skb(struct msghdr* msg, struct sk_buff* skb, size_t offset)
{

	return 0;
}
*/

struct content_chunk* content_chunk_alloc(size_t count, enum chunk_type t)
{
	struct content_chunk* chunk = NULL;

	return chunk;
}

void content_chunk_free(struct content_chunk* chunk)
{

}

void hsyn_timer_emit(unsigned long chunk)
{

}

void free_timer_emit(unsigned long chunk)
{

}

void time_wait_timer_emit(unsigned long chunk)
{

}


int csock_init(struct sock* sk)
{
	//init hashtable
	return 0;
}

void csock_fini(struct sock* sk, long timeout)
{
	//struct content_sock* csk = csock(sk);
	//fini hashtable
	sk_common_release(sk);
}

//git from heshao demo
unsigned char send_data_packet(const struct in6_addr sip, const struct in6_addr dip,
        const unsigned char* label, const unsigned char label_len,
        const unsigned char* buffer, const unsigned int size)
{
    struct sk_buff* skb = NULL;
    struct net_device* dev = NULL;
    struct ethhdr* ethdr = NULL;
    struct ipv6hdr* iph = NULL;
    u_char* pexhdr = NULL;
    u_char* pdata = NULL;

    unsigned char nret = 1;

    //alloc new skb for new data packet
    skb = alloc_skb(sizeof(struct ipv6hdr) + LINK_LEN + size + EX_IP_LEN, GFP_ATOMIC);
    if(NULL == skb)
        goto out;

    //set skb
    skb_reserve(skb,LINK_LEN);
    skb->pkt_type = PACKET_OTHERHOST;
    skb->protocol = __constant_htons(ETH_P_IPV6);
    skb->ip_summed = CHECKSUM_NONE;
    skb->priority = 0;

    //set ip header pointer
    //network hedaer = skb->data + 0
    skb_set_network_header(skb,0);
    //change tail and len pointer
    skb_put(skb,sizeof(struct ipv6hdr));

    //set ipv6 ex header poniter
    pexhdr = skb->data + sizeof(struct ipv6hdr);
    skb_put(skb, EX_IP_LEN);

    //set data pointer
    pdata = pexhdr + EX_IP_LEN;
    skb_put(skb, size);

    {
        //set data content
        if(NULL!=buffer)
            memcpy(pdata,buffer,size);
    }

    {
        //set ex ipv6 header content
        if(NULL==label)
            goto out;
        pexhdr[0] = 59;
        pexhdr[1] = 1;
        memcpy(&(pexhdr[2]),label,label_len);
    }

    {
        //set ipv6 header content
        iph = ipv6_hdr(skb);
        iph->version = 6;
        iph->priority = 0;
        memset(iph->flow_lbl,0,3);
        iph->payload_len = htons(CHUNK_SIZE + EX_IP_LEN);
        iph->nexthdr = CACHE_HEAD_CODE;
        iph->hop_limit = 255;
        iph->saddr = sip;
        iph->daddr = dip;
    }

    {
        //set mac header content
        ethdr = (struct ethhdr*)skb_push(skb,14);
        ethdr->h_proto = __constant_htons(ETH_P_IPV6);
    }

    //put into route table
    if(skb_dst(skb) == NULL)
    {
        struct dst_entry* route = NULL;
        struct flowi6 fl6 = 
        {
            .daddr = iph->daddr,
            .saddr = iph->saddr,
        };
        route = ip6_route_output(&init_net,NULL,&fl6);
        skb_dst_set(skb,route);
        skb->dev = route->dev;
    }

    //send the skb
    if(0 > dst_output(skb))
        goto out;
    nret = 0;

out:
    if(0 != nret && NULL !=skb)
    {
        dev_put(dev);
        kfree_skb(skb);
    }
    return nret;
}


//TODO: 如何实现调用阻塞...
int csock_sendmsg(struct content_sock* sk, struct msghdr* msg,
				  size_t len, struct cmsghdr* cmsg)
{
	int ret = 0;
	switch(cmsg->cmsg_type) {
	case CONTENT_REQ:
		{
            struct in6_addr daddr, saddr;
            daddr = *((struct in6_addr*)((*msg).msg_name));
            memset(&saddr, 0, sizeof(struct in6_addr));
            unsigned char label[LABEL_SIZE];
            memcpy(label, LABEL((*msg).msg_control), LABEL_SIZE);
            unsigned char buffer[10];
            memset(buffer, 0, 10);
            send_data_packet(saddr, daddr, label, LABEL_SIZE, buffer, 10);
		}; break;
	case CONTENT_RESP:
		{

		}; break;
	default:
		ret = -EOPNOTSUPP;
	}

	return ret;
}

int csock_recvmsg(struct content_sock* sk, struct msghdr* msg,
				  size_t len, int noblock, int flags, int *addr_len)
{

	return 0;
}

int csock_rcv_skb(struct content_sock* sk, struct sk_buff* skb)
{

	return 0;
}

int csock_setsockopt(struct sock* sk, int level, int optname,
					 char __user *optval, unsigned int optlen)
{
	
	return 0;
}

int csock_getsockopt(struct sock* sk, int level, int optname,
					 char __user *optval, int __user *optlen)
{

	return 0;
}
