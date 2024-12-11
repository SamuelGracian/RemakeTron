#include "LobbyScreen.h"

LobbyScreen::LobbyScreen()
{
	//set the max messages
	miMaxMessages = 10;
	//load the font
	if (!mMessageFont.loadFromFile("C:/Users/sammy/source/repos/RemakeTron/RemakeTron/Resources/pixely[1].ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
	//set the text
	mMessageText.setFont(mMessageFont);
	mMessageText.setCharacterSize(20);
	mMessageText.setFillColor(sf::Color::White);
	mMessageText.setPosition(sf::Vector2f(50, 50));
	//set the background
	mBackground.setSize(sf::Vector2f(800, 600));
	mBackground.setFillColor(sf::Color(0, 0, 0, 150));
	mBackground.setPosition(sf::Vector2f(350, 200));
	StartPlayerColors();
}


void LobbyScreen::AddMessage(int  SenderIndex, const string& message)
{
	//set a default color
	sf::Color Messagecolor = sf::Color::White;

	if (mPlayerColors.find(SenderIndex) != mPlayerColors.end())
	{
		Messagecolor = mPlayerColors[SenderIndex];
	}
	mMessagesVector.emplace_back(message, Messagecolor);
	if (mMessagesVector.size() > miMaxMessages)
	{
		mMessagesVector.erase(mMessagesVector.begin());
	}
}

void LobbyScreen::SendChatMessage ( const sf::IpAddress& serverip, unsigned short serverport, const string message)
{
	std::vector <char> Buffer;

	PackageHeader header
	{
		PackageType::Chat,
		message.size(),
		-1,
		static_cast<char>(message.size())
	};
	Buffer.resize(sizeof(PackageHeader));
    _memccpy(Buffer.data(), &header, sizeof(PackageHeader), sizeof(PackageHeader));

	Buffer.insert(Buffer.end(), message.begin(), message.end());

	if (mUdpSocket.send(Buffer.data(), Buffer.size(), serverip, serverport) != sf::Socket::Status::Done)
	{
		std::cout << "Failed to send message" << std::endl;
	}

}

void LobbyScreen::RecieveMessages()
{
	std::vector <char> Buffer(1024);
	std::size_t Received = 0;
	sf::IpAddress Senderip;
	unsigned short Senderport;

	//receive the message
	if (mUdpSocket.receive(Buffer.data(), Buffer.size(), Received, Senderip, Senderport) == sf::Socket::Status::Done)
	{
		if (Received >= sizeof(PackageHeader))
		{
			PackageHeader header;
			memcpy(&header, Buffer.data(), sizeof(PackageHeader));

			if (header.type == PackageType::Chat)
			{
				string message(Buffer.begin() + sizeof(PackageHeader), Buffer.end());
				HandleMessageServer(header.playerIndex, message);
			}
		}
	}

}

void LobbyScreen::HandleInput(const sf::Event& myevent, sf::UdpSocket& udpSocket, const sf::IpAddress& serverIp, unsigned short serverPort)
{
    if (myevent.type == sf::Event::TextEntered)
    {

        if (myevent.text.unicode == '\b' && !msCurrentInput.empty())
        {
            msCurrentInput.pop_back();
        }

        else if (myevent.text.unicode == '\r')
        {
            if (!msCurrentInput.empty())
            {
				HandleMessageServer(-1, msCurrentInput);

                SendChatMessage(serverIp, serverPort, msCurrentInput);

                msCurrentInput.clear();
            }
        }

        else if (myevent.text.unicode < 128)
        {
            msCurrentInput += static_cast<char>(myevent.text.unicode);
        }
    }
}


void LobbyScreen::HandleMessageServer(int SenderIndex, const string& message)
{
	AddMessage(SenderIndex, message);
}

void LobbyScreen::Render(sf::RenderWindow& window)
{
    const float initialYOffset = 100.0f;
    const float yOffsetIncrement = 20.0f;
    const float xPosition = 20.0f;

    window.draw(mBackground);

    float yOffset = initialYOffset;
    for (const auto& messagePair : mMessagesVector)
    {
        const std::string& msg = messagePair.first;
        const sf::Color& color = messagePair.second;

        mMessageText.setString(msg);
        mMessageText.setFillColor(color);
        mMessageText.setPosition(xPosition, yOffset);
        window.draw(mMessageText);
        yOffset += yOffsetIncrement;
    }

    // Draw current input
    mMessageText.setString(">> " + msCurrentInput);
    mMessageText.setFillColor(sf::Color::White);
    mMessageText.setPosition(xPosition, mBackground.getPosition().y + mBackground.getSize().y - 30.0f);
    window.draw(mMessageText);
}


void LobbyScreen::StartPlayerColors()
{
	//set the player colors
	mPlayerColors[0] = sf::Color::Red;
	mPlayerColors[1] = sf::Color::Blue;
	mPlayerColors[2] = sf::Color::Green;
	mPlayerColors[3] = sf::Color::Yellow;
	mPlayerColors[4] = sf::Color::Magenta;
	mPlayerColors[5] = sf::Color::Cyan;
}


void LobbyScreen::Update(float DeltaTime)
{
	RecieveMessages();
}

void LobbyScreen::Clean()
{
	//call the destructor
	//~LobbyScreen();
}
