#include "AVConvSettings.h"

void AVConvSettings::Init()
{
    wxString path = GetConfigurationPath();

    if(!wxDirExists(path))
    {
        wxMkdir(path);
    }
}

wxString AVConvSettings::GetConfigurationPath()
{
    #ifdef PORTABLE
        #ifdef __LINUX__
            return wxStandardPaths::Get().GetExecutablePath().BeforeLast('/');
        #endif
        #ifdef __WINDOWS__
            return wxStandardPaths::Get().GetExecutablePath().BeforeLast('\\');
        #endif
    #else
        #ifdef __LINUX__
            wxString EnvironmentFilePath;
            wxGetEnv(wxT("XDG_CONFIG_HOME"), &EnvironmentFilePath);
            EnvironmentFilePath = EnvironmentFilePath.BeforeFirst(':');
            if(EnvironmentFilePath.IsEmpty())
            {
                EnvironmentFilePath = wxStandardPaths::Get().GetUserConfigDir() + wxT("/.config/ffmpegyag");
            }
            else
            {
                EnvironmentFilePath +=  wxT("/ffmpegyag");
            }
            return EnvironmentFilePath;
        #endif
        #ifdef __WINDOWS__
            return wxStandardPaths::Get().GetUserDataDir();
        #endif
    #endif
}

wxArrayString AVConvSettings::GetPresets()
{
    wxArrayString PresetFiles;
    wxDir::GetAllFiles(wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()) + wxFileName::GetPathSeparator() + wxT("presets"), &PresetFiles, wxT("*.fyt"));
    wxDir::GetAllFiles(GetConfigurationPath(), &PresetFiles, wxT("*.fyt"));
    for(size_t f=0; f<PresetFiles.GetCount(); f++)
    {
        PresetFiles[f] = PresetFiles[f].BeforeLast('.').AfterLast(wxFileName::GetPathSeparator());
    }
    PresetFiles.Sort();
    return PresetFiles;
}

wxArrayString AVConvSettings::LoadPreset(wxString PresetName)
{
    wxArrayString PresetSettings;
    wxArrayString PresetFiles;
    // presets in executable directory has higher priority (when same name) then in home directory, so load them first
    wxDir::GetAllFiles(wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()), &PresetFiles, PresetName + wxT(".fyt"));
    wxDir::GetAllFiles(GetConfigurationPath(), &PresetFiles, PresetName + wxT(".fyt"));
    if(PresetFiles.GetCount() > 0)
    {
        wxTextFile PresetFile;
        PresetFile.Open(PresetFiles[0]);
        PresetSettings.Add(PresetFile.GetFirstLine());
        while(!PresetFile.Eof())
        {
            PresetSettings.Add(PresetFile.GetNextLine());
        }
        PresetFile.Close();
    }
    else
    {
        // preset not found
    }
    return PresetSettings;
}

void AVConvSettings::SavePreset(wxString PresetName, wxArrayString PresetSettings)
{
    wxArrayString PresetFiles;
    // presets in executable directory has higher priority (when same name) then in home directory, so load them first
    wxDir::GetAllFiles(wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()), &PresetFiles, PresetName + wxT(".fyt"));
    wxDir::GetAllFiles(GetConfigurationPath(), &PresetFiles, PresetName + wxT(".fyt"));

    wxTextFile PresetFile;
    if(PresetFiles.GetCount() > 0)
    {
        // replace existing preset
        PresetFile.Open(PresetFiles[0]);
        PresetFile.Clear();
    }
    else
    {
        // create preset in userdata directory
        PresetFile.Create(GetConfigurationPath() + wxFileName::GetPathSeparator() + PresetName + wxT(".fyt"));
    }
    for(long i=0; i<(long)PresetSettings.GetCount(); i++)
    {
        PresetFile.AddLine(PresetSettings[i]);
    }
    PresetFile.Write();
    PresetFile.Close();

    return;
}
