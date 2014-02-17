// socket_tcp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <process.h>
#include "ToolFunctionSet.h"
#include "data_format.h"
#include "SaveToOracle.h"
#include "Base16.h"
#include "TestSend.h"

#define PORT			7069
#define IPLENGTH		15
#define TIME_OUT_TIME	10  //s��ʱʱ��10��
#define MAXCNT			100	//max count of socket clients

SOCKET			g_sockfd			= -1;
SOCKET			g_server_sock		= -1;
static SOCKET	g_SockClient[MAXCNT]	= {0};
static int		icount				= 0;

IDBConnect		*gpDBConn;
IDBRecordSet	*gpDBRs;
TCHAR g_pPath[MAX_PATH];
ToolFunctionSet *g_pTool = new ToolFunctionSet();
char g_host[BUFSIZ];
char g_user[BUFSIZ];
char g_passwd[BUFSIZ];
char g_db[BUFSIZ];
int	 g_port;
int  g_funcSend;
int  g_funcReceive;
int	 g_funcTrain;
int  g_funcRescue;


void uninit(int sig)
{
	closesocket(g_sockfd);
	WSACleanup();
	printf("close sock\n");
	exit(0);
}

void initOracle()
{
	InitDBEngine("MIDCARDS");
	gpDBConn = ConnDBServer(g_host, g_user, g_passwd, g_db, g_port);
	if(gpDBConn == NULL)
	{
		printf(("gpDBConn is null\n"));
		return;
	}

	gpDBRs = CreateRsInst(gpDBConn);
	if(gpDBRs == NULL)
	{
		printf(("gpDBRs is null\n"));
		return;
	}
	printf(("connect oracle succeed\n"));
}

void GetConfigPath(TCHAR *pPath, ToolFunctionSet *pTool)
{
	pTool->GetCurExePath(pPath);

	StringCchPrintf(pPath, MAX_PATH/sizeof(TCHAR), _T("%s//config.ini"), pPath);
}

void GetServerInfo( int* iPort, char *chServerIP ) 
{
	TCHAR szServerIP[IPLENGTH];	

	*iPort = GetPrivateProfileInt(_T("Server"), _T("Port"), 0, g_pPath);
	GetPrivateProfileString(_T("Server"), _T("IP"), _T(""), szServerIP, MAX_PATH/sizeof(TCHAR), g_pPath);

	GetPrivateProfileString(_T("Database"), _T("host"), _T(""), g_host, MAX_PATH/sizeof(TCHAR), g_pPath);
	GetPrivateProfileString(_T("Database"), _T("user"), _T(""), g_user, MAX_PATH/sizeof(TCHAR), g_pPath);
	GetPrivateProfileString(_T("Database"), _T("passwd"), _T(""), g_passwd, MAX_PATH/sizeof(TCHAR), g_pPath);
	GetPrivateProfileString(_T("Database"), _T("db"), _T(""), g_db, MAX_PATH/sizeof(TCHAR), g_pPath);
	g_port = GetPrivateProfileInt(_T("Database"), _T("port"), 0, g_pPath);

	g_funcReceive = GetPrivateProfileInt(_T("Function"), _T("Receive"), 0, g_pPath);
	g_funcSend = GetPrivateProfileInt(_T("Function"), _T("Send"), 0, g_pPath);
	g_funcRescue = GetPrivateProfileInt(_T("Function"), _T("Rescue"), 0, g_pPath);
	g_funcTrain = GetPrivateProfileInt(_T("Function"), _T("Train"), 0, g_pPath);

	g_pTool->ConvertToMChar(chServerIP, IPLENGTH, szServerIP);
	//printf("%s:%d\n", chServerIP, iPort);	
	//return *iPort;
}
unsigned int __stdcall accept_thread(void* param)
//DWORD WINAPI accept_thread(LPVOID lParam)
//int accept_thread()
{
	struct sockaddr_in client_addr;
	int sin_size = 0;
	sin_size = sizeof(struct sockaddr_in);
	SOCKET newsockfd;

	while(1)
	{	
		newsockfd = accept(g_server_sock, (struct sockaddr *)(&client_addr), &sin_size);
		if (newsockfd != -1)
		{
			printf("[Client in %s, fd is %d]\n", inet_ntoa(client_addr.sin_addr), newsockfd);
			g_SockClient[icount++] = newsockfd;
			if (g_funcRescue)
			{
				TestSendPlanePosInfo(newsockfd);
				TestSendCarPosInfo(newsockfd);
				TestSendHandsetPosInfo(newsockfd);
				TestSendDealInfo(newsockfd);
				TestSendHandsetReturnInfo(newsockfd);
				TestSendCarReturnInfo(newsockfd);
			}
			else if (g_funcTrain)
			{
				TestTrainPosInfo(newsockfd);
			}			
		}
		//Sleep(1);
	}	
	return 0;
}

