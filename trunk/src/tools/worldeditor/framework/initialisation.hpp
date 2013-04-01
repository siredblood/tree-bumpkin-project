#ifndef WE_INITIALISATION_HPP
#define WE_INITIALISATION_HPP

#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include <iostream>


/**
 *	This class exists purely to move code out of app.cpp
 */
class Initialisation
{
public:
	static bool initApp( HINSTANCE hInstance, HWND hWndInput, HWND hWndGraphics );
	static void finiApp();

	static HINSTANCE s_hInstance;
	static HWND s_hWndInput;
	static HWND s_hWndGraphics;

private:
	static bool initGraphics( HINSTANCE hInstance, HWND hWnd );
	static void finaliseGraphics();

	static bool initScripts();
	static void finaliseScripts();

	static bool initTiming();
	static bool initConsoles();
	static void initSound();
	static bool initErrorHandling();

	Initialisation(const Initialisation&);
	Initialisation& operator=(const Initialisation&);

	friend std::ostream& operator<<( std::ostream&, const Initialisation& );
};


#ifdef CODE_INLINE
#include "initialisation.ipp"
#endif


#endif // WE_INITIALISATION_HPP
