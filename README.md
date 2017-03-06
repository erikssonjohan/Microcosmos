# TNM094-Media-navigering
Medietekniskt kandidatprojekt: Media-navigering genom materiella gränssnitt




####Building with CMake and Visual Studio
1. Build with CMake 
  * Use available compiler (14 2015 win64)
  * Set SDL2_INCLUDE_DIR to sdl2/include
  * Set SDL2_LIBRARY to sdl2/lib/x86/SDL2.lib for 32bit or sdl2/lib/x64/SDL2.lib for 64bit
  * Set SDL2MAIN_LIBRARY to sdl2/lib/x86/SDL2main.lib for 32bit or sdl2/lib/x64/SDL2main.lib for 64bit 
2. Generate files and open with Visual Studio
3. Under coniguration properties, VC++ Directories set Include Directories to your SDL2 Include directory
4. Set VC++ Library Directories to your SDL2 lib x86 or x64 folder depending on your CMake build settings
5. Under Linker, Input, add SDL2.lib and SDL2main.lib to your Additional Dependencies 
6. Under Linker, System set SubSystem to be CONSOLE
7. Add SDL2.lib to your Debug folder after building
