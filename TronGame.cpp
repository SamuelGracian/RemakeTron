#include "TronGame.h"
#include "TronGame.h" 
#include <iostream>

#include "MainMenuScreen.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

Tron_Game::Tron_Game()
{
	miCurrentState = GameState::MAIN_MENU;
	mPlayer.Username = "Player";
}

void Tron_Game::Load_Resources()
{
	////ResourceManager& RManager = ResourceManager::GetInstance();
	//////add textures to map
	////RManager.AddTexture("");


	//////entities list
	////MainMenuButtons* mainMenu = new MainMenuButtons(); 
	////mMainMenuEntities.push_back(mainMenu);
	MainmenuScreen& mmainMenuScreen = MainmenuScreen::GetInstance();
	mpLobbyScreen = std::make_unique<LobbyScreen>();
}

void Tron_Game::UpdateEntities()
{
	switch (miCurrentState)
	{
	case GameState::MAIN_MENU:
	{
	}
	break;
	case GameState::Lobby:
	{
		//mpLobbyScreen->AddMessage(mPlayerInfo.PlayerIndex ,"welcome to the lobby");
	}
	break;
	case GameState::PAUSED:
	{
		//update paused
	}
	break;
	case GameState::GAME_OVER:
	{
		//update game over
	}
	break;
	default:
		// Handle invalid state
		cout << "Invalid state" << endl;
		break;
	}
}



Tron_Game& Tron_Game::GetInstance()
{
	static Tron_Game instance;
	return instance;
}



sf::Window& Tron_Game::GetWindow()
{
	return mpGameWindow;
}


void Tron_Game::Connect_to_UDP_Server()
{
	// Create a socket
	sf::UdpSocket socket;

	// Save the local host IP address
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

	// Create the package header
	PackageHeader header
	{
		PackageType::Connect,
		// No more data to send 
		size_t(0u),
		-1
	};

	sf::sleep(sf::seconds(2));
	// Try to send the header to the server
	if (socket.send(&header, sizeof(PackageHeader), ip, mgPort) != sf::Socket::Status::Done)
	{
		cout << "Failed to connect to the server" << endl;
		return;
	}

	cout << "Connected to the server" << ip << endl;
	mbConnectedtoServer = true;
}

//////////////////////////////////


void Tron_Game::SetGameState(int State)
{
	switch (State)
	{
	case 0:
		miCurrentState = GameState::MAIN_MENU;
		break;
	case 1:
		miCurrentState = GameState::Lobby;
		break;
	case 2:
		miCurrentState = GameState::PLAYING;
		break;
	case 3:
		miCurrentState = GameState::PAUSED;
	case 4:
		miCurrentState = GameState::GAME_OVER;
		break;
	default:
		// Handle invalid state
		cout << "Invalid state" << endl;
		break;
	}
}


void Tron_Game::Create_Window()
{
	//mGameWindow.create(sf::VideoMode::getDesktopMode(), "tron");
	mpGameWindow.create(sf::VideoMode(1500,1000), "Tron");
	mpGameWindow.setActive();
}


void Tron_Game::RenderEntities()
{
	switch (miCurrentState)
	{
	case GameState::MAIN_MENU:
	{
		MainmenuScreen& mmainMenuScreen = MainmenuScreen::GetInstance();
		mmainMenuScreen.Render(mpGameWindow);
		break;
	}
	case GameState::Lobby:
	{
		mpLobbyScreen->Render(mpGameWindow);
		break;
	}
	default:
		break;
	}
}

void Tron_Game::DeleteAll()
{
}


void Tron_Game::SetUserName(const string& NewUser)
{
	mPlayer.Username = NewUser;
}




void Tron_Game::Handle_event(const sf::Event& myevent)
{
	if (myevent.type == sf::Event::KeyPressed)
	{
		if (miCurrentState == GameState::MAIN_MENU)
		{
			if (myevent.key.code == sf::Keyboard::Key::Enter)
			{
				MainmenuScreen& mmainMenuScreen = MainmenuScreen::GetInstance();
					mmainMenuScreen.OnCommand();
			}
		}
		if (miCurrentState == GameState::Lobby)
		{
			//mpLobbyScreen->HandleInput(myevent);
		}
	}
}


//void Tron_Game::Run_Game()
//{
//    Create_Window();
//	Load_Resources();
//
//	//if (!mbConnectedtoServer)
//	//{
//	//	Connect_to_UDP_Server();
//	//}
//
//    while (mpGameWindow-> isOpen())
//    {
//
//        while (std::optional<sf::Event> myEvent = mpGameWindow->pollEvent())
//        {
//			//Process event function if the window is open
//            // handle event
//			if(myEvent.has_value()) handle_event(myEvent);
//        }
//		UpdateEntities();
//
//		mpGameWindow->clear();
//        //update y render 
//		RenderEntities(miCurrentState);
//		mpGameWindow->display();
//    }
//    //close app
//	DeleteAll();
//}

//void Tron_Game::Handle_event(const sf::Event& MyEvent)
//{
//	if (miCurrentState == GameState::MAIN_MENU)
//	{
//		for (auto& button : mMainMenu->mButtons)
//		{
//			switch (mKeyPressedEvent.code)
//			{
//			case sf::Keyboard::Key::Enter:
//				button.OnCommand();
//			}
//		}
//	}
//}

void Tron_Game::Run_Game()
{
	Create_Window();
	Load_Resources();

    while (mpGameWindow.isOpen())
    {
        sf::Event CurrentEvent;
        while (mpGameWindow.pollEvent(CurrentEvent))
        {
            Handle_event(CurrentEvent);
        }
        UpdateEntities();

        mpGameWindow.clear();

        RenderEntities();

        mpGameWindow.display();
    }

    DeleteAll();
    }
