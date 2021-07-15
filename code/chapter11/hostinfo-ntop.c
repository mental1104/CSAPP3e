#include<csapp.h>

int main(int argc, char** argv){
    struct addrinfo* p, *listp, hints;
    struct sockaddr_in* sockp;
    char buf[MAXLINE];
    int rc;

    if(argc!=2){
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if((rc = getaddrinfo(argv[1], NULL, &hints, &listp))!=0){
        fprintf(stderr, "getaddrinfo error： %s\n",gai_strerror(rc));
        exit(1);
    }

    
    for (p = listp; p; p->ai_next){
        sockp = (struct sockaddr_in*)p->ai_addr;
        Inet_ntop(AF_INET, &(sockp->sin_addr),buf, MAXLINE);
        printf("%s\n", buf);
    }

    Freeaddrinfo(listp);

    exit(0);   
}