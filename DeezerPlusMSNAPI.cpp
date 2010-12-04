/**********************************************************\

  Auto-generated DeezerPlusMSNAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "windows.h"
#include <string>

#include "DeezerPlusMSNAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn DeezerPlusMSNAPI::DeezerPlusMSNAPI(DeezerPlusMSNPtr plugin, FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
DeezerPlusMSNAPI::DeezerPlusMSNAPI(DeezerPlusMSNPtr plugin, FB::BrowserHostPtr host) : m_plugin(plugin), m_host(host)
{
    registerMethod("echo",      make_method(this, &DeezerPlusMSNAPI::echo));
    registerMethod("testEvent", make_method(this, &DeezerPlusMSNAPI::testEvent));
	registerMethod("nowPlaying",  make_method(this, &DeezerPlusMSNAPI::nowPlaying));


    // Read-write property
    registerProperty("testString",
                     make_property(this,
                        &DeezerPlusMSNAPI::get_testString,
                        &DeezerPlusMSNAPI::set_testString));

    // Read-only property
    registerProperty("version",
                     make_property(this,
                        &DeezerPlusMSNAPI::get_version));
    
    
    registerEvent("onfired");    
}

///////////////////////////////////////////////////////////////////////////////
/// @fn DeezerPlusMSNAPI::~DeezerPlusMSNAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
DeezerPlusMSNAPI::~DeezerPlusMSNAPI()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @fn DeezerPlusMSNPtr DeezerPlusMSNAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
DeezerPlusMSNPtr DeezerPlusMSNAPI::getPlugin()
{
    DeezerPlusMSNPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read/Write property testString
std::string DeezerPlusMSNAPI::get_testString()
{
    return m_testString;
}
void DeezerPlusMSNAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string DeezerPlusMSNAPI::get_version()
{
    return "CURRENT_VERSION";
}

// Method echo
FB::variant DeezerPlusMSNAPI::echo(const FB::variant& msg)
{
    return msg;
}

void DeezerPlusMSNAPI::testEvent(const FB::variant& var)
{
    FireEvent("onfired", FB::variant_list_of(var)(true)(1));
}

bool DeezerPlusMSNAPI::nowPlaying(const std::wstring& artist, const std::wstring& track, const std::wstring& album, bool enable)
{
	wchar_t* msn_artist;
	wchar_t* msn_title;
	wchar_t* msn_album;
	wchar_t* format;
	wchar_t* icon;
	wchar_t buffer[400];
	wchar_t* active = L"1";
	HWND msnui = NULL;
	COPYDATASTRUCT msndata;

	if(enable) {
		msn_artist = const_cast<wchar_t*>( artist.c_str() );
		msn_title = const_cast<wchar_t*>( track.c_str() );
		msn_album = const_cast<wchar_t*>( album.c_str() );
			
		if(artist.length() == 0 && track.length() == 0 && album.length() == 0) {
				active = L"0";
		}

		format = L"{0} - {1}";
		icon = L"Music";

		if((wcslen(msn_artist) + wcslen(msn_title) + wcslen(msn_album) + wcslen(format) + wcslen(icon)) > 300) {
				return 0;
		}

		wsprintfW(buffer,L"\\0%s\\0%s\\0%s\\0%s\\0%s\\0%s\\0WMContentID\\0",icon, active, format, msn_title, msn_artist, msn_album);

		msndata.dwData = 0x547;
		msndata.lpData = &buffer;
		msndata.cbData = (lstrlenW(buffer)*2)+2;

		while (msnui = FindWindowEx(NULL, msnui, L"MsnMsgrUIManager", NULL)) {
			SendMessage(msnui, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&msndata);
		}
	} else {
		WCHAR buffer[500]; 
		HWND msnui = NULL; 
		bool bshow = 0; 

		// Arbitraire : buffer, Office, bshow, stringblah, truc;
		wsprintfW(buffer, L"\\0Office\\0%d\\0\\0\\0\\0\\0%s\\0", bshow, L"{0} - {1} - {2}", L"WMContentID");

		msndata.dwData=0x547;
		msndata.cbData = (lstrlen(buffer)*2)+2; 
		msndata.lpData = &buffer; 

		msnui = (HWND)FindWindowEx(NULL, NULL, (LPCWSTR)L"MsnMsgrUIManager", NULL);

		if (msnui) SendMessage(msnui, WM_COPYDATA, (WPARAM)0, (LPARAM)&msndata);


		/* OLD STUFF 

		wsprintfW(buffer,L"\\0Music\\01\\0\\0\\0\\0\\0\\0");

        msndata.dwData = 0x547;
        msndata.lpData = &buffer;
        msndata.cbData = (lstrlenW(buffer)*2)+2;

        while (msnui = FindWindowEx(NULL, msnui, L"MsnMsgrUIManager", NULL)) {
            SendMessage(msnui, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&msndata);
        }*/
	}
	return enable;
}
