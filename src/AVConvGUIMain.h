#ifndef AVCONVGUIMAIN_H
#define AVCONVGUIMAIN_H

//(*Headers(AVConvGUIFrame)
#include <wx/glcanvas.h>
#include <wx/checklst.h>
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/statline.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/menu.h>
//*)

//#include <wx/dcclient.h>
#include <wx/textfile.h>
#include <wx/txtstrm.h>
#include <wx/process.h>
#include <wx/timer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include <wx/icon.h>

#include "resource.h"
#include "EncodingTask.h"
#include "AVConvSettings.h"

#define STR_DEFAULT wxT("default")
#define STR_NO_CHANGE wxT("no change")

struct SelectedStreamIndex
{
    // index of the input file
    long FileIndex;
    // index of the stream
    long StreamIndex;
    // id of the stream (curently not used)
    unsigned int ID;
};

WX_DECLARE_OBJARRAY(SelectedStreamIndex, SelectedStreamIndexArray);

class AVConvGUIFrame: public wxFrame
{
    public:

        AVConvGUIFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~AVConvGUIFrame();

    private:

        //(*Handlers(AVConvGUIFrame)
        void OnResize(wxSizeEvent& event);
        void OnFrameScroll(wxScrollEvent& event);
        void OnGLCanvasPreviewResize(wxSizeEvent& event);
        void OnButtonAddTaskClick(wxCommandEvent& event);
        void OnButtonRemoveTaskClick(wxCommandEvent& event);
        void OnListCtrlTasksItemSelect(wxListEvent& event);
        void OnCheckBoxFileSegmentJoinClick(wxCommandEvent& event);
        void OnListCtrlSegmentsItemSelect(wxListEvent& event);
        void OnSpinCtrlCropChange(wxSpinEvent& event);
        void OnButtonSegmentAddClick(wxCommandEvent& event);
        void OnButtonSegmentDeleteClick(wxCommandEvent& event);
        void OnButtonSegmentFromClick(wxCommandEvent& event);
        void OnButtonSegmentToClick(wxCommandEvent& event);
        void OnComboBoxFileFormatSelect(wxCommandEvent& event);
        void OnTextCtrlFileOutChange(wxCommandEvent& event);
        void OnCheckListBoxVideoStreamsToggled(wxCommandEvent& event);
        void OnComboBoxVideoCodecSelect(wxCommandEvent& event);
        void OnComboBoxVideoBitrateSelect(wxCommandEvent& event);
        void OnComboBoxVideoFrameSizeSelect(wxCommandEvent& event);
        //void OnComboBoxVideoFrameRateSelect(wxCommandEvent& event);
        void OnComboBoxVideoAspectRatioSelect(wxCommandEvent& event);
        //void OnCheckBoxVideoMultiPassClick(wxCommandEvent& event);
        void OnCheckListBoxAudioStreamsToggled(wxCommandEvent& event);
        void OnComboBoxAudioCodecSelect(wxCommandEvent& event);
        void OnComboBoxAudioBitrateSelect(wxCommandEvent& event);
        void OnComboBoxAudioFrequencySelect(wxCommandEvent& event);
        void OnComboBoxAudioChannelsSelect(wxCommandEvent& event);
        void OnCheckListBoxSubtitleStreamsToggled(wxCommandEvent& event);
        void OnComboBoxSubtitleCodecSelect(wxCommandEvent& event);
        void OnButtonEncodeClick(wxCommandEvent& event);
        void OnButtonAbortClick(wxCommandEvent& event);
        void OnCheckListBoxVideoStreamsSelect(wxCommandEvent& event);
        void OnCheckListBoxAudioStreamsSelect(wxCommandEvent& event);
        void OnCheckListBoxSubtitleStreamsSelect(wxCommandEvent& event);
        void OnButtonScriptClick(wxCommandEvent& event);
        //*)
        void OnProcessTerinate(wxProcessEvent& event);
        void OnMainWindowRClick(wxMouseEvent& event);
        void OnMenuPresetsClick(wxCommandEvent& event);
        void OnListCtrlSegmentsRClick(wxMouseEvent& event);
        void OnMenuSegmentFiltersClick(wxCommandEvent& event);

