#ifndef __IAP_DATA_H
#define __IAP_DATA_H
#include "Include.h"



/*************IAP Status*************/
#define IAP_NO_SUPPORT         0x0000 //设备不支持IAP
#define IAP_Free               0x0001	//未升级，或已经完成
#define IAP_Ready              0x0002	//发送IAP信息
#define IAP_File_Transfer      0x0003	//文件传输
#define IAP_Codeing            0x0004	//Flash 程序更新
#define IAP_Update_Fault       0x0005	//升级故障
#define IAP_Update_Succuss     0x0006	//升级成功
/*************IAP Fault*************/
#define IAP_Disable            0x0001	//IAP 未使能
#define IAP_Password_Err       0x0002	//IAP 密码错误
#define IAP_Timeout            0x0003	//超时退出
#define IAP_Cancel             0x0004	//退出/取消
#define IAP_Model_Err          0x0005	//型号不匹配
#define IAP_Firmware_Err       0x0006	//固件版本不匹配
#define IAP_Update_Fail        0x0007	//自动升级失败
#define IAP_Flash_Over         0x0008	//程序空间不够
#define IAP_Check_Fail         0x0009	//文件CRC 校验失败
#define IAP_Comm_Err           0x000A	//从机通信异常


extern INT16U IAP_Enable[2];
extern INT16U IAP_Status;
extern INT16U IAP_Fault;
extern INT16U IAP_Baud;
extern INT16U IAP_Com;
extern INT16U IAP_Password[4];
extern INT16U MCU_Model;
extern INT16U Software_Version[16];
extern INT16U File_Check_Val[2];
extern INT16U File_Length[2];
extern INT16U PKG_Length;
extern INT16U PKG_Sum;
extern INT16U PKG_Cnt;
extern INT16U Reserved;
/*******************Iap标志位***************/
extern INT8U  Iap_Update_Req_Flag ; //更新请求
extern INT8U  Iap_Enable_Flag; //Iap使能
extern INT8U  Iap_Start_Flag; //Iap启动
extern INT8U  Iap_Password_Flag; //Iap密码
extern INT8U  Iap_Baud_1152_Flag; //波特率115200
extern INT8U  Iap_Update_Flag; //升级过程中




void Iap_Status_Check(void);
void Iap_Update(void);

#endif
