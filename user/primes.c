#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int fd[2]){
    int num, prime_num;
    read(fd[0],&prime_num,sizeof(prime_num));
    printf("prime %d\n", prime_num);

    int buf[36],cnt=0;
    while(read(fd[0],&num,sizeof(num))){
        if(num%prime_num!=0){
            buf[cnt++]=num;
        }
    }
    close(fd[0]);

    if(cnt==0){
        return;
    }
    int fd_next[2];
    pipe(fd_next);
    for(int i=0;i<cnt;i++){
        write(fd_next[1],&buf[i],sizeof(buf[i]));
    }
    close(fd_next[1]);

    if(fork()==0){
        prime(fd_next);
    }
    wait(0);
    close(fd_next[0]);
    return;
}

int
main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    for(int i=2;i<=35;i++){
        write(fd[1],&i,sizeof(i));
    }
    close(fd[1]);
    prime(fd);
    exit(0);
}
