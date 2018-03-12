// IntegreityPacketChecker.cpp : Defines the entry point for the console application.
//

#include "IntegrityPacketChecker.hh"

IntegrityPacketChecker::IntegrityPacketChecker()
{
	State = WAIT;
}

IntegrityPacketChecker::~IntegrityPacketChecker()
{
}

void IntegrityPacketChecker::setState(CodeChecker state)
{
	State = state;
}

CodeChecker IntegrityPacketChecker::getState()
{
	return State;
}

void IntegrityPacketChecker::stateTrigerrer()
{
	switch (State)
	{
	case ERROR:
		// ERROR !!
		break;
	case D_PHOTO:
		setState(S_PHOTO);
		break;
	case S_PHOTO:
		if (isPhotoPacketOk())
			setState(D_PALETTE);
		else
			setState(ERROR);
		break;
	case D_PALETTE:
		setState(S_PALETTE);
		break;
	case S_PALETTE:
		if (isPalettePacketOk())
			setState();
		else
			setState(ERROR);
		break;
	case D_CONNECT_CLE:
		break;
	case D_CONNECT_CLG:
		break;
	case D_INFO:
		break;
	case S_INFO:
		break;
	case OK_INFO:
		break;
	case D_TYPE:
		break;
	case S_TYPE:
		break;
	case OK_TYPE:
		break;
	case P_ANOMALI:
		break;
	case P_ALERT:
		break;
	default:
		break;
	}
}

bool IntegrityPacketChecker::isPhotoPacketOk()
{
	if (/* Taille Packet == ok*/1 == 1)
		return true;
	else
		return false;
}

bool IntegrityPacketChecker::isPalettePacketOk()
{
	if (/* Taille Palette == ok*/1 == 1)
		return true;
	else
		return false;
}


int main()
{
    return 0;
}

