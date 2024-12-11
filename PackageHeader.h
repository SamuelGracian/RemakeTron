#pragma once
#include <iostream>

#include "PackageType.h"

struct PackageHeader
{
	PackageType type;
	size_t size;
	int playerIndex;
	char message[50];
};

struct AuthenticationData
{
	std::string username;
	std::string password;
};

struct ChatData
{
	char message[256];
};

