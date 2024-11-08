#include <psp2/ctrl.h> // Include the necessary header for user input
#include <string>

class Button
{
    int mKey;
    bool mIsPressed;

public:
    Button(const int pKey);
    ~Button() = default;

    const int GetKey() { return mKey; }
    const std::string GetState() { return mIsPressed ? "true" : "false";}
    void SetKey(const bool pState) { mIsPressed = pState; }
    const bool CheckKey(SceCtrlData &padData);
    const bool CheckButtonDown(SceCtrlData &padData);
    
};