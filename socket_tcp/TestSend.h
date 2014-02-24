#ifndef _TESTSEND_H
#define _TESTSEND_H

#include "stdafx.h"

void TestSendPlanePosInfo(SOCKET Sockfd);
void TestSendCarPosInfo(SOCKET Sockfd);
void TestSendHandsetPosInfo(SOCKET Sockfd);
void TestSendDealInfo(SOCKET Sockfd);
void TestTrainPosInfo(SOCKET Sockfd);
void TestSendHandsetReturnInfo(SOCKET Sockfd);
void TestSendCarReturnInfo(SOCKET Sockfd);
void TestTrainPosInfo_obstacle(SOCKET Sockfd);
void TestTrainPosInfo_45(SOCKET Sockfd);

#endif

