/*******************************************************************************

 File Name: user.c
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月20日 星期三 20时38分17秒

*******************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>

#define IPPROTO_CONTENT  55

int main()
{
	int sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_CONTENT);
	if (sock == -1) {
		perror("socket");
		return 1;
	}

	close(sock);
	return 0;
}