        //(*Identifiers(AVConvGUIFrame)
        static const long ID_STATICTEXT8;
        static const long ID_LISTCTRL1;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_STATICLINE4;
        static const long ID_STATICTEXT19;
        static const long ID_GLCANVAS1;
        static const long ID_TEXTCTRL1;
        static const long ID_SLIDER1;
        static const long ID_STATICTEXT9;
        static const long ID_SPINCTRL1;
        static const long ID_SPINCTRL2;
        static const long ID_STATICTEXT10;
        static const long ID_SPINCTRL3;
        static const long ID_SPINCTRL4;
        static const long ID_CHECKBOX1;
        static const long ID_LISTCTRL2;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_BUTTON8;
        static const long ID_BUTTON7;
        static const long ID_STATICLINE1;
        static const long ID_STATICTEXT5;
        static const long ID_COMBOBOX2;
        static const long ID_STATICTEXT16;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICLINE3;
        static const long ID_STATICTEXT2;
        static const long ID_CHECKLISTBOX1;
        static const long ID_STATICTEXT7;
        static const long ID_COMBOBOX4;
        static const long ID_STATICTEXT14;
        static const long ID_COMBOBOX8;
        static const long ID_STATICTEXT15;
        static const long ID_COMBOBOX9;
        static const long ID_STATICTEXT17;
        static const long ID_COMBOBOX11;
        static const long ID_STATICLINE6;
        static const long ID_STATICTEXT1;
        static const long ID_CHECKLISTBOX2;
        static const long ID_STATICTEXT4;
        static const long ID_COMBOBOX1;
        static const long ID_STATICTEXT11;
        static const long ID_COMBOBOX5;
        static const long ID_STATICTEXT12;
        static const long ID_COMBOBOX6;
        static const long ID_STATICTEXT13;
        static const long ID_COMBOBOX7;
        static const long ID_STATICLINE5;
        static const long ID_STATICTEXT3;
        static const long ID_CHECKLISTBOX3;
        static const long ID_STATICTEXT6;
        static const long ID_COMBOBOX3;
        static const long ID_STATICLINE2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON9;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_GotoSegmentStart;
        static const long ID_GotoSegmentEnd;
        static const long ID_VideoFadeIn;
        static const long ID_VideoFadeInStart;
        static const long ID_VideoFadeInEnd;
        static const long ID_VideoFadeInReset;
        static const long ID_VideoFadeOut;
        static const long ID_VideoFadeOutStart;
        static const long ID_VideoFadeOutEnd;
        static const long ID_VideoFadeOutReset;
        static const long ID_AudioFadeIn;
        static const long ID_AudioFadeInStart;
        static const long ID_AudioFadeInEnd;
        static const long ID_AudioFadeInReset;
        static const long ID_AudioFadeOut;
        static const long ID_AudioFadeOutStart;
        static const long ID_AudioFadeOutEnd;
        static const long ID_AudioFadeOutReset;

