#include "config.h"
/***************************************************************
*��    Ȩ������ŷķ�������Դ�Ƽ����޹�˾�����
*�ļ����ƣ�config.c
*�޸��ˣ�����ǿ
*�޸����ڣ�2019.06.20
*��    �����Ĵ�����Ķ�ȡ��д��
***************************************************************/
INT16U CFG_ParamCfg(INT16U *pusDataSource, INT16U usStartAddr, INT16U usLen)
{
	INT8U i,x;
	for(i = 0;i < PARAM_NUM;i++)
	{
		if(g_astrParamCfgTblAttr[i].usRdWrtAddr == usStartAddr)
		{
			x = i;
			break;
		}
	}
	for(i = 0;i < usLen;i++)
	{
		*(g_astrParamCfgTblAttr[x+i].unCfgDest) = *pusDataSource;
		pusDataSource++;
		if((x+i)>PARAM_NUM)
		break;
	}
	return 1;
}
INT16U CFG_LoadParam(INT16U *pusDataTarget, INT16U usStartAddr, INT16U usLen)
{
	INT8U i,x;
	for(i = 0;i < PARAM_NUM;i++)
	{
		if(g_astrParamCfgTblAttr[i].usRdWrtAddr == usStartAddr)
		{
			x = i;
			break;
		}
	}
	for(i = 0;i < usLen;i++)
	{
		*pusDataTarget = *(g_astrParamCfgTblAttr[x+i].unCfgDest);
		pusDataTarget++;
		if((x+i)>PARAM_NUM)
			break;
	}
	return 1;
}
