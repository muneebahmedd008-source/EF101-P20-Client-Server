#include<winsock.h>
#include<iostream>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

// BONUS 1 (optional): wait for the server's "ACK" reply and show it
void getAck(SOCKET s){
    char r[10]={0};
    recv(s,r,9,0);
    cout<<"   Server: "<<r<<endl;
}

int main(){
srand(time(0));
WSADATA w; WSAStartup(MAKEWORD(2,2),&w);

char ip[50]; int port;
cout<<"Enter server IP (127.0.0.1 if same laptop): "; cin>>ip;
cout<<"Enter server port: "; cin>>port;

SOCKET s=socket(AF_INET,SOCK_STREAM,0);
sockaddr_in a; a.sin_family=AF_INET; a.sin_port=htons(port);
a.sin_addr.s_addr=inet_addr(ip);

if(connect(s,(sockaddr*)&a,sizeof(a))<0){cout<<"Failed! Wrong IP/Port - Server not found!\n";return 0;}
cout<<"Connected!\n";

// BONUS 2 (optional): send the secret token, server answers OK or DENIED
char token[50],reply[10]={0};
cout<<"Enter token: "; cin>>token;
send(s,token,strlen(token),0);
recv(s,reply,9,0);
if(strcmp(reply,"OK")!=0){cout<<"Wrong token! Rejected by server.\n";return 0;}

while(true){
    cout<<"\n1. Send a message\n2. Send 100 temperature records\n3. Exit\nChoice: ";
    int choice; cin>>choice;
    char msg[300],dt[50];
    time_t t=time(0);
    strftime(dt,50,"%Y-%m-%d %H:%M:%S",localtime(&t));   // current time

    if(choice==1){
        char text[200];
        cout<<"Type message: ";
        cin.ignore();
        cin.getline(text,200);
        sprintf(msg,"MSG,%s,%s\n",dt,text);
        send(s,msg,strlen(msg),0);
        cout<<"Sent: "<<msg;
        getAck(s);                                         // BONUS 1
    }
    else if(choice==2){
        for(int i=0;i<100;i++){
            float temp=20+(rand()%550)/10.0;
            t=time(0);
            strftime(dt,50,"%Y-%m-%d %H:%M:%S",localtime(&t));
            sprintf(msg,"DATA,%s,%.1f\n",dt,temp);
            send(s,msg,strlen(msg),0);
            cout<<"Sent "<<i+1<<"/100: "<<msg;
            getAck(s);                                     // BONUS 1
            Sleep(200);
        }
    }
    else break;
}
closesocket(s);
}
