#ifndef AVCONVSETTINGS_H
#define AVCONVSETTINGS_H

#include <wx/arrstr.h>
#include <wx/utils.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/textfile.h>

class AVConvSettings
{
    // initialize all static members with valid values
    public: static void Init();
    // the path where the configuration settings should be stored
    public: static wxString GetConfigurationPath();
    // returns a list of all available ffmpegyag presets (*.fyt) found in the application directory / user directory
    // (prefer application directory templates over user directory templates when same name was found)
    public: static wxArrayString GetPresets();
    // returns a list of parameters for a given preset, the seperator of parameters is '='
    public: static wxArrayString LoadPreset(wxString PresetName);
    // save the settings in a file corresponding to the preset name (user datadirectory)
    public: static void SavePreset(wxString PresetName, wxArrayString PresetSettings);
};

#endif // AVCONVSETTINGS_H
