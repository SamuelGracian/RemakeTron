#include "MainmenuScreen.h"
#include <iostream>

using std::cout;
using std::endl;

///mMainMenu = std::make_unique<MainmenuScreen>(sf::Vector2f(200, 100), sf::Vector2f(500, 100), "Start");

MainmenuScreen::MainmenuScreen()
{
    mServerIp;
    mbConnectedtoServerUdp = false;
    mbConnectedtoServerTcp = false;

    //Create the buttons, add them to the list
    ///parameters: size, position, color, name
    mButtons.emplace_back(sf::Vector2f(400, 100), sf::Vector2f(500, 90), sf::Color::White, "Title");
    mButtons.emplace_back(sf::Vector2f(400, 100), sf::Vector2f(500, 500), sf::Color::Cyan ,  "Start");

    //set the font
    if (!mFont.loadFromFile("C:/Users/sammy/source/repos/RemakeTron/RemakeTron/Resources/pixely[1].ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }
    //set the text
	//title
    mTitleText.setFont(mFont);
    mTitleText.setString("tron");
    mTitleText.setCharacterSize(50);
    mTitleText.setFillColor(sf::Color::Black);
    mTitleText.setPosition(sf::Vector2f(600, 100));
	//connect to lobby button
    mConnectButtonText.setFont(mFont);
    mConnectButtonText.setString("connect  to  lobby");
    mConnectButtonText.setCharacterSize(30);
    mConnectButtonText.setFillColor(sf::Color::Black);
    mConnectButtonText.setPosition(sf::Vector2f(530, 530));

}

void MainmenuScreen::ConnectToServer()
{
    sf::TcpSocket tcpSocket;

    while (!mbConnectedtoServerTcp)
    {
        if (tcpSocket.connect(mServerIp.getLocalAddress(), mgPort) != sf::Socket::Status::Done)
        {
            std::cout << "Failed to connect to the server" << std::endl;
            return;
        }
        mbConnectedtoServerTcp = true;
    }

    std::cout << "Connected to the server" << std::endl;

    //Create udp socket

    sf::UdpSocket udpSocket;

    //bind the udp socket
    if (udpSocket.bind(mgUdpPort) != sf::Socket::Status::Done)
    {
        std::cout << "Failed to bind the udp socket" << std::endl;
        return;
    }
    std::cout << "Binded the udp socket" << std::endl;

    //create a package header
    PackageHeader header
    {
        PackageType::Connect,
            size_t(0u),
            -1,
            "connection"
    };

    if (udpSocket.send(&header, sizeof(PackageHeader), mServerIp, mgPort) != sf::Socket::Status::Done)
    {
        std::cout << "Failed to connect to the server" << std::endl;
        return;
    }
    std::cout << "Connected to the server" << mServerIp << std::endl;
	Tron_Game& tron = Tron_Game::GetInstance();
	tron.SetGameState(1);
    mbConnectedtoServerUdp = true;

    if (mbConnectedtoServerUdp)
    {
        ReceieveDatafromServer(udpSocket, header);
        Tron_Game& tron = Tron_Game::GetInstance();
        tron.SetGameState(1);
    }

}


void MainmenuScreen::Update(float DeltaTime)
{

}

void MainmenuScreen::Clean()
{

}

void MainmenuScreen::Render(sf::RenderWindow& window)
{
    //Render the buttons in the list
    for (auto& button : mButtons)
    {
        button.Render(window);
    }
	window.draw(mTitleText);
	window.draw(mConnectButtonText);
}

void MainmenuScreen::OnCommand()
{
    std::cout << "Enter key pressed" << std::endl;
    //Connect to the server
    ConnectToServer();
}

void MainmenuScreen::ReceieveDatafromServer(sf::UdpSocket& socket, PackageHeader& header)
{
    //create a buffer to receive data
    vector <char> Buffer(1024);
    std::size_t Received = 0;
    sf::IpAddress Sender;
    unsigned short SenderPort;

    if (socket.receive(Buffer.data(), Buffer.size(), Received, Sender, SenderPort) == sf::Socket::Status::Done)
    {
        if (Received >= sizeof(PackageHeader))
        {
            memcpy(&header, Buffer.data(), sizeof(PackageHeader));
            cout << "Type: " << static_cast<int> (header.type) << endl;
            cout << "Size: " << header.size << endl;
            cout << "Player index: " << header.playerIndex << endl;
        }
        else
        {
            cout << "data too small for a valid package" << endl;
        }
    }
    else
    {
        cout << "Failed to receive data from server" << endl;
    }

}