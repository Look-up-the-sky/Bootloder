#include "Check.h"
/***************************************************************
*版    权：苏州欧姆尼克新能源科技有限公司软件组
*文件名称：check.c
*修改人：沈仕强
*修改日期：2019.06.20
*描    述：校验函数
***************************************************************/
INT16U crc16(INT8U *pucDataBuf, INT16U usLen) 
{
	INT16U usBitCnt;
	INT16U usByteCnt;
	INT16U usCrcData;
	
	usCrcData = 0xFFFF;
	for(usByteCnt = 0;usByteCnt < usLen;usByteCnt++)
	{
		usCrcData ^=((*pucDataBuf)&0xFFFF);
		for(usBitCnt = 0;usBitCnt <8;usBitCnt++)
		{
			if(usCrcData & 0x0001)
			{
				usCrcData>>=1;
				usCrcData^=0xA001;
			}
			else
			{
				usCrcData>>=1;
			}
		}
		pucDataBuf++;
	}
	return(usCrcData);
}
