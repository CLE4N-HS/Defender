#pragma once
#include "tools.h"

typedef enum gamepadXBOX gamepadXBOX;
enum gamepadXBOX {
	DPAD_UP = 0x0001,
	DPAD_DOWN = 0x0002,
	DPAD_LEFT = 0x0004,
	DPAD_RIGHT = 0x0008,
	START = 0x0010,
	BACK = 0x0020,
	LEFT_THUMB = 0x0040,
	RIGHT_THUMB = 0x0080,
	LB = 0x0100,
	RB = 0x0200,
	A = 0x1000,
	B = 0x2000,
	X = 0x4000,
	Y = 0x8000
};

typedef enum stick stick;
enum stick {
	STICKL,
	STICKR,
	DPAD
};

typedef struct gamepad gamepad;
struct gamepad
{
	sf::Vector2f stickL;
	sf::Vector2f stickR;
	sf::Vector2f cross;
	float TriggerL;
	float TriggerR;
	int Bouton[14];
};


/// <summary>
/// check how many controller are connected 
/// </summary>
void GamepadDetection();

/// <summary>
/// check if a controller is connected/disconected and if you press a specific button and release it and check if a stick is moved
/// </summary>
/// <param name="_joystickId">the controller id. Exemple 0 for player 1, 1 for player 2...</param>
/// <param name="event">the event of the current window</param>
/// <param name="_window">the current window</param>
void GamepadManager(int _joystickId, sf::Event& _event/*, sfRenderWindow* _window*/);

/// <summary>
/// check if a specific button is currently pressed except L2/R2 and the arrow keys
/// </summary>
/// <param name="_joystickId">the id of the controller</param>
/// <param name="_button">the id of the button</param>
/// <param name="_window">the current window</param>
/// <returns>0 if the button is not pressed and 1 if the button is pressed</returns>
bool Gamepad_isButtonPressed(unsigned int _joystickId, gamepadXBOX _button/*, sfRenderWindow* _window*/);

/// <summary>
/// check if a specific button is currently pressed except L2/R2 and the arrow keys
/// </summary>
int Gamepad_isButtonPressedNF(unsigned int _joystickId, gamepadXBOX _button);

/// <summary>
/// function to get the stick inclinaison
/// </summary>
/// <param name="_joystickId">the controller ID</param>
/// <param name="_stick">the stick that you wanna see the inclinaison of (left stick is STICKL and right stick is STICKR)</param>
/// <param name="_window">the current window</param>
/// <returns>the stick inclinaison</returns>
sf::Vector2f Gamepad_getStickPos(unsigned int _joystickId, stick _stick/*, sfRenderWindow* _window*/);

/// <summary>
/// function to get the stick inclinaison
/// </summary>
/// <param name="_joystickId">the controller ID</param>
/// <param name="_stick">the stick that you wanna see the inclinaison of (left stick is STICKL and right stick is STICKR)</param>
/// <returns>the stick inclinaison</returns>
sf::Vector2f Gamepad_getStickPosNF(unsigned int _joystickId, stick _stick);

/// <summary>
/// function to get the normalized inclinaison of the stick can be useful for forwards
/// </summary>
/// <param name="_joystickId">the controller ID</param>
/// <param name="_stick">the stick that you wanna see the inclinaison of (left stick is STICKL and right stick is STICKR)</param>
/// <param name="_window">the current window</param>
/// <returns>the stick inclinaison</returns>
//sf::Vector2f Gamepad_getNormalizedStickPos(unsigned int _joystickId, stick _stick, sfRenderWindow* _window);


/// <summary>
/// function to get the normalized inclinaison of the stick can be useful for forwards
/// </summary>
/// <param name="_joystickId">the controller ID</param>
/// <param name="_stick">the stick that you wanna see the inclinaison of (left stick is STICKL and right stick is STICKR)</param>
/// <returns>the stick inclinaison</returns>
//sf::Vector2f Gamepad_getNormalizedStickPosNF(unsigned int _joystickId, stick _stick);

/// <summary>
/// make the controller vibrate
/// </summary>
/// <param name="controlerID">the controler id</param>
/// <param name="leftMotor">the left motor strenght</param>
/// <param name="rightMotor">the right motor strenght</param>
void setControlerVibration(int controlerID, float leftMotor, float rightMotor);

float Gamepad_getTriggerPos(unsigned int _joystickId, bool _leftTrigger/*, sfRenderWindow* _window*/);
