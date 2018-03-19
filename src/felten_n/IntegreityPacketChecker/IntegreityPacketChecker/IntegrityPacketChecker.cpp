// IntegreityPacketChecker.cpp : Defines the entry point for the console application.
//

#include "IntegrityPacketChecker.hh"

IntegrityPacketChecker::IntegrityPacketChecker() {}

IntegrityPacketChecker::~IntegrityPacketChecker() {}

bool IntegrityPacketChecker::stateTrigerrer(CodeChecker State, struct Packet packet)
{
	switch (State)
	{
	case ERROR:
		// ERROR !!
		break;
	case D_PHOTO:
		return (isPhotoPacketOk(packet));
		break;
	case D_PALETTE:
		return (isPalettePacketOk());
		break;
	case D_CONNECT_CLE:
		return (isCLEPacketOk());
		break;
	case D_CONNECT_CLG:
		return (isCLGPacketOk());
		break;
	case D_INFO:
		return (isDInfoOk());
		break;
	case D_TYPE:
		return (isDTypeOk());
		break;
	case P_ANOMALI:
		return (isAnomalyOk());
		break;
	case P_ALERT:
		return (isAlertOk());
		break;
	default:
		break;
	}
}

bool IntegrityPacketChecker::isPhotoPacketOk(struct Packet packet)
{
	if (sizeof(packet) == SIZE_PHOTO)
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

bool IntegrityPacketChecker::isCLEPacketOk()
{
	if (/* Taille Palette == ok*/1 == 1)
		return true;
	else
		return false;
}

bool IntegrityPacketChecker::isCLGPacketOk()
{
	if (/* Taille Palette == ok*/1 == 1)
		return true;
	else
		return false;
}

bool IntegrityPacketChecker::isDInfoOk()
{
	if (/* Taille Palette == ok*/1 == 1)
		return true;
	else
		return false;
}

bool IntegrityPacketChecker::isDTypeOk()
{
	if (/* Taille Palette == ok*/1 == 1)
		return true;
	else
		return false;
}

bool IntegrityPacketChecker::isAnomalyOk()
{
	if (/* Taille Palette == ok*/1 == 1)
		return true;
	else
		return false;
}

bool IntegrityPacketChecker::isAlertOk()
{
	if (/* Taille Palette == ok*/1 == 1)
		return true;
	else
		return false;
}


int main()
{
	IntegrityPacketChecker	test;
	struct Packet			test2;

	test2.c = 4;
	//test2.str = NULL;
	//test2.str = (char*)malloc(512);

	if (test.stateTrigerrer(D_PHOTO, test2))
		std::cout << "ok" << std::endl;
	else
		std::cout << "ko" << std::endl;
	return 0;
}

/*
Impossible de check la taille check le contenu !
Du coup il faut savoir combien de char il y aura dans le char * qu'on va
recevoir et qu'on les comptes.

- Voir avec boubou pour le Packet.

- voir avec xuan / maurel pour la taille de la photo envoyée.

- voir avec val/boubou pour si on fait une machine à état ou si
on se prend pas la tête et on passe une valeur de l'énum a la
fct et pour la valeur de retour de la fct.
*/