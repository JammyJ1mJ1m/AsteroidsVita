#include "Button.h"

Button::Button(const int pKey) :
mKey(pKey),
mIsPressed(false)
{ }

// get buytton
const bool Button::CheckKey(SceCtrlData &padData)
{
    // Detect button down event (only act if the button was not previously pressed)
    if ((padData.buttons & mKey) && !mIsPressed)
    {

        mIsPressed = true;                              // Mark the button as pressed in the current frame
    }
    // Detect button release (button was previously pressed but is not pressed anymore)
    else if (!(padData.buttons & mKey) && mIsPressed)
    {
        mIsPressed = false; // Mark the button as released in the current frame
    }
    return mIsPressed;
}

// get button down
const bool Button::CheckButtonDown(SceCtrlData &padData)
{
    // Detect button down event (only act if the button was not previously pressed)
    if ((padData.buttons & mKey) && !mIsPressed) {
        mIsPressed = true;  // Mark the button as pressed in the current frame
        return true;        // Logic to run once per press
    }
    // Detect button release event
    else if (!(padData.buttons & mKey) && mIsPressed) {
        mIsPressed = false; // Mark the button as released
    }

    // Return false if the button is not pressed or already processed
    return false;
}