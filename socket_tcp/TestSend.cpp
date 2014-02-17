#include "stdafx.h"
#include <windows.h>
#include <math.h>

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