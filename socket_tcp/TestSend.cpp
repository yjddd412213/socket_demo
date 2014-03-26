#include "stdafx.h"
#include <windows.h>
#include <math.h>
#include <process.h>

#define MINLONGITUDE		119.385017
#define MAXLONGITUDE		119.524054
#define MINLATITUDE			32.162929
#define MAXLATITUDE			32.241730
#define TIMELIMIT			60
#define LONGITUDE_INTERVAL	((MAXLONGITUDE - MINLONGITUDE) / TIMELIMIT)
#define LATITUDE_INTERVAL	((MAXLATITUDE - MINLATITUDE) / TIMELIMIT)
#define CAR_DEST_POS_INDEX	20
#define PERSON_POS_INDEX	30
#define HOSPITAL_POS_INDEX	20

#define	TRAIN_AERA_LENGTH		50
#define TRAIN_AERA_WIDTH		50	
#define TRAIN_TIME				30
#define TRAIN_CENTER_X			25.0
#define TRAIN_CENTER_Y			25.0
#define TRAIN_RADIUS			15.0
#define TRAIN_RADIUS_2			16.0
#define TRAIN_RADIUS_3			17.0
#define TRAIN_POS_X_INTERVAL	((4.0 * TRAIN_RADIUS) / (10.0 * TRAIN_TIME))
#define TRAIN_POS_X_INTERVAL_2	((4.0 * TRAIN_RADIUS_2) / (10.0 * TRAIN_TIME))
#define TRAIN_POS_X_INTERVAL_3	((4.0 * TRAIN_RADIUS_3) / (10.0 * TRAIN_TIME))

#define TRAIN_SIDE_LEFT			5.0
#define TRAIN_START_X			5.0
#define TRAIN_START_Y			40.0
#define TRAIN_END_X				5.0
#define TRAIN_END_Y				10.0

#define TRAIN_OBSTACLE_1_X		10.0
#define TRAIN_OBSTACLE_1_Y		40.0
#define TRAIN_OBSTACLE_1_LEN	10.0

#define TRAIN_OBSTACLE_2_X		30.0
#define TRAIN_OBSTACLE_2_Y		40.0
#define TRAIN_OBSTACLE_2_LEN	10.0

#define TRAIN_OBSTACLE_3_X		40.0
#define TRAIN_OBSTACLE_3_Y		10.0
#define TRAIN_OBSTACLE_3_LEN	10.0

#define TRAIN_OBSTACLE_4_X		20.0
#define TRAIN_OBSTACLE_4_Y		10.0
#define TRAIN_OBSTACLE_4_LEN	10.0

#define TRAIN_ENTER_X			(25)
#define TRAIN_ENTER_Y			(25)

#define TRAIN_45_START_X		1973
#define TRAIN_45_START_Y		1081
#define TRAIN_45_END_X			735
#define TRAIN_45_END_Y			315
#define	TRAIN_45_INTERVAL_X		((TRAIN_45_START_X - TRAIN_45_END_X) / 120)

SOCKET Sockfd;
struct PosInfo
{
	double lPosX;
	double lPosY;
};
PosInfo pos;

void TestSendPlanePosInfo(SOCKET Sockfd)
{
	for (int i = 0; i < TIMELIMIT; i++)
	{
		int size = 0;
		char buf[BUFSIZ] = {0};
		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		char tmp[64] = {0};
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		long double longitude = MINLONGITUDE + i * (LONGITUDE_INTERVAL);
		long double latitude = MINLATITUDE + i * (LATITUDE_INTERVAL);

		switch(i)
		{
		case 30:
			StringCchPrintf(buf, BUFSIZ, "1,%s,%.8f,%.8f,", "E2006003027E8E0P", longitude, latitude);
			break;
		case 31:
			StringCchPrintf(buf, BUFSIZ, "1,%s,%.8f,%.8f,", "E2006003027E8E0Z", longitude, latitude);
			break;
		case 33:
			StringCchPrintf(buf, BUFSIZ, "1,%s,%.8f,%.8f,", "E2006003027E8E0D", longitude, latitude);
			break;
		case 35:
			StringCchPrintf(buf, BUFSIZ, "1,%s,%.8f,%.8f,", "E2006003027E8E0U", longitude, latitude);
			break;
		case 50:
			StringCchPrintf(buf, BUFSIZ, "1,%s,%.8f,%.8f,", "E2006003027E8E0C", longitude, latitude);
			break;
		default:
			StringCchPrintf(buf, BUFSIZ, "1,,%.8f,%.8f,", longitude, latitude);
		}
		
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		size = send(Sockfd, buf, len, 0);
		Sleep(1000);
	}	
}

