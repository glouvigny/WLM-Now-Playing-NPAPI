/**********************************************************\

  Auto-generated DeezerPlusMSNAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "DeezerPlusMSN.h"
#include "windows.h"

#ifndef H_DeezerPlusMSNAPI
#define H_DeezerPlusMSNAPI

class DeezerPlusMSNAPI : public FB::JSAPIAuto
{
public:
    DeezerPlusMSNAPI(DeezerPlusMSNPtr plugin, FB::BrowserHostPtr host);
    virtual ~DeezerPlusMSNAPI();

    DeezerPlusMSNPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Method test-event
    void testEvent(const FB::variant& s);

	bool nowPlaying(const std::wstring& artist, const std::wstring& track, const std::wstring& album, bool enable);


private:
    DeezerPlusMSNWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_DeezerPlusMSNAPI

