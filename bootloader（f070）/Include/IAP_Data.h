#ifndef __IAP_DATA_H
#define __IAP_DATA_H
#include "Include.h"



/*************IAP Status*************/
#define IAP_NO_SUPPORT         0x0000 //�豸��֧��IAP
#define IAP_Free               0x0001	//δ���������Ѿ����
#define IAP_Ready              0x0002	//����IAP��Ϣ
#define IAP_File_Transfer      0x0003	//�ļ�����
#define IAP_Codeing            0x0004	//Flash �������
#define IAP_Update_Fault       0x0005	//��������
#define IAP_Update_Succuss     0x0006	//�����ɹ�
/*************IAP Fault*************/
#define IAP_Disable            0x0001	//IAP δʹ��
#define IAP_Password_Err       0x0002	//IAP �������
#define IAP_Timeout            0x0003	//��ʱ�˳�
#define IAP_Cancel             0x0004	//�˳�/ȡ��
#define IAP_Model_Err          0x0005	//�ͺŲ�ƥ��
#define IAP_Firmware_Err       0x0006	//�̼��汾��ƥ��
#define IAP_Update_Fail        0x0007	//�Զ�����ʧ��
#define IAP_Flash_Over         0x0008	//����ռ䲻��
#define IAP_Check_Fail         0x0009	//�ļ�CRC У��ʧ��
#define IAP_Comm_Err           0x000A	//�ӻ�ͨ���쳣


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
/*******************Iap��־λ***************/
extern INT8U  Iap_Update_Req_Flag ; //��������
extern INT8U  Iap_Enable_Flag; //Iapʹ��
extern INT8U  Iap_Start_Flag; //Iap����
extern INT8U  Iap_Password_Flag; //Iap����
extern INT8U  Iap_Baud_1152_Flag; //������115200
extern INT8U  Iap_Update_Flag; //����������




void Iap_Status_Check(void);
void Iap_Update(void);

#endif
