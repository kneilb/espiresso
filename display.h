#ifndef __display_h
#define __display_h

//-----------------------------------------------------------------------------

#include <string>
#include <thread>
#include <mutex>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//-----------------------------------------------------------------------------

class Display {
public:
	Display();

	virtual ~Display();

	Display & updateTemperature( double degrees );

    Display & updatePressure( double pressure );

	Display & updateLevel( double level );

    Display & updateTime( double time );

    Display & setPowerOn( bool powerOn );

    Display & setPumpOn( bool pumpOn );

    Display & setMessage( const std::string& message );

private:
	bool open();

	void close();

	/// Rendering thread worker
	void worker();

	/// Render one frame
	void render();

	void drawText(
		TTF_Font *font,
		short x, short y,
		const std::string & text,
		SDL_Color foregroundColour,
		SDL_Color backgroundColour
	);

private:
	SDL_Surface *m_display;	    ///< Display surface
	TTF_Font	*m_font;
    TTF_Font    *m_smallFont;   ///< Small font
    SDL_Surface *m_powerIcon;   ///< Power icon image
    SDL_Surface *m_pumpIcon;    ///< Pump icon image

	int			m_width;	///< Width of display in pixels
	int			m_height;	///< Height of display in pixels

	bool		m_run;		///< Should thread continue to run?
	bool		m_dirty;	///< Does the display need updating?

	double 		m_degrees;	///< Temperature in degrees
    double      m_pressure; ///< Pressure display
	double		m_level;	///< Water level display
    double      m_time;     ///< Shot time display
    bool        m_powerOn;  ///< Power on display
    bool        m_pumpOn;   ///< Pump on display
    std::string m_message;  ///< Message text

    /// Rendering thread
    std::thread m_thread;

    /// Mutex to control access to shared memory
    mutable std::mutex m_mutex;
};

//-----------------------------------------------------------------------------

#endif//__display_h

