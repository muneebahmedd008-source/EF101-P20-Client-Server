#include<winsock.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main(){
WSADATA w; WSAStartup(MAKEWORD(2,2),&w);
SOCKET s=socket(AF_INET,SOCK_STREAM,0);
sockaddr_in a;a.sin_family=AF_INET;a.sin_addr.s_addr=INADDR_ANY;a.sin_port=htons(5000);
bind(s,(sockaddr*)&a,sizeof(a));
listen(s,1);
cout<<"Server running on port 5000... waiting\n";

FILE *fh=fopen("data.csv","w");
fprintf(fh,"type,time,value\n");
fclose(fh);

while(true){
    SOCKET c=accept(s,0,0);
    cout<<"Client connected!\n";
    char buf[1024];

    // BONUS 2 (optional): token check - first message must be the secret token
    int n=recv(c,buf,1023,0);
    if(n<=0){closesocket(c);continue;}
    buf[n]='\0';
    if(strcmp(buf,"abc123")!=0){
        send(c,"DENIED",6,0);
        cout<<"Wrong token! Client rejected.\n";
        closesocket(c);
        continue;
    }
    send(c,"OK",2,0);

    while(true){
        n=recv(c,buf,1023,0);
        if(n<=0){cout<<"client disconnected! Waiting for new client...\n";break;}
        buf[n]='\0';
        cout<<"Got: "<<buf;               // message/data received
        FILE *f=fopen("data.csv","a");
        fprintf(f,"%s",buf);              // save to file
        fclose(f);
        send(c,"ACK",3,0);                // BONUS 1 (optional): acknowledgement
    }
    closesocket(c);
}
}