void TestSendCarPosInfo(SOCKET Sockfd)
{
	for (int i = 0; i < CAR_DEST_POS_INDEX + 1; i++)
	{
		int size = 0;
		char buf[BUFSIZ] = {0};
		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		char tmp[64] = {0};
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		long double longitude = MINLONGITUDE + i * (LONGITUDE_INTERVAL);
		long double latitude = MINLATITUDE + i * (LATITUDE_INTERVAL);

		StringCchPrintf(buf, BUFSIZ, "2,,%.8f,%.8f,", longitude, latitude);
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		size = send(Sockfd, buf, len, 0);
		Sleep(1000);
	}	
}

void TestSendHandsetPosInfo(SOCKET Sockfd)
{
	for (int i = CAR_DEST_POS_INDEX; i < PERSON_POS_INDEX + 1; i++)
	{
		int size = 0;
		char buf[BUFSIZ] = {0};
		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		char tmp[64] = {0};
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		long double longitude = MINLONGITUDE + i * (LONGITUDE_INTERVAL);
		long double latitude = MINLATITUDE + i * (LATITUDE_INTERVAL);

		StringCchPrintf(buf, BUFSIZ, "31,,%.8f,%.8f,", longitude, latitude);
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		size = send(Sockfd, buf, len, 0);
		Sleep(1000);
	}	
}

void TestSendHandsetReturnInfo(SOCKET Sockfd)
{
	for (int i = PERSON_POS_INDEX; i > CAR_DEST_POS_INDEX - 1; i--)
	{
		int size = 0;
		char buf[BUFSIZ] = {0};
		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		char tmp[64] = {0};
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		long double longitude = MINLONGITUDE + i * (LONGITUDE_INTERVAL);
		long double latitude = MINLATITUDE + i * (LATITUDE_INTERVAL);

		StringCchPrintf(buf, BUFSIZ, "31,,%.8f,%.8f,", longitude, latitude);
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		size = send(Sockfd, buf, len, 0);
		Sleep(1000);
	}	
}

void TestSendCarReturnInfo(SOCKET Sockfd)
{
	for (int i = CAR_DEST_POS_INDEX; i > -1; i--)
	{
		int size = 0;
		char buf[BUFSIZ] = {0};
		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		char tmp[64] = {0};
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		long double longitude = MINLONGITUDE + i * (LONGITUDE_INTERVAL);
		long double latitude = MINLATITUDE + i * (LATITUDE_INTERVAL);

		StringCchPrintf(buf, BUFSIZ, "2,,%.8f,%.8f,", longitude, latitude);
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		size = send(Sockfd, buf, len, 0);
		Sleep(1000);
	}	
}

void TestSendDealInfo(SOCKET Sockfd)
{
	int size = 0;
	char buf[BUFSIZ] = {0};
	SYSTEMTIME time; 
	GetLocalTime( &time ); 
	char tmp[64] = {0};
	snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
		time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	StringCchPrintf(buf, BUFSIZ, "32,E2006003027E8E0P,%s,", "11");
	StringCchCat(buf, BUFSIZ, tmp);

	int len = sizeof(buf)/sizeof(char);
	size = send(Sockfd, buf, len, 0);
	Sleep(1000);

	StringCchPrintf(buf, BUFSIZ, "33,E2006003027E8E0P,%s,", "111111");
	StringCchCat(buf, BUFSIZ, tmp);

	len = sizeof(buf)/sizeof(char);
	size = send(Sockfd, buf, len, 0);
}