int split(const char *str, const char *deli, vector<string> &vecString) 
{
	char buff[BUFSIZ];
	memset(buff, 0, sizeof(buff));
	strncpy_s(buff, str, sizeof(buff));
	char * gg; 
	char *p = strtok_s(buff, deli, &gg);

//	vecString.clear();

	int index = 0;
	while(p != NULL) 
	{ 
		vecString.push_back(p);
		p = strtok_s(NULL, deli, &gg); 
		index++;
	}
	
	return index;
}

void DealValidData(CSaveToOracle *pSaveToOracle, int &ret, const char *buf)
{
	vector<string> vecString;
	int length = split(buf, ",", vecString);

	if (length > 0)
	{
		int iTypeID = atoi(vecString.at(0).c_str());
		int iSize = vecString.size();

		switch(iTypeID)
		{
		case TRAIN_POS:
			{
				if (iSize >= 4)
				{
					TRAINPOS_INFO info = {0};
					info.iID			= atoi(vecString.at(0).c_str());
					if (iSize == 5)
					{
						info.strCardID		= vecString.at(1);
						info.strPosX		= vecString.at(2).c_str();
						info.strPosY		= vecString.at(3).c_str();		
						info.strDateTime	= vecString.at(4).substr(0, 19);
					}
					else
					{
						info.strPosX		= vecString.at(1).c_str();
						info.strPosY		= vecString.at(2).c_str();		
						info.strDateTime	= vecString.at(3).substr(0, 19);
					}
					ret = pSaveToOracle->SaveTrainPosInfo(info);
				}
			}
			break;
		case PLANE_POS:
		case CAR_POS:
		case SEARCHER_POS:
			{
				if (iSize >= 4)
				{
					RESCUEPOS_INFO info;
					info.iID			= atoi(vecString.at(0).c_str());
					if (iSize == 5)
					{
						info.strCardID		= vecString.at(1).c_str();
						info.strLongitude	= vecString.at(2).c_str();
						info.strLatitude	= vecString.at(3).c_str();		
						info.strDateTime	= vecString.at(4).substr(0, 19);
					}
					else
					{
						info.strLongitude	= vecString.at(1).c_str();
						info.strLatitude	= vecString.at(2).c_str();		
						info.strDateTime	= vecString.at(3).substr(0, 19);
					}
					ret = pSaveToOracle->SaveRescuePosInfo(info);
				}
			}
			break;
		case DAMAGE_INFO:
		case RESCUE_INFO:
			{
				if (iSize >= 3)
				{
					HANDSET_INFO info;
					info.iID			= atoi(vecString.at(0).c_str());
					if (iSize == 4)
					{
						info.strCardID		= vecString.at(1);
						info.strContent		= vecString.at(2).c_str();
						info.strDateTime	= vecString.at(3).substr(0, 19);
					}
					else
					{
						info.strContent		= vecString.at(1).c_str();
						info.strDateTime	= vecString.at(2).substr(0, 19);
					}
					ret = pSaveToOracle->SaveHandsetInfo(info);
				}
			}
			break;
		default:
			ret = WRONG_DATATYPE;
			break;
		}
		//printf("save %s to database result: %d\n", buf, ret);
	}
	else
	{
		printf("receive buf error");
	}
}

void ReconnectSock( int &ret, const struct sockaddr_in *address, int iPort, int len ) 
{
	while(ret != 0)
	{
		printf("connect %s:%d error\n", inet_ntoa(address->sin_addr), iPort);
		Sleep(2000);
		printf("reconnecting ...\n");
		ret = connect(g_sockfd, (struct sockaddr *)address, len);
	}
}

int connect_retry(int &ret, int sockfd, const struct sockaddr *address, int len)
{
	int nsec;

	for (nsec = 1; nsec <= TIME_OUT_TIME; nsec++)
	{
		ret = connect(g_sockfd, (struct sockaddr *)address, len);
		if (ret == 0)
		{
			return 0;
		}
		if (nsec <= TIME_OUT_TIME / 2)
		{
			Sleep(nsec);
		}
	}
	return -1;
}

