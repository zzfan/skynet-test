/*******************************************************************************

 File Name: user.c
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月20日 星期三 11时39分05秒

*******************************************************************************/

#include <stdio.h>
#include <unistd.h>

#define CONTENT_SYSCALL 321

int main()
{
	int rc = syscall(CONTENT_SYSCALL, 1, 2, 3, 4, 5, 6, 7, 8);
    printf("return %d\n", rc);
    if (rc) {
        perror("syscall");
    }

	return 0;
}
