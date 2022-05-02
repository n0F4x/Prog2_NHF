////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_EVENT_HPP
#define SFML_EVENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFMLKeyboard.hpp"
#include "SFMLMouse.hpp"


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Defines a system event and its parameters
///
////////////////////////////////////////////////////////////
class Event
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Keyboard event parameters (KeyPressed, KeyReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct KeyEvent
    {
        Keyboard::Key code;    ///< Code of the key that has been pressed
        bool          alt;     ///< Is the Alt key pressed?
        bool          control; ///< Is the Control key pressed?
        bool          shift;   ///< Is the Shift key pressed?
        bool          system;  ///< Is the System key pressed?
        KeyEvent(Keyboard::Key code_ = Keyboard::None, bool alt_ = false, bool control_ = false, bool shift_ = false, bool system_ = false) :
            code{code_}, alt{alt_}, control{control_}, shift{shift_}, system{system_}
        {}
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse move event parameters (MouseMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseMoveEvent
    {
        int x; ///< X position of the mouse pointer, relative to the left of the owner window
        int y; ///< Y position of the mouse pointer, relative to the top of the owner window
        MouseMoveEvent(int x_ = 0, int y_ = 0) : x{ x_ }, y{ y_ } {}
        Vector2i getPosition() const { return Vector2i{ x, y }; }
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse buttons events parameters
    ///        (MouseButtonPressed, MouseButtonReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseButtonEvent
    {
        Mouse::Button button; ///< Code of the button that has been pressed
        int           x;      ///< X position of the mouse pointer, relative to the left of the owner window
        int           y;      ///< Y position of the mouse pointer, relative to the top of the owner window
        MouseButtonEvent(Mouse::Button button_ = Mouse::None, int x_ = 0, int y_ = 0) :
            button{button_}, x{x_}, y{y_}
        {}
        Vector2i getPosition() const { return Vector2i{x, y}; }
    };

    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the different types of events
    ///
    ////////////////////////////////////////////////////////////
    enum EventType
    {
        None,
        Closed,                 ///< The window requested to be closed (no data)
        KeyPressed,             ///< A key was pressed (data in event.key)
        KeyReleased,            ///< A key was released (data in event.key)
        MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
        MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
        MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    EventType type; ///< Type of the event

    KeyEvent              key;               ///< Key event parameters (Event::KeyPressed, Event::KeyReleased)
    MouseMoveEvent        mouseMove;         ///< Mouse move event parameters (Event::MouseMoved)
    MouseButtonEvent      mouseButton;       ///< Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)

    Event(EventType type_ = None, KeyEvent key_ = {}, MouseMoveEvent mouseMove_ = {}, MouseButtonEvent mouseButton_ = {}) :
        type{type_}, key{key_}, mouseMove{mouseMove_}, mouseButton{mouseButton_} 
    {}
};

} // namespace sf


#endif // SFML_EVENT_HPP


////////////////////////////////////////////////////////////
/// \class sf::Event
/// \ingroup window
///
/// sf::Event holds all the informations about a system event
/// that just happened. Events are retrieved using the
/// sf::Window::pollEvent and sf::Window::waitEvent functions.
///
/// A sf::Event instance contains the type of the event
/// (mouse moved, key pressed, window closed, ...) as well
/// as the details about this particular event. Please note that
/// the event parameters are defined in a union, which means that
/// only the member matching the type of the event will be properly
/// filled; all other members will have undefined values and must not
/// be read if the type of the event doesn't match. For example,
/// if you received a KeyPressed event, then you must read the
/// event.key member, all other members such as event.mouseMove
/// or event.text will have undefined values.
///
/// Usage example:
/// \code
/// sf::Event event;
/// while (window.pollEvent(event))
/// {
///     // Request for closing the window
///     if (event.type == sf::Event::Closed)
///         window.close();
///
///     // The escape key was pressed
///     if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
///         window.close();
///
///     // The window was resized
///     if (event.type == sf::Event::Resized)
///         doSomethingWithTheNewSize(event.size.width, event.size.height);
///
///     // etc ...
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
