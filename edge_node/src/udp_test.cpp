#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>




int main() {
    // udp 소켓 생성
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    // 목적지 주소 및 포트 설정
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5005);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.2");

    // 보낼 데이터
    const char* msg = "hello, c2 server! - 단말기 01정상 작동중";

    // 전송 시작
    sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    std::cout << "전송 완료" << std::endl;


    close(sock);



    return 0;

}