#include <WinSock2.h>
#include <string.h>
#include <winsock.h>
#include <iostream>
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <Windows.h>
#include <thread>
#include "socket_server.h" 
//#include "eco_conduite_algorithm.cpp"
#pragma comment(lib, "ws2_32.lib")


#define NB_TRAME 100
using namespace std;

int nbSampleSpeed;
int nbSampleCorner;
CEcoConduiteAlogrithm EcoConduiteAlg;

CEcoConduiteAlogrithm getEcoConduiteAlg()
{
	return EcoConduiteAlg;
}


int start_socket_serveur()
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKET csock;

	SOCKADDR_IN sin;
	SOCKADDR_IN csin;
	unsigned char buff[12];
	int rcvdLen = 0;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8080);
	bind(sock, (SOCKADDR*)& sin, sizeof(sin));
	listen(sock, 0);
	short vitesse = 0;
	short Corner23= 0;
	short Corner67 = 0;

	while (1) 
	{
		int sinsize = sizeof(csin);
		if ((csock = accept(sock, (SOCKADDR*)& csin, &sinsize)) != INVALID_SOCKET)
		{		
			rcvdLen = recv(csock, (char*)buff, sizeof(buff), 0);
			if (memcmp("\x18\xFE\xF1\x00", buff, 4) == 0)
			{	
				vitesse = (buff[6] * 0x100 + buff[5]) / 256;
				EcoConduiteAlg.setSpeed(nbSampleSpeed, vitesse);
				cout << "vitesse " << vitesse  <<endl;
				nbSampleSpeed++;
				if (100 == nbSampleSpeed)
				{
					nbSampleSpeed = 0;
					EcoConduiteAlg.ecoConduite_Calc_AccelIndicator(); 
					EcoConduiteAlg.ecoConduite_Calc_DesAccelIndicator();
				}
			}
			else if (memcmp("\x18\xFF\x12\x2B", buff, 4) == 0)      /// ajouté
			{														/// ajouté
				Corner67 = (buff[11] * 0x100 + buff[10]) / 256;		    /// ajouté
				EcoConduiteAlg.setCorner67(nbSampleCorner, Corner67);	    /// ajouté
				cout << "Corner Value (byte6&7) " << Corner67 << endl;			/// ajouté

				Corner23 = (buff[7] * 0x100 + buff[6]) / 256;		    /// ajouté
				EcoConduiteAlg.setCorner23(nbSampleCorner, Corner23);	    /// ajouté
				cout << "Corner Value (byte2&3) " << Corner23 << endl;			/// ajouté

				nbSampleCorner++;									/// ajouté
				if (100 == nbSampleCorner)							/// ajouté
				{													/// ajouté
					nbSampleCorner = 0;								/// ajouté
					EcoConduiteAlg.ecoConduite_Calc_LHCorneringAlgorithm();/// ajouté
					EcoConduiteAlg.ecoConduite_Calc_RHCorneringAlgorithm();/// ajouté
				}													/// ajouté
			}														/// ajouté
		}
	}

	closesocket(csock);

	/* On devrait faire closesocket(sock); puis WSACleanup(); mais puisqu'on a entré une boucle infinie ... */
	return 0;
}
#if 0
int main(int argc, char const *argv[])
{
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
unsigned char buffer[1024][100];
int i_vitesse=0;
int i=0;
while (true)
{
// Creating socket file descriptor
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
{
perror("socket failed");
exit(EXIT_FAILURE);
}

// Forcefully attaching socket to the port 8080
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
  &opt, sizeof(opt)))
{
perror("setsockopt");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);

// Forcefully attaching socket to the port 8080
if (bind(server_fd, (struct sockaddr *)&address,
sizeof(address)) < 0)
{
perror("bind failed");
exit(EXIT_FAILURE);
}
if (listen(server_fd, 3) < 0)
{
perror("listen");
exit(EXIT_FAILURE);
}
if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t *)&addrlen)) < 0)
{
perror("accept");
exit(EXIT_FAILURE);
}
valread = read(new_socket, buffer, 1024);

printf("received %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x \r\n",buffer[i][0],buffer[i][1],buffer[i][2],buffer[i][3],buffer[i][4],buffer[i][5],buffer[i][6],buffer[i][7],buffer[i][8],buffer[i][9],buffer[i][10],buffer[i][11]);
i++;
if(i==NB_TRAME)
{
	for(int i=0; i<NB_TRAME; i++)
	{ 
		if(strcmp((char *)buffer[i][1],( char *)"fe")==0 && strcmp(( char *)buffer[i][2],( char *)"f1")==0)
						{
							char *vit_oct1, vit_oct1_bin[16]={'0'};

							vit_oct1=strcat((char *)buffer[i][5],(char *)buffer[i][6]);
							conversion_hex2bin(vit_oct1, vit_oct1_bin);                                                        
              
              int v1=conversion_b2D(vit_oct1_bin);                         
              
              VSpeedCurrent[i]=(float)v1/256.0;
            }		
	}		
	vitesse(); 			
}


close(new_socket);
close(valread);
close(server_fd);
}

return 0;
}

#endif