void TestTrainPosInfo(SOCKET Sockfd)
{
	Sleep(1);

	double lPosx1 = TRAIN_CENTER_X - TRAIN_RADIUS;
	double lPosy1 = TRAIN_CENTER_Y;

	double lPosx2 = TRAIN_CENTER_X - TRAIN_RADIUS_2;
	double lPosy2 = TRAIN_CENTER_Y;

	double lPosx3 = TRAIN_CENTER_X - TRAIN_RADIUS_3;
	double lPosy3 = TRAIN_CENTER_Y;

	int size = 0;
	char buf[BUFSIZ] = {0};
	char buf2[BUFSIZ] = {0};
	char buf3[BUFSIZ] = {0};

	StringCchPrintf(buf, BUFSIZ, "0,%s,%.8f,%.8f,", "E2006003027E8E0P", lPosx1, lPosy1);
	StringCchPrintf(buf2, BUFSIZ, "0,%s,%.8f,%.8f,", "E2006003027E8E0Z", lPosx2, lPosy2);
	StringCchPrintf(buf3, BUFSIZ, "0,%s,%.8f,%.8f,", "E2006003027E8E0U", lPosx3, lPosy3);

	SYSTEMTIME time; 
	GetLocalTime( &time ); 
	char tmp[64] = {0};
	snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
		time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	StringCchCat(buf, BUFSIZ, tmp);
	StringCchCat(buf2, BUFSIZ, tmp);
	StringCchCat(buf3, BUFSIZ, tmp);

	int len = sizeof(buf)/sizeof(char);
	size = send(Sockfd, buf, len, 0);
	Sleep(1);
	len = sizeof(buf2)/sizeof(char);
	size = send(Sockfd, buf2, len, 0);
	Sleep(1);
	len = sizeof(buf3)/sizeof(char);
	size = send(Sockfd, buf3, len, 0);
	Sleep(100);


	for (int i = 0; i < (10 * TRAIN_TIME); i++)
	{
		if ((TRAIN_POS_X_INTERVAL * i) < (TRAIN_RADIUS * 2))
		{
			lPosx1 += TRAIN_POS_X_INTERVAL;
			lPosy1 = (-1.0) * sqrt(fabs((TRAIN_RADIUS * TRAIN_RADIUS) - (lPosx1 - TRAIN_CENTER_X) * (lPosx1 - TRAIN_CENTER_X))) + TRAIN_CENTER_Y;
		}
		else
		{
			lPosx1 -= TRAIN_POS_X_INTERVAL;
			lPosy1 = sqrt(fabs((TRAIN_RADIUS * TRAIN_RADIUS) - (lPosx1 - TRAIN_CENTER_X) * (lPosx1 - TRAIN_CENTER_X))) + TRAIN_CENTER_Y;
		}

		if ((TRAIN_POS_X_INTERVAL_2 * i) < (TRAIN_RADIUS_2 * 2))
		{
			lPosx2 += TRAIN_POS_X_INTERVAL_2;
			lPosy2 = (-1.0) * sqrt(fabs((TRAIN_RADIUS_2 * TRAIN_RADIUS_2) - (lPosx2 - TRAIN_CENTER_X) * (lPosx2 - TRAIN_CENTER_X))) + TRAIN_CENTER_Y;
		}
		else
		{
			lPosx2 -= TRAIN_POS_X_INTERVAL_2;
			lPosy2 = sqrt(fabs((TRAIN_RADIUS_2 * TRAIN_RADIUS_2) - (lPosx2 - TRAIN_CENTER_X) * (lPosx2 - TRAIN_CENTER_X))) + TRAIN_CENTER_Y;
		}

		if ((TRAIN_POS_X_INTERVAL_3 * i) < (TRAIN_RADIUS_3 * 2))
		{
			lPosx3 += TRAIN_POS_X_INTERVAL_3;
			lPosy3 = (-1.0) * sqrt(fabs((TRAIN_RADIUS_3 * TRAIN_RADIUS_3) - (lPosx3 - TRAIN_CENTER_X) * (lPosx3 - TRAIN_CENTER_X))) + TRAIN_CENTER_Y;
		}
		else
		{
			lPosx3 -= TRAIN_POS_X_INTERVAL_3;
			lPosy3 = sqrt(fabs((TRAIN_RADIUS_3 * TRAIN_RADIUS_3) - (lPosx3 - TRAIN_CENTER_X) * (lPosx3 - TRAIN_CENTER_X))) + TRAIN_CENTER_Y;
		}

		StringCchPrintf(buf, BUFSIZ, "0,%s,%.8f,%.8f,", "E2006003027E8E0P", lPosx1, lPosy1);
		StringCchPrintf(buf2, BUFSIZ, "0,%s,%.8f,%.8f,", "E2006003027E8E0Z", lPosx2, lPosy2);
		StringCchPrintf(buf3, BUFSIZ, "0,%s,%.8f,%.8f,", "E2006003027E8E0U", lPosx3, lPosy3);

		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		char tmp[64] = {0};
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		StringCchCat(buf, BUFSIZ, tmp);
		StringCchCat(buf2, BUFSIZ, tmp);
		StringCchCat(buf3, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		size = send(Sockfd, buf, len, 0);
		Sleep(1);
		len = sizeof(buf2)/sizeof(char);
		size = send(Sockfd, buf2, len, 0);
		Sleep(1);
		len = sizeof(buf3)/sizeof(char);
		size = send(Sockfd, buf3, len, 0);
		Sleep(100);
	}	
}

void GenOneLine1(double lPosx, double lPosy, char *cardid, double interval) 
{
	int size = 0;
	char buf[BUFSIZ] = {0};
	char tmp[64] = {0};
	double goStartLineInterval;
	double times = TRAIN_START_X > TRAIN_ENTER_X ? -1 : 1;

	goStartLineInterval = (TRAIN_START_Y - TRAIN_ENTER_Y) / (TRAIN_START_X - TRAIN_ENTER_X);
	while ((times > 0 && lPosx >= TRAIN_START_X) || (times < 0 && lPosx <= TRAIN_START_X))
	{
		lPosy = TRAIN_START_Y + goStartLineInterval * (lPosx - TRAIN_START_X);

		StringCchPrintf(buf, BUFSIZ, "0,%s,%.8f,%.8f,", cardid, lPosx, lPosy);

		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		if(lPosx >= TRAIN_START_X)
		{
			size = send(Sockfd, buf, len, 0);
			Sleep(100);
			lPosx -= times * interval;
		}
	}
}

void GenLine(PosInfo startPos, PosInfo endPos, char *cardid, double interval) 
{
	PosInfo curPos = startPos;
	int size = 0;
	char buf[BUFSIZ] = {0};
	char tmp[64] = {0};
	double goStartLineInterval;
	double times = endPos.lPosX > startPos.lPosX ? 1 : -1;

	if (endPos.lPosX == startPos.lPosX)		//avoid divided by 0
	{
		return;
	}
	goStartLineInterval = (endPos.lPosY - startPos.lPosY) / (endPos.lPosX - startPos.lPosX);
	while ((times > 0 && curPos.lPosX <= endPos.lPosX) || (times < 0 && curPos.lPosX >= endPos.lPosX))
	{
		curPos.lPosY = endPos.lPosY + goStartLineInterval * (curPos.lPosX - endPos.lPosX);

		StringCchPrintf(buf, BUFSIZ, "6,%s,%.8f,%.8f,", cardid, curPos.lPosX, curPos.lPosY);

		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		//if((startPos.lPosX >= endPos.lPosX && curPos.lPosX >= endPos.lPosX) ||
		//	(startPos.lPosX <= endPos.lPosX && curPos.lPosX <= endPos.lPosX))
		{
			size = send(Sockfd, buf, len, 0);
			Sleep(100);
			curPos.lPosX += times * interval;
		}
	}
}

void GenCircle(PosInfo startPos, PosInfo endPos, char *cardid, double interval)
{
	PosInfo curPos = startPos;
	int size = 0;
	char buf[BUFSIZ] = {0};
	char tmp[64] = {0};

	while(curPos.lPosY >= endPos.lPosY)
	{
		curPos.lPosX = sqrt((startPos.lPosX - TRAIN_CENTER_X)*(startPos.lPosX - TRAIN_CENTER_X) 
			+ (startPos.lPosY - TRAIN_CENTER_Y)*(startPos.lPosY - TRAIN_CENTER_Y) 
			- (curPos.lPosY - TRAIN_CENTER_Y) * (curPos.lPosY - TRAIN_CENTER_Y)) + 25;

		StringCchPrintf(buf, BUFSIZ, "0,%s,%.8f,%.8f,", cardid, curPos.lPosX, curPos.lPosY);

		SYSTEMTIME time; 
		GetLocalTime( &time ); 
		snprintf(tmp, sizeof(tmp), "%4d-%02d-%02d %02d:%02d:%02d\r\n", 
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		StringCchCat(buf, BUFSIZ, tmp);

		int len = sizeof(buf)/sizeof(char);
		size = send(Sockfd, buf, len, 0);
		Sleep(100);
		curPos.lPosY -= interval;
	}
}

void GenPath( char * cardid, double interval ) 
{
	PosInfo L1SP;
	L1SP.lPosX = TRAIN_ENTER_X;
	L1SP.lPosY = TRAIN_ENTER_Y;
	PosInfo L2SP;
	L2SP.lPosX = TRAIN_START_X;
	L2SP.lPosY = TRAIN_START_Y;
	PosInfo O1SP;
	O1SP.lPosX = TRAIN_OBSTACLE_1_X;
	O1SP.lPosY = TRAIN_OBSTACLE_1_Y;	
	PosInfo L3SP;
	L3SP.lPosX = TRAIN_OBSTACLE_1_X + TRAIN_OBSTACLE_1_LEN;
	L3SP.lPosY = TRAIN_OBSTACLE_1_Y;
	PosInfo O2SP;
	O2SP.lPosX = TRAIN_OBSTACLE_2_X;
	O2SP.lPosY = TRAIN_OBSTACLE_2_Y;	
	PosInfo C1SP;
	C1SP.lPosX = TRAIN_OBSTACLE_2_X + TRAIN_OBSTACLE_2_LEN;
	C1SP.lPosY = TRAIN_OBSTACLE_2_Y;
	PosInfo O3SP;
	O3SP.lPosX = TRAIN_OBSTACLE_3_X;
	O3SP.lPosY = TRAIN_OBSTACLE_3_Y;
	PosInfo L4SP;
	L4SP.lPosX = TRAIN_OBSTACLE_3_X - TRAIN_OBSTACLE_3_LEN;
	L4SP.lPosY = TRAIN_OBSTACLE_3_Y;
	PosInfo O4SP;
	O4SP.lPosX = TRAIN_OBSTACLE_4_X;
	O4SP.lPosY = TRAIN_OBSTACLE_4_Y;
	PosInfo L5SP;
	L5SP.lPosX = TRAIN_OBSTACLE_4_X - TRAIN_OBSTACLE_4_LEN;
	L5SP.lPosY = TRAIN_OBSTACLE_4_Y;
	PosInfo L6SP;
	L6SP.lPosX = TRAIN_END_X;
	L6SP.lPosY = TRAIN_END_Y;

	GenLine(L1SP, L2SP, cardid, interval);
	GenLine(L2SP, O1SP, cardid, interval);
	GenLine(O1SP, L3SP, cardid, interval / 10);
	GenLine(L3SP, O2SP, cardid, interval);
	GenLine(O2SP, C1SP, cardid, interval / 10);
	GenCircle(C1SP, O3SP, cardid, interval);
	GenLine(O3SP, L4SP, cardid, interval / 10);
	GenLine(L4SP, O4SP, cardid, interval);
	GenLine(O4SP, L5SP, cardid, interval / 10);
	GenLine(L5SP, L6SP, cardid, interval);
	GenLine(L6SP, L1SP, cardid, interval);
}

// generate data of first line
unsigned int __stdcall GenOne(void* param)
{
	PosInfo posinfo = *(PosInfo*)param;
	char *cardid = "E2006003027E8E0P";
	//GenOneLine1(posinfo.lPosX, posinfo.lPosY, cardid, TRAIN_POS_X_INTERVAL);
	GenPath(cardid, TRAIN_POS_X_INTERVAL);
	return 0;
}

unsigned int __stdcall GenTwo(void* param)
{
	PosInfo *posinfo = (PosInfo*)param;
	char *cardid = "E2006003027E8E0Z";
	GenPath(cardid, TRAIN_POS_X_INTERVAL_2);
	return 0;
}

unsigned int __stdcall GenThree(void* param)
{
	PosInfo *posinfo = (PosInfo*)param;
	char *cardid = "E2006003027E8E0U";
	GenPath(cardid, TRAIN_POS_X_INTERVAL_3);
	return 0;
}

void TestTrainPosInfo_obstacle(SOCKET sockfd)
{
	Sleep(1);
	Sockfd = sockfd;
	pos.lPosX = TRAIN_ENTER_X;
	pos.lPosY = TRAIN_ENTER_Y;

	HANDLE hThread;
	unsigned int uiThreadID(0);
	hThread = (HANDLE)_beginthreadex((void*)NULL, 0, (GenOne), (void *)&pos, 0, &uiThreadID);
	hThread = (HANDLE)_beginthreadex((void*)NULL, 0, (GenTwo), (void *)&pos, 0, &uiThreadID);
	hThread = (HANDLE)_beginthreadex((void*)NULL, 0, (GenThree), (void *)&pos, 0, &uiThreadID);
}

void GenPath45( char * cardid, double interval ) 
{
	PosInfo SP;
	SP.lPosX = TRAIN_45_START_X;
	SP.lPosY = TRAIN_45_START_Y;
	PosInfo O1_S;
	O1_S.lPosX = 1591;
	O1_S.lPosY = 836;	
	PosInfo O1_E;
	O1_E.lPosX = 1507;
	O1_E.lPosY = 796;
	PosInfo O2_S1;
	O2_S1.lPosX = 1403;
	O2_S1.lPosY = 666;	
	PosInfo O2_S2;
	O2_S2.lPosX = 1199;
	O2_S2.lPosY = 550;	
	PosInfo O2_S3;
	O2_S3.lPosX = 1125;
	O2_S3.lPosY = 570;	
	PosInfo O2_E;
	O2_E.lPosX = 1089;
	O2_E.lPosY = 546;
	PosInfo O3_S;
	O3_S.lPosX = 1061;
	O3_S.lPosY = 476;
	PosInfo O3_E;
	O3_E.lPosX = 1051;
	O3_E.lPosY = 512;
	PosInfo O4_S;
	O4_S.lPosX = 961;
	O4_S.lPosY = 452;
	PosInfo O4_E;
	O4_E.lPosX = 755;
	O4_E.lPosY = 325;
	PosInfo EP;
	EP.lPosX = TRAIN_45_END_X;
	EP.lPosY = TRAIN_45_END_Y;

	GenLine(SP, O1_S, cardid, interval);
	GenLine(O1_S, O1_E, cardid, interval);
	GenLine(O1_E, O2_S1, cardid, interval);
	GenLine(O2_S1, O2_S2, cardid, interval);
	GenLine(O2_S2, O2_S3, cardid, interval);
	GenLine(O2_S3, O2_E, cardid, interval);
	GenLine(O2_E, O3_S, cardid, interval);
	GenLine(O3_S, O3_E, cardid, interval);
	GenLine(O3_E, O4_S, cardid, interval);
	GenLine(O4_S, O4_E, cardid, interval);
	GenLine(O4_E, EP, cardid, interval);
}

unsigned int __stdcall GenOne45(void* param)
{
	char *cardid = "E2006003027E8E0P";
	//GenOneLine1(posinfo.lPosX, posinfo.lPosY, cardid, TRAIN_POS_X_INTERVAL);
	GenPath45(cardid, TRAIN_45_INTERVAL_X);
	return 0;
}

void TestTrainPosInfo_45(SOCKET sockfd)
{
	Sleep(1);
	Sockfd = sockfd;
	HANDLE hThread;
	unsigned int uiThreadID(0);
	hThread = (HANDLE)_beginthreadex((void*)NULL, 0, (GenOne45), (void *)NULL, 0, &uiThreadID);
}
