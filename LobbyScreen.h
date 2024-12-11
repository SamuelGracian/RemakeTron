#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <map>

#include "Entities.h"
#include "PackageHeader.h"

using std::vector;
using std::string;

class LobbyScreen : public Entities
{
public:

	//constructor
	LobbyScreen();
	//desctructor
	~LobbyScreen() = default;

	void SendChatMessage(const sf::IpAddress& serverip,unsigned short serverport, const string message);
	void RecieveMessages();
	void HandleInput(const sf::Event& myevent, sf::UdpSocket& udpSocket, const sf::IpAddress& serverIp, unsigned short serverPort);
	void HandleMessageServer(int SenderIndex, const string& message);
	void Render(sf::RenderWindow& window) override;
	void Update(float DeltaTime) override;
	void Clean() override;

private:

	//functions
	void StartPlayerColors();
	void AddMessage(int Senderindex, const string& message);
	//variables
	string msCurrentInput;		//Current message
	vector < std::pair < string, sf::Color >> mMessagesVector;		//Chat messages
	std::map <int, sf::Color> mPlayerColors;		//Player colors
	sf::Font mMessageFont;		//Font for the messages
	sf::Text mMessageText;		//Text for the messages
	sf::RectangleShape mBackground;		//Background for the chat
	unsigned int miMaxMessages;		//Max messages to show

	sf::UdpSocket mUdpSocket;		//Udp socket
};

