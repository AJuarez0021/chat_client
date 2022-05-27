#ifndef __CSOCKET_CLIENT_H
#define __CSOCKET_CLIENT_H

#include <winsock2.h>
#include <string>
#include <cassert>

using namespace std;



class CSocketClient{
public:
CSocketClient(unsigned short uPort=1111,const string& strIP="127.0.0.1"){
 m_strIP=strIP;
 m_uPort=uPort;
 m_Socket=NULL;
 
}

~CSocketClient(){ }

void SetIP(const string& strIP){
 m_strIP=strIP;
}

void Set_Port(unsigned short uPort){
 m_uPort=uPort;
}

unsigned short GetPort(){
  return m_uPort;
}

string GetIP(){
  string m_strIP;
}

bool Connect()
{
 
 WSADATA m_wsaData;
 int iResult =WSAStartup(MAKEWORD(2,2),&m_wsaData);
  
	 
 if (iResult != NO_ERROR)
  return false;

 m_Socket = CreateSocket();
 if(m_Socket== INVALID_SOCKET){
  WSACleanup();
  return false;

 }
 ClientInf.sin_family = AF_INET;
 ClientInf.sin_port=htons(m_uPort);
 ClientInf.sin_addr.s_addr=inet_addr(m_strIP.c_str());
 
 
 if ( connect(m_Socket, (SOCKADDR*) &ClientInf, sizeof(ClientInf) ) == SOCKET_ERROR) {    
    WSACleanup();
    return false;
  }

 return true;
}

SOCKET CreateSocket(int af=AF_INET,int iType=SOCK_STREAM,int iProtocol=IPPROTO_TCP)
{
  return socket(af,iType,iProtocol);
}

void Disconnect()
{
 closesocket(m_Socket);
 WSACleanup();
 m_Socket=NULL;
}

void CloseSocket(SOCKET s)
{
  closesocket(s);
   
}

bool Select(HWND hWnd,UINT uMsg){
 if(WSAAsyncSelect(m_Socket,hWnd,uMsg,FD_READ | FD_CLOSE | FD_WRITE | FD_CONNECT) == SOCKET_ERROR)
  return false;

 return true;
}

bool Send(const string& strText){
  if(send(m_Socket,strText.c_str(),strText.length()+1,0)==SOCKET_ERROR)
   return false;

  return true;
}

string Recv(){
  string strRes;
  strRes=recv(m_Socket,m_strBuffer,300,0)==SOCKET_ERROR ? "Error al leer datos" : m_strBuffer;
  return strRes;  
}

private:
 sockaddr_in ClientInf;
 SOCKET m_Socket;
 unsigned short m_uPort;
 string m_strIP;
 char m_strBuffer[300];
};

#endif