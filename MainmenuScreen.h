#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <optional>

#include "TronGame.h"
#include "Entities.h"
#include "PackageHeader.h"
#include "Buttons.h"

using std::vector;

class MainmenuScreen
{
public:
    //MainmenuScreen(sf::Vector2f Size, sf::Vector2f Position, std::string Name);

    /// <summary>
    /// Default constructor
    /// Sets 3 buttons
    /// </summary>

	static MainmenuScreen& GetInstance()
	{
		static MainmenuScreen instance;
		return instance;
	}

    ~MainmenuScreen() = default;

    void Update(float DeltaTime);

    void Clean();

    void Render(sf::RenderWindow& window);

    /// <summary>
    /// 
    /// </summary>
    void OnCommand();

    /// <summary>
    /// Vector of buttons
    /// </summary>
    vector<Buttons> mButtons;

private:

    MainmenuScreen();

    //functions 
    /// <summary>
    /// Connect to the game server
    /// With udp and tcp
    /// </summary>
    void ConnectToServer();

    void ReceieveDatafromServer(sf::UdpSocket& socket, PackageHeader& header);

    //variables

    sf::Text mTitleText;
    sf::Text mConnectButtonText;

    sf::Font mFont;

    //////// flags ////////
    bool mbConnectedtoServerUdp;
    bool mbConnectedtoServerTcp;
    ///////// ports ///////
    static constexpr int mgPort = 55001;
    static constexpr int mgUdpPort = 55002;
    ///////// ip /////////
    sf::IpAddress mServerIp = sf::IpAddress::getLocalAddress();
};
