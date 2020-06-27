#if !defined _RULES_H
#define _RULES_H

typedef struct _RuleInfo  //定义过滤规则的数据结构
{
	unsigned long sourceIp;
	unsigned long sourceMask;
	unsigned short sourcePort;

	unsigned long destinationIp;
	unsigned long destinationMask;
	unsigned short destinationPort;

	unsigned int protocol;

	int action;

}RuleInfo, *PRuleInfo;

#endif