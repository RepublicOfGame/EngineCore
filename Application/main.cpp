#include "event2/event.h"
#include "Log.h"

int main(){
    ERROR("TestError");
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = true;
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse);

    struct sockaddr_in listenAddress{
        .sin_family         = AF_INET,
        .sin_port           = htons(8888),
        .sin_addr           ={.s_addr = htonl(INADDR_ANY)},
    };
    bind(listenFd, reinterpret_cast<const sockaddr *>(&listenAddress), sizeof listenAddress);


    return 0;
}
