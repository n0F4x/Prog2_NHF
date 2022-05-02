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

#ifndef SFML_MOUSE_HPP
#define SFML_MOUSE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFMLVector2.hpp"


namespace sf
{
class Window;

////////////////////////////////////////////////////////////
/// \brief Give access to the real-time state of the mouse
///
////////////////////////////////////////////////////////////
class Mouse
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Mouse buttons
    ///
    ////////////////////////////////////////////////////////////
    enum Button
    {
        None,
        Left,       ///< The left mouse button
        Right,      ///< The right mouse button
        Middle,     ///< The middle (wheel) mouse button
        XButton1,   ///< The first extra mouse button
        XButton2,   ///< The second extra mouse button
    };
};

} // namespace sf


#endif // SFML_MOUSE_HPP


////////////////////////////////////////////////////////////
/// \class sf::Mouse
/// \ingroup window
///
/// sf::Mouse provides an interface to the state of the
/// mouse. It only contains static functions (a single
/// mouse is assumed), so it's not meant to be instantiated.
///
/// This class allows users to query the mouse state at any
/// time and directly, without having to deal with a window and
/// its events. Compared to the MouseMoved, MouseButtonPressed
/// and MouseButtonReleased events, sf::Mouse can retrieve the
/// state of the cursor and the buttons at any time
/// (you don't need to store and update a boolean on your side
/// in order to know if a button is pressed or released), and you
/// always get the real state of the mouse, even if it is
/// moved, pressed or released when your window is out of focus
/// and no event is triggered.
///
/// The setPosition and getPosition functions can be used to change
/// or retrieve the current position of the mouse pointer. There are
/// two versions: one that operates in global coordinates (relative
/// to the desktop) and one that operates in window coordinates
/// (relative to a specific window).
///
/// Usage example:
/// \code
/// if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
/// {
///     // left click...
/// }
///
/// // get global mouse position
/// sf::Vector2i position = sf::Mouse::getPosition();
///
/// // set mouse position relative to a window
/// sf::Mouse::setPosition(sf::Vector2i(100, 200), window);
/// \endcode
///
/// \see sf::Joystick, sf::Keyboard, sf::Touch
///
////////////////////////////////////////////////////////////
