#ifndef MAIN
#define MAIN


// make sure to add $(SFML_SDK)\lib to the project properties under
// Linker/additional library directories
// to create a static build add SFML_STATIC to PreprocessorDefinitions under C++ project propeties

#ifndef  SFML_STATIC

 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
//#pragma comment(lib,"sfml-main-d.lib")
//#pragma comment(lib,"sfml-network-d.lib") 
#define NO_RANDOM
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-audio.lib") 
//#pragma comment(lib,"sfml-main.lib")
//#pragma comment(lib,"sfml-network.lib") 
#endif //_DEBUG 
#else
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-s-d.lib")
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"jpeg.lib")
#pragma comment(lib,"opengl32.lib")

#pragma comment(lib,"sfml-system-s-d.lib") 
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"sfml-window-s-d.lib") 
#pragma comment(lib,"winmm")
#pragma comment(lib,"gdi32")

#pragma comment(lib,"sfml-audio-s-d.lib") 
#pragma comment(lib,"flac.lib")
#pragma comment(lib,"ogg.lib")
#pragma comment(lib,"vorbisenc.lib")
#pragma comment(lib,"vorbisfile.lib")
#pragma comment(lib,"vorbis.lib")
#pragma comment(lib,"openal32.lib")
//#pragma comment(lib,"sfml-main-s-d.lib")
//#pragma comment(lib,"sfml-network-s-d.lib") 
//#pragma comment(lib,"ws2_32.lib")
#define NO_RANDOM
#else 
#pragma comment(lib,"sfml-graphics-s.lib") 
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"jpeg.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"sfml-system-s.lib") 
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"sfml-window-s.lib") 
#pragma comment(lib,"winmm")
#pragma comment(lib,"gdi32")
#pragma comment(lib,"sfml-audio-s.lib") 
#pragma comment(lib,"flac.lib")
#pragma comment(lib,"ogg.lib")
#pragma comment(lib,"vorbisenc.lib")
#pragma comment(lib,"vorbisfile.lib")
#pragma comment(lib,"vorbis.lib")
#pragma comment(lib,"openal32.lib")
//#pragma comment(lib,"sfml-main-s.lib")
//#pragma comment(lib,"sfml-network-s.lib") 
//#pragma comment(lib,"ws2_32.lib")
#endif //_DEBUG 
#endif // !SFML_STATIC



#endif // MAIN