#pragma once

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

class IntegrityPacketChecker
{
public:
	IntegrityPacketChecker();
	~IntegrityPacketChecker();
	void	setState(CodeChecker state);
	CodeChecker		getState();
	void	stateTrigerrer();
	bool	isPhotoPacketOk();
	bool	isPalettePacketOk();
private:
	CodeChecker	State;
};