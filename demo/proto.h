/*******************************************************************************

 File Name: proto.h
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月27日 星期三 21时00分10秒

*******************************************************************************/

#ifndef __PROTO_H__
#define __PROTO_H__

#include <linux/socket.h>

#define IPPROTO_CONTENT  55

#define CONTENT_REQ  1
#define CONTENT_RESP 2

#define LABEL_SIZE 40

struct content_label {
	struct cmsghdr hdr;
	unsigned char label[LABEL_SIZE];
};

#define MSGCTL_SIZE  sizeof(struct content_label)

#define LABEL(cmsg)  (((struct content_label*)cmsg)->label)

#endif
