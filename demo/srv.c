/*******************************************************************************

 File Name: srv.c
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月26日 星期二 10时02分29秒

*******************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string.h>

#include "proto.h"

int main()
{
	int sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_CONTENT);
	if (sock == -1) {
		perror("socket");
		return 1;
	}

/*
    struct sockaddr_in6 saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin6_addr = in6addr_any;
    saddr.sin6_port = 1234;

    if (bind(sock, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        perror("bind");
    }
*/

	struct iovec iov;
    struct msghdr msg;
	struct content_label req_ctl = {{MSGCTL_SIZE, IPPROTO_CONTENT, 0}};

	bzero(&msg, sizeof(msg));

	msg.msg_iov = &iov;
	msg.msg_control = &req_ctl;
	msg.msg_controllen = MSGCTL_SIZE;

	if (recvmsg(sock, &msg, 0) == -1) {
		perror("recvmsg");
	}

	unsigned char* label = req_ctl.label;
	if (req_ctl.hdr.cmsg_type == CONTENT_REQ && memcmp(label, "abcd", 4) == 0) {
		bzero(&msg, sizeof(msg));
		struct content_label resp_ctl = {{MSGCTL_SIZE, IPPROTO_CONTENT, CONTENT_RESP},
										 {'a', 'b', 'c', 'd'}};
		char res[] = {'r', 'e', 's', 'u', 'l', 't', '\0'};
		iov.iov_base = res;
		iov.iov_len = strlen(res);
		msg.msg_iov = &iov;
		msg.msg_control = &resp_ctl;
		msg.msg_controllen = MSGCTL_SIZE;
		
		if (recvmsg(sock, &msg, 0) == -1) {
			perror("recvmsg");
		}
	}

	close(sock);
	return 0;
}