        //(*Declarations(AVConvGUIFrame)
        wxComboBox* ComboBoxFileFormat;
        wxStaticLine* StaticLine6;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxFileDialog* FileDialogLoadFiles;
        wxButton* ButtonSegmentAdd;
        wxButton* ButtonEncode;
        wxStaticText* StaticText15;
        wxStaticLine* StaticLine2;
        wxButton* ButtonAbort;
        wxListCtrl* ListCtrlSegments;
        wxButton* ButtonScript;
        wxSpinCtrl* SpinCtrlRight;
        wxStaticLine* StaticLine5;
        wxButton* ButtonRemoveTask;
        wxStaticText* StaticText18;
        wxCheckListBox* CheckListBoxAudioStreams;
        wxStaticText* StaticText1;
        wxStaticText* StaticText10;
        wxComboBox* ComboBoxVideoBitrate;
        wxStaticText* StaticText16;
        wxStaticText* StaticText3;
        wxComboBox* ComboBoxVideoAspectRatio;
        wxStaticLine* StaticLine1;
        wxCheckBox* CheckBoxFileSegmentJoin;
        wxFileDialog* FileDialogSaveFile;
        wxComboBox* ComboBoxVideoCodec;
        wxCheckListBox* CheckListBoxSubtitleStreams;
        wxSlider* SliderFrame;
        wxTextCtrl* TextCtrlTime;
        wxStaticText* StaticText8;
        wxStaticText* StaticText12;
        wxButton* ButtonSegmentTo;
        wxStaticLine* StaticLine3;
        wxComboBox* ComboBoxAudioChannels;
        wxComboBox* ComboBoxAudioCodec;
        wxListCtrl* ListCtrlTasks;
        wxComboBox* ComboBoxAudioFrequency;
        wxStaticText* StaticText7;
        wxCheckListBox* CheckListBoxVideoStreams;
        wxStaticText* StaticText4;
        wxComboBox* ComboBoxAudioBitrate;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxTextCtrl* TextCtrlFileOut;
        wxStaticText* StaticText6;
        wxStatusBar* StatusBar;
        wxStaticLine* StaticLine4;
        wxSpinCtrl* SpinCtrlBottom;
        wxStaticText* StaticTextFrameSize;
        wxSpinCtrl* SpinCtrlTop;
        wxButton* ButtonSegmentFrom;
        wxStaticText* StaticText9;
        wxButton* ButtonAddTask;
        wxComboBox* ComboBoxSubtitleCodec;
        wxComboBox* ComboBoxVideoFrameSize;
        wxGLCanvas* GLCanvasPreview;
        wxButton* ButtonSegmentDelete;
        wxSpinCtrl* SpinCtrlLeft;
        wxStaticText* StaticText11;
        //*)
        wxMenu* MenuMain;
        wxMenu* MenuPresets;
        wxMenu* MenuSegmentFilters;

        bool AbortEncoding;
        EncodingTaskArray EncodingTasks;
        // the list of currently highlighted tasks
        wxArrayLong SelectedTaskIndices;
        // the list of currently highlighted segments
        wxArrayLong SelectedSegmentIndices;
        // the list of currently highlighted input files (currently not in use)
        //wxArrayLong SelectedInputFilesIndex;
        // the list of currently highlighted video streams of all input files from this task
        SelectedStreamIndexArray SelectedVideoStreamIndices;
        // the list of currently highlighted audio streams of all input files from this task
        SelectedStreamIndexArray SelectedAudioStreamIndices;
        // the list of currently highlighted subtitle streams of all input files from this task
        SelectedStreamIndexArray SelectedSubtitleStreamIndices;

        // converts empty string (from setting) to StringFormat human readable string
        private: wxString FormatFromSetting(wxString Value, wxString EmptyRepresentation);
        // converts StringFormat human readable string to empty string (to settigns)
        private: wxString FormatToSetting(wxString Value);
        //
        private: void UpdateSelectedTaskIndices();
        //
        private: void UpdateSelectedSegmentIndices();
        //
        private: void UpdateSelectedVideoIndices();
        //
        private: void UpdateSelectedAudioIndices();
        //
        private: void UpdateSelectedSubtitleIndices();
// only for debugging
private: void ShowSelectedIndices();
        // enable disable controls depending on the selected format
        private: void EnableDisableAVFormatControls();
        // render the videoframe of current selected file,stream,timestamp
        private: void RenderFrame();
        // test if the settings are consistent
        private: bool VerifySettings();

        DECLARE_EVENT_TABLE()
};

#endif // AVCONVGUIMAIN_H
