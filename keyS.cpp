// Compile:
// g++ -O2 -o run .\keyS.cpp -L./C:/Windows/SysWOW64 -lwinmm -mwindows

#include <windows.h>
#include <mmsystem.h>
#include <algorithm>

#pragma comment(lib, "winmm.lib")


const char* KEY_PATHS[3] = { "wav\\key-1.wav", "wav\\key-3.wav", "wav\\key-4.wav" };
const char* KEY_DELETE_PATH = "wav\\key-del.wav";
const char* KEY_ENTER_PATH = "wav\\key-2.wav";



inline void sound( const char* path ) {
    PlaySound( path, NULL, SND_FILENAME | SND_ASYNC );
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow) {

    srand( 185679 );

    bool key_down[256] = { 0 };



    while (true) {

        // Backspace
        if (GetAsyncKeyState( 8 ) & 0x8000 && !key_down[8]) {

            key_down[8] = true;
            sound( KEY_DELETE_PATH );
        }

        // Enter
        if (GetAsyncKeyState( 13 ) & 0x8000 && !key_down[13]) {

            key_down[13] = true;
            sound( KEY_ENTER_PATH );
        }



        // Other Keys
        for (int button = 9; button < 13; ++button) {
            if (GetAsyncKeyState( button ) & 0x8000 && !key_down[button]) {

                key_down[button] = true;
                sound( KEY_PATHS[rand() % 2] );

                break;
            }
        }

        // Other Keys
        for (int button = 14; button < 256; ++button) {
            if (GetAsyncKeyState( button ) & 0x8000 && !key_down[button]) {

                key_down[button] = true;
                sound( KEY_PATHS[rand() % 2] );

                break;
            }
        }





        // Reset if key up (not down)
        for (int button = 8; button < 256; ++button) {
            if (!(GetAsyncKeyState( button ) & 0x8000)) {
                key_down[button] = false;
            }
        }





        Sleep(20);
    }
}