int _tmain(int argc, _TCHAR *argv[])
{
	signal(SIGTERM, uninit);
	signal(SIGINT, uninit);
	//signal(SIGPIPE, SIG_IGN);
	//	int sockfd;
	GetConfigPath(g_pPath, g_pTool);
	
	int iPort = 71069;
	char chServerIP[IPLENGTH] = {0};
	GetServerInfo(&iPort, chServerIP);

	int ret; 

#ifdef WIN32
	WORD wVersionRequested;  
	WSADATA wsaData;  

	//WinSock��ʼ��  
	wVersionRequested = MAKEWORD(2, 2); //ϣ��ʹ�õ�WinSock DLL�İ汾  
	ret = WSAStartup(wVersionRequested, &wsaData);  //�����׽��ֿ�  
	if(ret != 0)  
	{  
		printf("WSAStartup() failed!\n");  
		//return 0;  
	}  

	//ȷ��WinSock DLL֧�ְ汾2.2  
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)  
	{  
		WSACleanup();   //�ͷ�Ϊ�ó���������Դ����ֹ��winsock��̬���ʹ��  
		printf("Invalid WinSock version!\n");  
		//return 0;  
	} 
#endif

	if (g_funcSend)
	{
#pragma region Server Socket
		g_server_sock = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(5544);   //�˿�
		addr.sin_addr.s_addr = htonl(INADDR_ANY);//�ڱ���������ip�Ͽ�ʼ����
		bind(g_server_sock,(sockaddr *)&addr, sizeof(addr));
		listen(g_server_sock, MAXCNT);

		HANDLE hThread;
		//hThread = CreateThread(NULL, 0, accept_thread, NULL, 0, NULL);

		unsigned int uiThreadID(0);
		hThread = (HANDLE)_beginthreadex((void*)NULL, 0, (accept_thread), NULL, 0, &uiThreadID);
		printf("listen port 5544\n");
#pragma endregion Server Socket
	}

	if (g_funcReceive)
	{
		initOracle();
		CSaveToOracle *pSaveToOracle = new CSaveToOracle(gpDBConn, gpDBRs);

		int len;
		struct sockaddr_in address;
		char char_send[100] = { 0 };
		g_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (g_sockfd == INVALID_SOCKET)  
		{  
			WSACleanup();  
			printf("socket() failed!\n");
		}  
	
		::setsockopt(g_sockfd, SOL_SOCKET, SO_SNDTIMEO, (char*)TIME_OUT_TIME, sizeof(TIME_OUT_TIME));	//send timeout
		::setsockopt(g_sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)TIME_OUT_TIME, sizeof(TIME_OUT_TIME));	//recv timeout

		//���÷���������
	// 	unsigned long ul = 1;
	// 	ret = ioctlsocket(g_sockfd, FIONBIO, (unsigned long*)&ul);
	// 	if (ret == SOCKET_ERROR)
	// 	{
	// 		printf("����������ʧ��\r\n");
	// 		return -1;
	// 	}
	
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(iPort);
	#ifdef WIN32
		address.sin_addr.s_addr = inet_addr(chServerIP);
	#else
		inet_pton(AF_INET, argv[1], &address.sin_addr);
	#endif	

		len = sizeof(address);
		ret = connect(g_sockfd, (struct sockaddr *)&address, len);

		if (ret == SOCKET_ERROR)
		{
			ReconnectSock(ret, &address, iPort, len);
		}	

		printf("connect %s:%d succeed\n", inet_ntoa(address.sin_addr), iPort);

		int timeCount = 0;

		while(1)
		{
			++timeCount;
			if (timeCount > 11000)
			{
				ReconnectSock(ret, &address, iPort, len);
			}

			char buf[BUFSIZ] = {0};
			int byte = 0;
			memset(buf, 0, BUFSIZ);
			if((byte = recv(g_sockfd, buf, BUFSIZ, 0)) > 0)
			{
				buf[byte] = '\0';
				printf("recv: %s", buf);
			
				int size = 0;
				int i = 0;
				for(i = 0; i < icount; i++)
				{
					if((size = send(g_SockClient[i], buf, byte, 0)) < 0)
					{
						printf("send to client error\n");
					}
				}
				// TODO write into DB, transfer data to client	
			
				if (buf[0] == 'h' || buf[0] == 'H')
				{
					//TODO heart beat, reset timer
					timeCount = 0;
					printf("heart beat: %s!\n", buf);
				}
				else
				{
					timeCount = 0;
					DealValidData(pSaveToOracle, ret, buf);
				}
			}
			Sleep(1);
		}
	}
	while(1)
	{
		Sleep(1);
	}
	closesocket(g_server_sock);
	closesocket(g_sockfd);
	for (int i = 0; i < 100; i++)
	{
		closesocket(g_SockClient[i]);
	}
	WSACleanup();

	return 0;
}