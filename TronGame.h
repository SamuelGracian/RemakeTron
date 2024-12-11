#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <thread>
#include <fstream>
#include <memory>

#include "PackageHeader.h"
#include "Entities.h"
#include "ResourceManager.h"
#include "MainmenuScreen.h"
#include "LobbyScreen.h"

using std::string;

class Tron_Game
{
public:

	////////////struct to save player info////////////
	struct mPlayerInfo
	{
		std::string Username;
		int PlayerIndex;
	};

	/// <summary>
	/// Load the resources of the game,
	/// Add textures to the map
	/// Load textures
	/// Creates entities lists
	/// Add entities to the list
	/// </summary>
	void Load_Resources();

	/// <summary>
	/// Connect to the UDP server
	/// </summary>
	void Connect_to_UDP_Server();

	/// <summary>
	/// Create the window (render window)
	/// </summary>
	void Create_Window();

	/// <summary>
	/// Main game loop
	/// </summary>
	void Run_Game();

	/// <summary>
	/// Handle the events of the window
	/// </summary>
	void Handle_event(const sf::Event& myevent);

	/// <summary>
	/// Get the window
	/// </summary>
	/// <returns> Pointer to render window</returns>
	sf::Window& GetWindow();

	//MainMenu m_myMainMenu;
/// <summary>
/// Get the instance of the Tron_Game class
/// </summary>
/// <returns> reference to the instance of the tron game class </returns>
	static Tron_Game& GetInstance();


	/// <summary>
	/// Change the game state, window manager 
	/// </summary>
	/// <param name="State"> int represents the state that si going to be the current</param>
	void SetGameState(int state);

	/// <summary>
	/// Set the username of the player
	/// </summary>
	/// <param name="NewUser"></param>
	void SetUserName(const string& NewUser);

	//void SavePlayerInfo();


private:

	///////////Game state///////////////
	enum class GameState
	{
		MAIN_MENU = 0,
		Lobby = 1,
		PLAYING = 2,
		PAUSED = 3,
		GAME_OVER = 4
	};

	/////////////struct to save player info////////////
	/// <summary>
	/// Struct to save player info
	/// </summary>
	mPlayerInfo mPlayer;

	////////////////singleton ( constructor) //////////////////
	/// <summary>
	/// Constructor of the Tron_Game class
	/// </summary>
	Tron_Game();

	/////////////////// functions //////////////////////

	/// <summary>
	/// Process the events of the window closed window
	/// </summary>
	//void ProcessEvent();

	/// <summary>
	/// Function to update the entities according to the game state
	/// </summary>
	/// <param name="state"> </param>
	void UpdateEntities();

	/// <summary>
	///Render the entities in the list according to the game state
	/// </summary>
	void RenderEntities();

	/// <summary>
	/// Clean the memory, delete all in the stack
	/// </summary>
	void DeleteAll();

	/// <summary>
	/// Send input to the server (temporal function)
	/// </summary>
	//void SendInput(sf::UdpSocket& socket, Input input);

	///////////////////// Variables //////////////////////

	const size_t MaxUsernameSize = 20;
	const size_t MaxPasswordSize = 20;

	// Port to connect to the server
	/// <summary>
	/// Port to connect to the server
	/// </summary>s
	const unsigned int mgPort = 55001;

	// Delta time, time between frames
	const float mfDeltaTime = 1.0f / 60.0f;

	//Game Window
	sf::RenderWindow mpGameWindow;

	// Current game state
	/// <summary>
	/// Current game state
	/// </summary>
	GameState miCurrentState;

	/// <summary>
	/// Delete this, it is only for testing
	/// </summary>
	sf::RectangleShape mTestShape;
	//sf::Text mButtonText;
	//sf::Font mFont;
	//sf::Text mTitleText;

	//sf::Event::KeyPressed mKeyPressedEvent;


	sf::Event mKeyPressedEvent ;

	////////////input flags//////////////
	bool mbPressedButton = false;
	bool mbConnectedtoServer = false;


	/////////////lists of entities////////////
	/// <summary>
	/// List of entities
	///Entities are the objects that are going to be rendered
	/// </summary>
	std::unique_ptr <LobbyScreen> mpLobbyScreen = nullptr;
};