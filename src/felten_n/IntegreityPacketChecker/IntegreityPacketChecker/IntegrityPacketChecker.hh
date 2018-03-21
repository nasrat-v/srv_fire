#pragma once
#include <iostream>

#define	SIZE_PHOTO 8

enum CodeChecker
{
	WAIT,
	ERROR,
	D_PHOTO,
	S_PHOTO,
	D_PALETTE,
	S_PALETTE,
	D_CONNECT_CLE,
	D_CONNECT_CLG,
	D_INFO,
	S_INFO,
	OK_INFO,
	D_TYPE,
	S_TYPE,
	OK_TYPE,
	P_ANOMALI,
	P_ALERT
};

struct Packet
{
	int	c;
	char	*str;
};

class IntegrityPacketChecker
{
public:
	IntegrityPacketChecker();
	~IntegrityPacketChecker();
	bool	stateTrigerrer(CodeChecker State, struct Packet packet);
	bool	isPhotoPacketOk(struct Packet packet);
	bool	isPalettePacketOk();
	bool	isCLEPacketOk();
	bool	isCLGPacketOk();
	bool	isDInfoOk();
	bool	isDTypeOk();
	bool	isAnomalyOk();
	bool	isAlertOk();
};