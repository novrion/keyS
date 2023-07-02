/* NOTICE: Run in vs with the lib: winmm.lib (Properties -> Linker -> Input -> Additional Dependencies) */

#include <Windows.h>
#include <algorithm>


//const wchar_t* KEY_PATHS[4] = { L"wav\\key-1.wav", L"wav\\key-2.wav", L"wav\\key-3.wav", L"wav\\key-4.wav" };

const wchar_t* KEY_PATHS[3] = { L"wav\\key-1.wav", L"wav\\key-3.wav", L"wav\\key-4.wav" };
const wchar_t* KEY_DELETE_PATH = L"wav\\key-del.wav";



inline void sound( const wchar_t* path ) {
    PlaySound( path, NULL, SND_FILENAME | SND_ASYNC );
}


int main() {

    srand( 185679 );

    bool key_down[256] = { 0 };



    while (true) {

        // Backspace
        if (GetAsyncKeyState( 8 ) & 0x8000 && !key_down[8]) {

            key_down[8] = true;
            sound( KEY_DELETE_PATH );
        }

        // Other Keys
        for (int button = 9; button < 256; ++button) {
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
    }



    return 0;
}
