#ifndef CONFIG_H
#define CONFIG_H

#include "Include.h"

#define	PARAM_NUM            42
typedef struct
{
	INT16U    usRdWrtAddr;
	INT16U*    unCfgDest;
}PARAM_CFG_TBL_STR;

extern const PARAM_CFG_TBL_STR g_astrParamCfgTblAttr[PARAM_NUM];
extern INT16U CFG_ParamCfg(INT16U *pusDataSource, INT16U usStartAddr, INT16U usLen);
extern INT16U CFG_LoadParam(INT16U *pusDataTarget, INT16U usStartAddr, INT16U usLen);


#endif
