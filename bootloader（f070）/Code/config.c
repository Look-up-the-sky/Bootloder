#include "config.h"
/***************************************************************
*版    权：苏州欧姆尼克新能源科技有限公司软件组
*文件名称：config.c
*修改人：沈仕强
*修改日期：2019.06.20
*描    述：寄存器表的读取和写入
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
