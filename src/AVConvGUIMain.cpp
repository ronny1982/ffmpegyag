#include "AVConvGUIMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(AVConvGUIFrame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(SelectedStreamIndexArray);

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(AVConvGUIFrame)
const long AVConvGUIFrame::ID_STATICTEXT8 = wxNewId();
const long AVConvGUIFrame::ID_LISTCTRL1 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON3 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON4 = wxNewId();
const long AVConvGUIFrame::ID_STATICLINE4 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT19 = wxNewId();
const long AVConvGUIFrame::ID_GLCANVAS1 = wxNewId();
const long AVConvGUIFrame::ID_TEXTCTRL1 = wxNewId();
const long AVConvGUIFrame::ID_SLIDER1 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT9 = wxNewId();
const long AVConvGUIFrame::ID_SPINCTRL1 = wxNewId();
const long AVConvGUIFrame::ID_SPINCTRL2 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT10 = wxNewId();
const long AVConvGUIFrame::ID_SPINCTRL3 = wxNewId();
const long AVConvGUIFrame::ID_SPINCTRL4 = wxNewId();
const long AVConvGUIFrame::ID_CHECKBOX1 = wxNewId();
const long AVConvGUIFrame::ID_LISTCTRL2 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON5 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON6 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON8 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON7 = wxNewId();
const long AVConvGUIFrame::ID_STATICLINE1 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT5 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX2 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT16 = wxNewId();
const long AVConvGUIFrame::ID_TEXTCTRL2 = wxNewId();
const long AVConvGUIFrame::ID_STATICLINE3 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT2 = wxNewId();
const long AVConvGUIFrame::ID_CHECKLISTBOX1 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT7 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX4 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT14 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX8 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT15 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX9 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT17 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX11 = wxNewId();
const long AVConvGUIFrame::ID_STATICLINE6 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT1 = wxNewId();
const long AVConvGUIFrame::ID_CHECKLISTBOX2 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT4 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX1 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT11 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX5 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT12 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX6 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT13 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX7 = wxNewId();
const long AVConvGUIFrame::ID_STATICLINE5 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT3 = wxNewId();
const long AVConvGUIFrame::ID_CHECKLISTBOX3 = wxNewId();
const long AVConvGUIFrame::ID_STATICTEXT6 = wxNewId();
const long AVConvGUIFrame::ID_COMBOBOX3 = wxNewId();
const long AVConvGUIFrame::ID_STATICLINE2 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON1 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON2 = wxNewId();
const long AVConvGUIFrame::ID_BUTTON9 = wxNewId();
const long AVConvGUIFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AVConvGUIFrame,wxFrame)
    //(*EventTable(AVConvGUIFrame)
    //*)
END_EVENT_TABLE()

AVConvGUIFrame::AVConvGUIFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(AVConvGUIFrame)
    wxFlexGridSizer* FlexGridSizerPreProcessing;
    wxFlexGridSizer* FlexGridSizerVideo;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizerPreview;
    wxFlexGridSizer* FlexGridSizer7;
    wxBoxSizer* BoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizerSubtitle;
    wxBoxSizer* BoxSizer4;
    wxFlexGridSizer* FlexGridSizerFormat;
    wxBoxSizer* BoxSizerButtons;
    wxFlexGridSizer* FlexGridSizerJobList;
    wxFlexGridSizer* FlexGridSizerPostProcessing;
    wxFlexGridSizer* FlexGridSizerAudio;
    wxFlexGridSizer* FlexGridSizer5;
    wxBoxSizer* BoxSizer5;

    Create(parent, wxID_ANY, _("FFmpegYAG"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
    wxIcon ico;
    wxMemoryInputStream* ResourceMemoryStream = new wxMemoryInputStream(RESOURCES::APP_16_ICO.data, RESOURCES::APP_16_ICO.length);
    ico.CopyFromBitmap(wxBitmap(wxImage(*ResourceMemoryStream, wxBITMAP_TYPE_ICO)));
    wxDELETE(ResourceMemoryStream);
    //ResourceMemoryStream = NULL;
    SetIcon(ico);
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableCol(2);
    FlexGridSizer2->AddGrowableRow(0);
    FlexGridSizerJobList = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizerJobList->AddGrowableCol(0);
    FlexGridSizerJobList->AddGrowableRow(1);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Tasks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StaticText8->Disable();
    wxFont StaticText8Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText8->SetFont(StaticText8Font);
    FlexGridSizerJobList->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ListCtrlTasks = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
    ListCtrlTasks->SetMinSize(wxSize(400,-1));
    wxListItem col;
    col.SetText(wxT("Source File"));
    ListCtrlTasks->InsertColumn(0, col);
    col.SetAlign(wxLIST_FORMAT_RIGHT);
    col.SetText(wxT("Duration"));
    ListCtrlTasks->InsertColumn(1, col);
    col.SetText(wxT("Size"));
    ListCtrlTasks->InsertColumn(2, col);
    ListCtrlTasks->SetToolTip(_("List of all tasks that will be encoded. You can select a single task for editing, or select multiple tasks for mass editing. Depending on the differences in the selected tasks, there might be some limitations in mass editing (i.e. videos with different amount of audio tracks)."));
    FlexGridSizerJobList->Add(ListCtrlTasks, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    ButtonAddTask = new wxButton(this, ID_BUTTON3, _("Add Tasks(s)..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    ButtonAddTask->SetToolTip(_("Add new task(s) to the list.\nTIP: Added task(s) will be initialized with the current FFmpegYAG settings. If you want to add multiple files with the same settings, it would be smart to make the 'master' setting before you add the files ;)"));
    BoxSizer4->Add(ButtonAddTask, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonRemoveTask = new wxButton(this, ID_BUTTON4, _("Remove Task(s)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    ButtonRemoveTask->SetToolTip(_("Remove the selected task(s) from the list."));
    BoxSizer4->Add(ButtonRemoveTask, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerJobList->Add(BoxSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizerJobList, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL, _T("ID_STATICLINE4"));
    FlexGridSizer2->Add(StaticLine4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPreview = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizerPreview->AddGrowableCol(0);
    FlexGridSizerPreview->AddGrowableRow(0);
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(1);
    StaticText18 = new wxStaticText(this, ID_STATICTEXT19, _("Preview"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    StaticText18->Disable();
    wxFont StaticText18Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText18->SetFont(StaticText18Font);
    FlexGridSizer4->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    int GLCanvasAttributes_1[] = {
        WX_GL_RGBA,
        WX_GL_DOUBLEBUFFER,
        WX_GL_DEPTH_SIZE,      16,
        WX_GL_STENCIL_SIZE,    0,
        0, 0 };
    GLCanvasPreview = new wxGLCanvas(this, ID_GLCANVAS1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    GLCanvasPreview->SetMinSize(wxSize(280,140));
    GLCanvasPreview->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));
    FlexGridSizer4->Add(GLCanvasPreview, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlTime = new wxTextCtrl(this, ID_TEXTCTRL1, _("00:00:00.000 / 00:00:00.000 []"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrlTime->Disable();
    FlexGridSizer4->Add(TextCtrlTime, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderFrame = new wxSlider(this, ID_SLIDER1, 0, 0, 1, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
    SliderFrame->Disable();
    FlexGridSizer4->Add(SliderFrame, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPreview->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPreProcessing = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizerPreProcessing->AddGrowableCol(0);
    FlexGridSizerPreProcessing->AddGrowableRow(3);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Crop / Trim"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText9->Disable();
    wxFont StaticText9Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText9->SetFont(StaticText9Font);
    FlexGridSizerPreProcessing->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    SpinCtrlLeft = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(60,24), 0, 0, 1024, 0, _T("ID_SPINCTRL1"));
    SpinCtrlLeft->SetValue(_T("0"));
    SpinCtrlLeft->Disable();
    SpinCtrlLeft->SetToolTip(_("Crop the left side of the source video."));
    BoxSizer2->Add(SpinCtrlLeft, 1, wxALL|wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(1);
    SpinCtrlTop = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxSize(60,24), 0, 0, 1024, 0, _T("ID_SPINCTRL2"));
    SpinCtrlTop->SetValue(_T("0"));
    SpinCtrlTop->Disable();
    SpinCtrlTop->SetToolTip(_("Crop the top of the source video."));
    FlexGridSizer3->Add(SpinCtrlTop, 1, wxTOP|wxBOTTOM|wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextFrameSize = new wxStaticText(this, ID_STATICTEXT10, _("0000 x 0000"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticTextFrameSize->Disable();
    FlexGridSizer3->Add(StaticTextFrameSize, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlBottom = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxSize(60,24), 0, 0, 1024, 0, _T("ID_SPINCTRL3"));
    SpinCtrlBottom->SetValue(_T("0"));
    SpinCtrlBottom->Disable();
    SpinCtrlBottom->SetToolTip(_("Crop the bottom of the source video."));
    FlexGridSizer3->Add(SpinCtrlBottom, 1, wxTOP|wxBOTTOM|wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlRight = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxSize(60,24), 0, 0, 1024, 0, _T("ID_SPINCTRL4"));
    SpinCtrlRight->SetValue(_T("0"));
    SpinCtrlRight->Disable();
    SpinCtrlRight->SetToolTip(_("Crop the right side of the source video."));
    BoxSizer2->Add(SpinCtrlRight, 1, wxALL|wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPreProcessing->Add(BoxSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxFileSegmentJoin = new wxCheckBox(this, ID_CHECKBOX1, _("Join File Segments"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBoxFileSegmentJoin->SetValue(false);
    CheckBoxFileSegmentJoin->Disable();
    FlexGridSizerPreProcessing->Add(CheckBoxFileSegmentJoin, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ListCtrlSegments = new wxListCtrl(this, ID_LISTCTRL2, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTCTRL2"));
    ListCtrlSegments->Disable();
    ListCtrlSegments->InsertColumn(0, wxT("From"));
    ListCtrlSegments->InsertColumn(1, wxT("To"));
    ListCtrlSegments->SetToolTip(_("Segments are trimmed parts of the video.\nThis is useful if you want to extract one or more parts of the video (i.e. openeing and ending of an anime). This list shows a collection of all segments from the selected task. If the selected task has no segements, then the whole video will be encoded."));
    FlexGridSizerPreProcessing->Add(ListCtrlSegments, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    ButtonSegmentFrom = new wxButton(this, ID_BUTTON5, _("From {"), wxDefaultPosition, wxSize(60,24), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    ButtonSegmentFrom->Disable();
    ButtonSegmentFrom->SetToolTip(_("Set the start time of the selected segment to the current position of the preview."));
    BoxSizer5->Add(ButtonSegmentFrom, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSegmentTo = new wxButton(this, ID_BUTTON6, _("} To"), wxDefaultPosition, wxSize(60,24), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    ButtonSegmentTo->Disable();
    ButtonSegmentTo->SetToolTip(_("Set the end time of the selected segment to the current position of the preview."));
    BoxSizer5->Add(ButtonSegmentTo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSegmentDelete = new wxButton(this, ID_BUTTON8, _("Del -"), wxDefaultPosition, wxSize(60,24), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    ButtonSegmentDelete->Disable();
    ButtonSegmentDelete->SetToolTip(_("Delete the selected segment from the selected task."));
    BoxSizer5->Add(ButtonSegmentDelete, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSegmentAdd = new wxButton(this, ID_BUTTON7, _("Add +"), wxDefaultPosition, wxSize(60,24), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    ButtonSegmentAdd->Disable();
    ButtonSegmentAdd->SetToolTip(_("Add a new segment with the current position of the preview to the selected task."));
    BoxSizer5->Add(ButtonSegmentAdd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPreProcessing->Add(BoxSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPreview->Add(FlexGridSizerPreProcessing, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizerPreview, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerFormat = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizerFormat->AddGrowableCol(3);
    FlexGridSizerFormat->AddGrowableRow(0);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Format"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText5->Disable();
    wxFont StaticText5Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText5->SetFont(StaticText5Font);
    FlexGridSizerFormat->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxFileFormat = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    ComboBoxFileFormat->Append(_("matroska"));
    ComboBoxFileFormat->Append(_("mp4"));
    ComboBoxFileFormat->Append(_("mov"));
    ComboBoxFileFormat->Append(_("ogg"));
    ComboBoxFileFormat->Append(_("webm"));
    ComboBoxFileFormat->Append(_("mpeg"));
    ComboBoxFileFormat->Append(_("mp3"));
    ComboBoxFileFormat->Append(_("ac3"));
    ComboBoxFileFormat->Append(_("flac"));
    ComboBoxFileFormat->Append(_("wav"));
    ComboBoxFileFormat->Append(_("ass"));
    ComboBoxFileFormat->Append(_("srt"));
    ComboBoxFileFormat->Append(_("image2"));
    ComboBoxFileFormat->SetToolTip(_("No tooltip available"));
    FlexGridSizerFormat->Add(ComboBoxFileFormat, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText15 = new wxStaticText(this, ID_STATICTEXT16, _("File"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    StaticText15->Disable();
    wxFont StaticText15Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText15->SetFont(StaticText15Font);
    FlexGridSizerFormat->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlFileOut = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH2|wxTE_DONTWRAP, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrlFileOut->Disable();
    TextCtrlFileOut->SetToolTip(_("No tooltip available"));
    FlexGridSizerFormat->Add(TextCtrlFileOut, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizerFormat, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    FlexGridSizer1->Add(StaticLine3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPostProcessing = new wxFlexGridSizer(0, 5, 0, 0);
    FlexGridSizerPostProcessing->AddGrowableCol(0);
    FlexGridSizerPostProcessing->AddGrowableCol(2);
    FlexGridSizerPostProcessing->AddGrowableCol(4);
    FlexGridSizerPostProcessing->AddGrowableRow(0);
    FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    FlexGridSizer5->AddGrowableRow(2);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Video"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText2->Disable();
    wxFont StaticText2Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer5->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBoxVideoStreams = new wxCheckListBox(this, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(0,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    CheckListBoxVideoStreams->Disable();
    CheckListBoxVideoStreams->SetToolTip(_("List of available video streams from the selected task. If multiple tasks are selected this list shows only the 'common' streams (in case the tasks differ in the amount of video streams). Toggle the checkbox to decide which video stream(s) should be included for encoding. Select a stream(s) to change the corresponding encoding settings."));
    FlexGridSizer5->Add(CheckListBoxVideoStreams, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerVideo = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizerVideo->AddGrowableCol(1);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Codec:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    StaticText7->Disable();
    FlexGridSizerVideo->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxVideoCodec = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
    ComboBoxVideoCodec->SetToolTip(_("Set the codec for the selected video stream(s).\nTIP: This parameter is directly passed to ffmpeg, so you can append commandline options\n(i.e. 'libx264 -preset:v slower -tune:v animation')."));
    FlexGridSizerVideo->Add(ComboBoxVideoCodec, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText13 = new wxStaticText(this, ID_STATICTEXT14, _("Bitrate:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    StaticText13->Disable();
    //StaticText13->SetToolTip(_("Bitrate for the selected video stream.\nHigher bitrates give better quality but increase the filesize.\nSome encoders like x264 supports CRF (constant rate factor).\nLower CRF values give better quality but increase the filesize."));
    FlexGridSizerVideo->Add(StaticText13, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxVideoBitrate = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
    ComboBoxVideoBitrate->Append(_("default"));
    ComboBoxVideoBitrate->Append(_("800k"));
    ComboBoxVideoBitrate->Append(_("1000k"));
    ComboBoxVideoBitrate->Append(_("1200k"));
    ComboBoxVideoBitrate->Append(_("1400k"));
    ComboBoxVideoBitrate->SetSelection( ComboBoxVideoBitrate->Append(_("1800k")) );
    ComboBoxVideoBitrate->Append(_("2400k"));
    ComboBoxVideoBitrate->Append(_("3200k"));
    ComboBoxVideoBitrate->Append(_("4000k"));
    ComboBoxVideoBitrate->Append(_("-crf 28"));
    ComboBoxVideoBitrate->Append(_("-crf 26"));
    ComboBoxVideoBitrate->Append(_("-crf 24"));
    ComboBoxVideoBitrate->Append(_("-crf 22"));
    ComboBoxVideoBitrate->Append(_("-crf 20"));
    ComboBoxVideoBitrate->Append(_("-crf 18"));
    ComboBoxVideoBitrate->SetToolTip(_("Set the bitrate for the selected video stream(s).\nHigher bitrates give better quality but increase the filesize.\nSome encoders like x264 supports CRF (constant rate factor).\nLower CRF values give better quality but increase the filesize."));
    FlexGridSizerVideo->Add(ComboBoxVideoBitrate, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(this, ID_STATICTEXT15, _("Frame Size:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    StaticText14->Disable();
    FlexGridSizerVideo->Add(StaticText14, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxVideoFrameSize = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
    ComboBoxVideoFrameSize->SetSelection( ComboBoxVideoFrameSize->Append(_("no change")) );
    ComboBoxVideoFrameSize->Append(_("1920x1080"));
    ComboBoxVideoFrameSize->Append(_("1280x720"));
    ComboBoxVideoFrameSize->Append(_("1024x576"));
    ComboBoxVideoFrameSize->Append(_("854x480"));
    ComboBoxVideoFrameSize->Append(_("640x360"));
    ComboBoxVideoFrameSize->Append(_("1600x1200"));
    ComboBoxVideoFrameSize->Append(_("1024x768"));
    ComboBoxVideoFrameSize->Append(_("800x600"));
    ComboBoxVideoFrameSize->Append(_("768x576"));
    ComboBoxVideoFrameSize->Append(_("640x480"));
    ComboBoxVideoFrameSize->SetToolTip(_("Set the resolution for the selected video stream(s).\nVideo will be scaled if this is different from the source."));
    FlexGridSizerVideo->Add(ComboBoxVideoFrameSize, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText16 = new wxStaticText(this, ID_STATICTEXT17, _("Aspect Ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StaticText16->Disable();
    FlexGridSizerVideo->Add(StaticText16, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxVideoAspectRatio = new wxComboBox(this, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX11"));
    ComboBoxVideoAspectRatio->SetSelection( ComboBoxVideoAspectRatio->Append(_("no change")) );
    ComboBoxVideoAspectRatio->Append(_("2.35"));
    ComboBoxVideoAspectRatio->Append(_("19:10"));
    ComboBoxVideoAspectRatio->Append(_("16:10"));
    ComboBoxVideoAspectRatio->Append(_("16:9"));
    ComboBoxVideoAspectRatio->Append(_("3:2"));
    ComboBoxVideoAspectRatio->Append(_("4:3"));
    ComboBoxVideoAspectRatio->SetToolTip(_("Set the aspect ratio for the selected video stream(s). This is useful for playback, stretching the video to fit the given aspect ratio."));
    FlexGridSizerVideo->Add(ComboBoxVideoAspectRatio, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizerVideo, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPostProcessing->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine6 = new wxStaticLine(this, ID_STATICLINE6, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL, _T("ID_STATICLINE6"));
    FlexGridSizerPostProcessing->Add(StaticLine6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    FlexGridSizer6->AddGrowableRow(2);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Audio"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText1->Disable();
    wxFont StaticText1Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer6->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBoxAudioStreams = new wxCheckListBox(this, ID_CHECKLISTBOX2, wxDefaultPosition, wxSize(0,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX2"));
    CheckListBoxAudioStreams->Disable();
    CheckListBoxAudioStreams->SetToolTip(_("No tooltip available"));
    FlexGridSizer6->Add(CheckListBoxAudioStreams, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerAudio = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizerAudio->AddGrowableCol(1);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Codec:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText4->Disable();
    FlexGridSizerAudio->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxAudioCodec = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    ComboBoxAudioCodec->SetToolTip(_("No tooltip available"));
    FlexGridSizerAudio->Add(ComboBoxAudioCodec, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("Bitrate:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    StaticText10->Disable();
    FlexGridSizerAudio->Add(StaticText10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxAudioBitrate = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
    ComboBoxAudioBitrate->Append(_("default"));
    ComboBoxAudioBitrate->Append(_("34k"));
    ComboBoxAudioBitrate->Append(_("48k"));
    ComboBoxAudioBitrate->Append(_("64k"));
    ComboBoxAudioBitrate->Append(_("96k"));
    ComboBoxAudioBitrate->Append(_("128k"));
    ComboBoxAudioBitrate->Append(_("160k"));
    ComboBoxAudioBitrate->SetSelection( ComboBoxAudioBitrate->Append(_("192k")) );
    ComboBoxAudioBitrate->Append(_("256k"));
    ComboBoxAudioBitrate->Append(_("384k"));
    ComboBoxAudioBitrate->Append(_("576k"));
    ComboBoxAudioBitrate->SetToolTip(_("No tooltip available"));
    FlexGridSizerAudio->Add(ComboBoxAudioBitrate, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(this, ID_STATICTEXT12, _("Frequency:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    StaticText11->Disable();
    FlexGridSizerAudio->Add(StaticText11, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxAudioFrequency = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
    ComboBoxAudioFrequency->SetSelection( ComboBoxAudioFrequency->Append(_("no change")) );
    ComboBoxAudioFrequency->Append(_("11025"));
    ComboBoxAudioFrequency->Append(_("22050"));
    ComboBoxAudioFrequency->Append(_("44100"));
    ComboBoxAudioFrequency->Append(_("48000"));
    ComboBoxAudioFrequency->Append(_("96000"));
    ComboBoxAudioFrequency->SetToolTip(_("No tooltip available"));
    FlexGridSizerAudio->Add(ComboBoxAudioFrequency, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _("Channels:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    StaticText12->Disable();
    FlexGridSizerAudio->Add(StaticText12, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxAudioChannels = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
    ComboBoxAudioChannels->SetSelection( ComboBoxAudioChannels->Append(_("no change")) );
    ComboBoxAudioChannels->Append(_("1"));
    ComboBoxAudioChannels->Append(_("2"));
    ComboBoxAudioChannels->Append(_("6"));
    ComboBoxAudioChannels->SetToolTip(_("No tooltip available"));
    FlexGridSizerAudio->Add(ComboBoxAudioChannels, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(FlexGridSizerAudio, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPostProcessing->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine5 = new wxStaticLine(this, ID_STATICLINE5, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL, _T("ID_STATICLINE5"));
    FlexGridSizerPostProcessing->Add(StaticLine5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer7->AddGrowableCol(0);
    FlexGridSizer7->AddGrowableRow(2);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Subtitle"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText3->Disable();
    wxFont StaticText3Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBoxSubtitleStreams = new wxCheckListBox(this, ID_CHECKLISTBOX3, wxDefaultPosition, wxSize(0,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX3"));
    CheckListBoxSubtitleStreams->Disable();
    CheckListBoxSubtitleStreams->SetToolTip(_("No tooltip available"));
    FlexGridSizer7->Add(CheckListBoxSubtitleStreams, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerSubtitle = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizerSubtitle->AddGrowableCol(1);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Codec:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText6->Disable();
    FlexGridSizerSubtitle->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxSubtitleCodec = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
    ComboBoxSubtitleCodec->SetToolTip(_("No tooltip available"));
    FlexGridSizerSubtitle->Add(ComboBoxSubtitleCodec, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(FlexGridSizerSubtitle, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizerPostProcessing->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizerPostProcessing, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    FlexGridSizer1->Add(StaticLine2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizerButtons = new wxBoxSizer(wxHORIZONTAL);
    ButtonEncode = new wxButton(this, ID_BUTTON1, _("Encode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizerButtons->Add(ButtonEncode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonAbort = new wxButton(this, ID_BUTTON2, _("Abort"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    ButtonAbort->Disable();
    BoxSizerButtons->Add(ButtonAbort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonScript = new wxButton(this, ID_BUTTON9, _("Save Script"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizerButtons->Add(ButtonScript, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizerButtons, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    StatusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -1, 480, 120 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar);
    FileDialogLoadFiles = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("Videos|*.avi;*.mkv;*.mp4;*.mpg;*.mpeg;*.vob;*.m2ts;*.ogm;*.flv;*.mov|All Files (*.*)|*.*"), wxFD_OPEN|wxFD_MULTIPLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FileDialogSaveFile = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    MenuPresets = new wxMenu();
    MenuSegmentFilters = new wxMenu();
    MenuSegmentFilters->AppendSeparator();
    MenuSegmentFilters->Append(-1, _("Video Filters"))->Enable(false);
    MenuSegmentFilters->AppendSeparator();
    MenuSegmentFilters->Append(VideoFadeIn, _("Video Fade-In"));
    MenuSegmentFilters->Append(VideoFadeOut, _("Video Fade-Out"));
    MenuSegmentFilters->AppendSeparator();
    MenuSegmentFilters->Append(-1, _("Audio Filters"))->Enable(false);
    MenuSegmentFilters->AppendSeparator();
    MenuSegmentFilters->Append(AudioFadeIn, _("Audio Fade-In"));
    MenuSegmentFilters->Append(AudioFadeOut, _("Audio Fade-Out"));
    MenuMain = new wxMenu(_("Main Menu"));
    MenuMain->Append(-1, _("Save Script"))->Enable(false);
    MenuMain->AppendSeparator();
    MenuMain->AppendSubMenu(MenuPresets, _("Load Preset"));
    MenuMain->AppendSeparator();
    MenuMain->Append(-1, _("Help"))->Enable(false);
    MenuMain->Append(-1, _("About"))->Enable(false);
    MenuMain->Append(-1, _("Exit"))->Enable(false);
    Center();

    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&AVConvGUIFrame::OnListCtrlTasksItemSelect);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&AVConvGUIFrame::OnListCtrlTasksItemSelect);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&AVConvGUIFrame::OnListCtrlSegmentsItemSelect);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&AVConvGUIFrame::OnListCtrlSegmentsItemSelect);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonAddTaskClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonRemoveTaskClick);
    Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnFrameScroll);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnSpinCtrlCropChange);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnSpinCtrlCropChange);
    Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnSpinCtrlCropChange);
    Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnSpinCtrlCropChange);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonSegmentFromClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonSegmentToClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonSegmentDeleteClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonSegmentAddClick);
    Connect(ID_COMBOBOX2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxFileFormatSelect);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnTextCtrlFileOutChange);
    Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&AVConvGUIFrame::OnCheckListBoxVideoStreamsToggled);
    Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&AVConvGUIFrame::OnCheckListBoxVideoStreamsSelect);
    Connect(ID_COMBOBOX4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxVideoCodecSelect);
    Connect(ID_COMBOBOX8,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxVideoBitrateSelect);
    Connect(ID_COMBOBOX9,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxVideoFrameSizeSelect);
    Connect(ID_COMBOBOX11,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxVideoAspectRatioSelect);
    Connect(ID_CHECKLISTBOX2,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&AVConvGUIFrame::OnCheckListBoxAudioStreamsToggled);
    Connect(ID_CHECKLISTBOX2,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&AVConvGUIFrame::OnCheckListBoxAudioStreamsSelect);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxAudioCodecSelect);
    Connect(ID_COMBOBOX5,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxAudioBitrateSelect);
    Connect(ID_COMBOBOX6,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxAudioFrequencySelect);
    Connect(ID_COMBOBOX7,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxAudioChannelsSelect);
    Connect(ID_CHECKLISTBOX3,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&AVConvGUIFrame::OnCheckListBoxSubtitleStreamsToggled);
    Connect(ID_CHECKLISTBOX3,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&AVConvGUIFrame::OnCheckListBoxSubtitleStreamsSelect);
    Connect(ID_COMBOBOX3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AVConvGUIFrame::OnComboBoxSubtitleCodecSelect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonEncodeClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonAbortClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AVConvGUIFrame::OnButtonScriptClick);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&AVConvGUIFrame::OnResize);
    //*)
    GLCanvasPreview->Connect(wxEVT_SIZE,(wxObjectEventFunction)&AVConvGUIFrame::OnGLCanvasPreviewResize,0,this);
    MenuPresets->Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&AVConvGUIFrame::OnMenuPresetsClick, NULL, this);
    Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&AVConvGUIFrame::OnMainWindowRClick);
    MenuSegmentFilters->Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&AVConvGUIFrame::OnMenuSegmentFiltersClick, NULL, this);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&AVConvGUIFrame::OnListCtrlSegmentsRClick);

    ComboBoxFileFormat->SetValue(wxT("matroska"));
    ComboBoxVideoCodec->SetValue(wxT("libx264"));
    ComboBoxAudioCodec->SetValue(wxT("aac"));
    ComboBoxSubtitleCodec->SetValue(wxT("copy"));
    EnableDisableAVFormatControls();
}

AVConvGUIFrame::~AVConvGUIFrame()
{
    WX_CLEAR_ARRAY(EncodingTasks);
    SelectedTaskIndices.Clear();
    //SelectedInputFilesIndex.Clear();
    SelectedVideoStreamIndices.Clear();
    SelectedAudioStreamIndices.Clear();
    SelectedSubtitleStreamIndices.Clear();
    //(*Destroy(AVConvGUIFrame)
    //*)
}

wxString AVConvGUIFrame::FormatFromSetting(wxString Value, wxString EmptyRepresentation)
{
    if(Value.IsEmpty())
    {
        return EmptyRepresentation;
    }
    return Value;
}

wxString AVConvGUIFrame::FormatToSetting(wxString Value)
{
    if(Value.IsSameAs(STR_DEFAULT) || Value.IsSameAs(STR_NO_CHANGE))
    {
        return wxEmptyString;
    }
    return Value;
}

void AVConvGUIFrame::ShowSelectedIndices()
{
    wxString log = wxT("Index Update Log:\n");
    log.Append(wxString::Format(wxT("\nTask Selected Count: %lu\n"), (unsigned long)SelectedTaskIndices.GetCount()));
    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        log.Append(wxString::Format(wxT("Task Selected Index: %ld\n"), SelectedTaskIndices[i]));
    }
    log.Append(wxString::Format(wxT("\nVideo Selected Count: %lu\n"), (unsigned long)SelectedVideoStreamIndices.GetCount()));
    for(size_t i=0; i<SelectedVideoStreamIndices.GetCount(); i++)
    {
        log.Append(wxString::Format(wxT("Video Selected File:Index, ID: %ld:%ld, %u\n"), SelectedVideoStreamIndices[i].FileIndex, SelectedVideoStreamIndices[i].StreamIndex, SelectedVideoStreamIndices[i].ID));
    }
    log.Append(wxString::Format(wxT("\nAudio Selected Count: %lu\n"), (unsigned long)SelectedAudioStreamIndices.GetCount()));
    for(size_t i=0; i<SelectedAudioStreamIndices.GetCount(); i++)
    {
        log.Append(wxString::Format(wxT("Audio Selected File:Index, ID: %ld:%ld, %u\n"), SelectedAudioStreamIndices[i].FileIndex, SelectedAudioStreamIndices[i].StreamIndex, SelectedAudioStreamIndices[i].ID));
    }
    log.Append(wxString::Format(wxT("\nSubtitle Selected Count: %lu\n"), (unsigned long)SelectedSubtitleStreamIndices.GetCount()));
    for(size_t i=0; i<SelectedSubtitleStreamIndices.GetCount(); i++)
    {
        log.Append(wxString::Format(wxT("Subtitle Selected File:Index, ID: %ld:%ld, %u\n"), SelectedSubtitleStreamIndices[i].FileIndex, SelectedSubtitleStreamIndices[i].StreamIndex, SelectedSubtitleStreamIndices[i].ID));
    }
    wxMessageBox(log);
}

void AVConvGUIFrame::UpdateSelectedTaskIndices()
{
    long TaskIndex;

    SelectedTaskIndices.Clear();

    // create the list of selected tasks
    TaskIndex = ListCtrlTasks->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while(TaskIndex > -1)
    {
        SelectedTaskIndices.Add(TaskIndex);
        TaskIndex = ListCtrlTasks->GetNextItem(TaskIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
}

void AVConvGUIFrame::UpdateSelectedSegmentIndices()
{
    long SegmentIndex;

    SelectedSegmentIndices.Clear();

    // create the list of selected tasks
    SegmentIndex = ListCtrlSegments->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while(SegmentIndex > -1)
    {
        SelectedSegmentIndices.Add(SegmentIndex);
        SegmentIndex = ListCtrlSegments->GetNextItem(SegmentIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
}

void AVConvGUIFrame::UpdateSelectedVideoIndices()
{
    long TaskIndex;
    wxArrayInt Indices;
    wxString StreamIndex;
    SelectedStreamIndex SelectedIndex;

    SelectedVideoStreamIndices.Clear();

    // serch in all tasks for an appropriate stream, beware of finding duplicates!
    for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
    {
        TaskIndex = SelectedTaskIndices[t];

        // create the list of selected video streams
        CheckListBoxVideoStreams->GetSelections(Indices);
        for(unsigned int i=0; i<Indices.GetCount(); i++)
        {
            // parse the list item to get file and stream index
            StreamIndex = CheckListBoxVideoStreams->GetString(Indices[i]).BeforeFirst('#');
            SelectedIndex.FileIndex = wxAtoi(StreamIndex.Before(':'));
            SelectedIndex.StreamIndex = wxAtoi(StreamIndex.After(':'));
            // detect the id of this stream
            if(SelectedIndex.FileIndex < (long)EncodingTasks[TaskIndex]->InputFiles.GetCount() && SelectedIndex.StreamIndex < (long)EncodingTasks[TaskIndex]->InputFiles[SelectedIndex.FileIndex]->VideoStreams.GetCount())
            {
                SelectedIndex.ID = EncodingTasks[TaskIndex]->InputFiles[SelectedIndex.FileIndex]->VideoStreams[SelectedIndex.StreamIndex]->ID;

                // check for duplicate
                bool exist = false;
                for(size_t v=0; v<SelectedVideoStreamIndices.GetCount(); v++)
                {
                    if(SelectedVideoStreamIndices[v].FileIndex == SelectedIndex.FileIndex && SelectedVideoStreamIndices[v].StreamIndex == SelectedIndex.StreamIndex)
                    {
                        exist = true;
                        break;
                    }
                }
                if(!exist)
                {
                    SelectedVideoStreamIndices.Add(SelectedIndex);
                }
                else
                {
                    //wxMessageBox(wxT("WARNING:\nVideo Stream already selected!"));
                }
            }
            else
            {
                wxMessageBox(wxString::Format(wxT("WARNING:\nVideo Stream was not found in Task[%ld]!"), TaskIndex));
            }
        }
    }
}

void AVConvGUIFrame::UpdateSelectedAudioIndices()
{
    long TaskIndex;
    wxArrayInt Indices;
    wxString StreamIndex;
    SelectedStreamIndex SelectedIndex;

    SelectedAudioStreamIndices.Clear();

    // serch in all tasks for an appropriate stream, beware of finding duplicates!
    for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
    {
        TaskIndex = SelectedTaskIndices[t];

        // create the list of selected audio streams
        CheckListBoxAudioStreams->GetSelections(Indices);
        for(size_t i=0; i<Indices.GetCount(); i++)
        {
            // parse the list item to get file and stream index
            StreamIndex = CheckListBoxAudioStreams->GetString(Indices[i]).BeforeFirst('#');
            SelectedIndex.FileIndex = wxAtoi(StreamIndex.Before(':'));
            SelectedIndex.StreamIndex = wxAtoi(StreamIndex.After(':'));
            // detect the id of this stream
            if(SelectedIndex.FileIndex < (long)EncodingTasks[TaskIndex]->InputFiles.GetCount() && SelectedIndex.StreamIndex < (long)EncodingTasks[TaskIndex]->InputFiles[SelectedIndex.FileIndex]->AudioStreams.GetCount())
            {
                SelectedIndex.ID = EncodingTasks[TaskIndex]->InputFiles[SelectedIndex.FileIndex]->AudioStreams[SelectedIndex.StreamIndex]->ID;

                // check for duplicate
                bool exist = false;
                for(size_t a=0; a<SelectedAudioStreamIndices.GetCount(); a++)
                {
                    if(SelectedAudioStreamIndices[a].FileIndex == SelectedIndex.FileIndex && SelectedAudioStreamIndices[a].StreamIndex == SelectedIndex.StreamIndex)
                    {
                        exist = true;
                        break;
                    }
                }
                if(!exist)
                {
                    SelectedAudioStreamIndices.Add(SelectedIndex);
                }
                else
                {
                    //wxMessageBox(wxT("WARNING:\nAudio Stream already selected!"));
                }
            }
            else
            {
                wxMessageBox(wxString::Format(wxT("WARNING:\nAudio Stream was not found in Task[%ld]!"), TaskIndex));
            }
        }
    }
}

void AVConvGUIFrame::UpdateSelectedSubtitleIndices()
{
    long TaskIndex;
    wxArrayInt Indices;
    wxString StreamIndex;
    SelectedStreamIndex SelectedIndex;

    SelectedSubtitleStreamIndices.Clear();

    // serch in all tasks for an appropriate stream, beware of finding duplicates!
    for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
    {
        TaskIndex = SelectedTaskIndices[t];

        // create the list of selected subtitle streams
        CheckListBoxSubtitleStreams->GetSelections(Indices);
        for(size_t i=0; i<Indices.GetCount(); i++)
        {
            // parse the list item to get file and stream index
            StreamIndex = CheckListBoxSubtitleStreams->GetString(Indices[i]).BeforeFirst('#');
            SelectedIndex.FileIndex = wxAtoi(StreamIndex.Before(':'));
            SelectedIndex.StreamIndex = wxAtoi(StreamIndex.After(':'));
            // detect the id of this stream
            if(SelectedIndex.FileIndex < (long)EncodingTasks[TaskIndex]->InputFiles.GetCount() && SelectedIndex.StreamIndex < (long)EncodingTasks[TaskIndex]->InputFiles[SelectedIndex.FileIndex]->SubtitleStreams.GetCount())
            {
                SelectedIndex.ID = EncodingTasks[TaskIndex]->InputFiles[SelectedIndex.FileIndex]->SubtitleStreams[SelectedIndex.StreamIndex]->ID;

                // check for duplicate
                bool exist = false;
                for(size_t s=0; s<SelectedSubtitleStreamIndices.GetCount(); s++)
                {
                    if(SelectedSubtitleStreamIndices[s].FileIndex == SelectedIndex.FileIndex && SelectedSubtitleStreamIndices[s].StreamIndex == SelectedIndex.StreamIndex)
                    {
                        exist = true;
                        break;
                    }
                }
                if(!exist)
                {
                    SelectedSubtitleStreamIndices.Add(SelectedIndex);
                }
                else
                {
                    //wxMessageBox(wxT("WARNING:\nSubtitle Stream already selected!"));
                }
            }
            else
            {
                wxMessageBox(wxString::Format(wxT("WARNING:\nSubtitle Stream was not found in Task[%ld]!"), TaskIndex));
            }
        }
    }
}

void AVConvGUIFrame::EnableDisableAVFormatControls()
{
    wxString Format = FormatToSetting(ComboBoxFileFormat->GetValue());
    if(true/*SelectedTaskIndices.GetCount() > 0*/)
    {
        wxString selected_video_codec = ComboBoxVideoCodec->GetValue();
        ComboBoxVideoCodec->Clear();
        //ComboBoxVideoCodec->SetValue(wxEmptyString);
        wxString selected_audio_codec = ComboBoxAudioCodec->GetValue();
        ComboBoxAudioCodec->Clear();
        //ComboBoxAudioCodec->SetValue(wxEmptyString);
        wxString selected_subtitle_codec = ComboBoxSubtitleCodec->GetValue();
        ComboBoxSubtitleCodec->Clear();
        //ComboBoxSubtitleCodec->SetValue(wxEmptyString);

        AVMediaFlags MediaFlags = Libav::FormatMediaMap[Format];

        if(MediaFlags & AVMEDIA_FLAG_VIDEO)
        {
            SpinCtrlTop->Enable();
            SpinCtrlLeft->Enable();
            SpinCtrlBottom->Enable();
            SpinCtrlRight->Enable();

            CheckListBoxVideoStreams->Enable();
            ComboBoxVideoCodec->Enable();
            ComboBoxVideoBitrate->Enable();
            ComboBoxVideoFrameSize->Enable();
            ComboBoxVideoAspectRatio->Enable();

            ComboBoxVideoCodec->Append(Libav::FormatVideoCodecs(Format));
            ComboBoxVideoCodec->SetValue(selected_video_codec);
        }
        else
        {
            SpinCtrlTop->Disable();
            SpinCtrlLeft->Disable();
            SpinCtrlBottom->Disable();
            SpinCtrlRight->Disable();

            CheckListBoxVideoStreams->Disable();
            ComboBoxVideoCodec->Disable();
            ComboBoxVideoBitrate->Disable();
            ComboBoxVideoFrameSize->Disable();
            ComboBoxVideoAspectRatio->Disable();
        }

        if(MediaFlags & AVMEDIA_FLAG_AUDIO)
        {
            CheckListBoxAudioStreams->Enable();
            ComboBoxAudioCodec->Enable();
            ComboBoxAudioBitrate->Enable();
            ComboBoxAudioFrequency->Enable();
            ComboBoxAudioChannels->Enable();

            ComboBoxAudioCodec->Append(Libav::FormatAudioCodecs(Format));
            ComboBoxAudioCodec->SetValue(selected_audio_codec);
        }
        else
        {
            CheckListBoxAudioStreams->Disable();
            ComboBoxAudioCodec->Disable();
            ComboBoxAudioBitrate->Disable();
            ComboBoxAudioFrequency->Disable();
            ComboBoxAudioChannels->Disable();
        }

        if(MediaFlags & AVMEDIA_FLAG_SUBTITLE)
        {
            CheckListBoxSubtitleStreams->Enable();
            ComboBoxSubtitleCodec->Enable();

            ComboBoxSubtitleCodec->Append(Libav::FormatSubtitleCodecs(Format));
            ComboBoxSubtitleCodec->SetValue(selected_subtitle_codec);
        }
        else
        {
            CheckListBoxSubtitleStreams->Disable();
            ComboBoxSubtitleCodec->Disable();
        }
    }
}

void AVConvGUIFrame::OnButtonAddTaskClick(wxCommandEvent& event)
{
    // open file dialog
    if(FileDialogLoadFiles->ShowModal() == wxID_OK)
    {
        //ListCtrlTasks->SetItemState(-1, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);

        wxFileName SourceFile;
        wxArrayString SourceFiles;
        FileDialogLoadFiles->GetPaths(SourceFiles);
        EncodingFileLoader* InputFile;
        EncodingTask* EncTask;
        VideoStream* vStream;
        AudioStream* aStream;
        SubtitleStream* sStream;
        int top = SpinCtrlTop->GetValue();
        int bottom = SpinCtrlBottom->GetValue();
        int left = SpinCtrlLeft->GetValue();
        int right = SpinCtrlRight->GetValue();

        size_t InsertIndex;
        bool HadSelectedTasks = false;
        UpdateSelectedTaskIndices();
        if(SelectedTaskIndices.GetCount() > 0)
        {
            HadSelectedTasks = true;
        }
        // TODO: change selection behaviour on new added tasks
        // never auto select new added tasks
        // HadSelectedTasks = true;

        ListCtrlTasks->Freeze();

        for(size_t i=0; i<SourceFiles.GetCount(); i++)
        {
            SourceFile = wxFileName(SourceFiles[i]);

            if(SourceFile.FileExists())
            {
                InputFile = new EncodingFileLoader(SourceFile);

                if(InputFile->CanRead())
                {
                    InsertIndex = ListCtrlTasks->GetItemCount();
                    ListCtrlTasks->InsertItem(InsertIndex, SourceFile.GetFullName());
                    ListCtrlTasks->SetItem(InsertIndex, 1, Libav::MilliToSMPTE(InputFile->FileDuration).BeforeLast('.'));
                    ListCtrlTasks->SetItem(InsertIndex, 2, wxString::Format(wxT("%i MB"), (int)(InputFile->FileSize/1024/1024)));

                    EncTask = new EncodingTask();
                    EncTask->OutputFile = SourceFile;
                    EncTask->OutputFormat = ComboBoxFileFormat->GetValue();
                    EncTask->OutputFile.SetExt(Libav::FormatExtensionMap[EncTask->OutputFormat]);

                    for(size_t v=0; v<InputFile->VideoStreams.GetCount(); v++)
                    {
                        vStream = InputFile->VideoStreams[v];

                        //vStream->ID;
                        if(v == 0)
                        {
                            vStream->Enabled = true;
                        }
                        else
                        {
                            vStream->Enabled = false;
                        }
                        //vStream->Size;
                        //vStream->StartTime;
                        //vStream->Duration;
                        //vStream->Bitrate;
                        //vStream->Title;
                        //vStream->Language;
                        //vStream->CodecName;
                        //vStream->FrameIndexCount;
                        //vStream->FrameRate;
                        //vStream->Width;
                        //vStream->Height;
                        //vStream->Profile;

                        vStream->EncodingSettings.Codec = FormatToSetting(ComboBoxVideoCodec->GetValue());
                        vStream->EncodingSettings.Bitrate = FormatToSetting(ComboBoxVideoBitrate->GetValue());
                        //vStream->EncodingSettings.FrameRate = wxEmptyString;
                        vStream->EncodingSettings.FrameSize = FormatToSetting(ComboBoxVideoFrameSize->GetValue());
                        vStream->EncodingSettings.AspectRatio = FormatToSetting(ComboBoxVideoAspectRatio->GetValue());
                        //vStream->EncodingSettings.Deinterlace = false;
                        //vStream->EncodingSettings.MacroblockDecision = wxT("rd");
                        //vStream->EncodingSettings.MacroblockComparsion = wxT("rd");
                        //vStream->EncodingSettings.MotionEstimationComparsion = wxT("rd");
                        //vStream->EncodingSettings.PreMotionEstimationComparsion = wxT("rd");
                        //vStream->EncodingSettings.SubMotionEstimationComparsion = wxT("rd");
                        //vStream->EncodingSettings.Trellis = true;
                        //vStream->EncodingSettings.MinQuantization = wxT("1");
                        //vStream->EncodingSettings.MaxQuantization = wxT("31");
                        //vStream->EncodingSettings.QPEL = false;
                        //vStream->EncodingSettings.GMC = false;
                        if(top > 0 || bottom > 0 || left > 0 || right > 0)
                        {
                            vStream->EncodingSettings.Crop[0] = 1;
                        }
                        else
                        {
                            vStream->EncodingSettings.Crop[0] = 0;
                        }
                        vStream->EncodingSettings.Crop[1] = vStream->Width - left - right;
                        vStream->EncodingSettings.Crop[2] = vStream->Height - top - bottom;
                        vStream->EncodingSettings.Crop[3] = left;
                        vStream->EncodingSettings.Crop[4] = top;

                        vStream = NULL;
                    }

                    for(size_t a=0; a<InputFile->AudioStreams.GetCount(); a++)
                    {
                        aStream = InputFile->AudioStreams[a];

                        //aStream->ID;
                        if(a == 0)
                        {
                            aStream->Enabled = true;
                        }
                        else
                        {
                            aStream->Enabled = false;
                        }
                        //aStream->Size;
                        //aStream->StartTime;
                        //aStream->Duration;
                        //aStream->Bitrate;
                        //aStream->Title;
                        //aStream->Language;
                        //aStream->CodecName;
                        //aStream->FrameIndexCount;
                        //aStream->SampleRate;
                        //aStream->ChannelCount;

                        aStream->EncodingSettings.Codec = FormatToSetting(ComboBoxAudioCodec->GetValue());
                        aStream->EncodingSettings.Bitrate = FormatToSetting(ComboBoxAudioBitrate->GetValue());
                        aStream->EncodingSettings.Frequency = FormatToSetting(ComboBoxAudioFrequency->GetValue());
                        aStream->EncodingSettings.Channels = FormatToSetting(ComboBoxAudioChannels->GetValue());

                        aStream = NULL;
                    }

                    for(size_t s=0; s<InputFile->SubtitleStreams.GetCount(); s++)
                    {
                        sStream = InputFile->SubtitleStreams[s];

                        //sStream->ID;
                        if(s == 0)
                        {
                            sStream->Enabled = true;
                        }
                        else
                        {
                            sStream->Enabled = false;
                        }
                        //sStream->Size;
                        //sStream->StartTime;
                        //sStream->Duration;
                        //sStream->Bitrate;
                        //sStream->Title;
                        //sStream->Language;
                        //sStream->CodecName;
                        //sStream->FrameIndexCount;

                        sStream->EncodingSettings.Codec = FormatToSetting(ComboBoxSubtitleCodec->GetValue());

                        sStream = NULL;
                    }

                    EncTask->InputFiles.Add(InputFile);
                    EncodingTasks.Add(EncTask);
                    EncTask = NULL;

                    if(!HadSelectedTasks)
                    {
                        ListCtrlTasks->SetItemState(InsertIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
                        // TODO: change selection behaviour on new added tasks
                        // never auto select more then the first new added task
                        // HadSelectedTasks = true;
                    }
                }
                else
                {
                    wxDELETE(InputFile);
                    wxMessageBox(wxT("Invalid File Format:\n") + SourceFiles[i]);
                }

                InputFile = NULL;
            }
            else
            {
                wxMessageBox(wxT("File not Found:\n") + SourceFiles[i]);
            }
        }

        ListCtrlTasks->Thaw();
    }
}

void AVConvGUIFrame::OnButtonRemoveTaskClick(wxCommandEvent& event)
{
    ListCtrlTasks->Freeze();
    for(long i=SelectedTaskIndices.GetCount()-1; i>=0; i--)
    {
        wxDELETE(EncodingTasks[SelectedTaskIndices[i]]); // destructor executes flush buffer
        EncodingTasks.RemoveAt(SelectedTaskIndices[i]);
        // triggers update of selected task indices on msw
        ListCtrlTasks->DeleteItem(SelectedTaskIndices[i]);
    }
    ListCtrlTasks->Thaw();

    wxListEvent le;
    OnListCtrlTasksItemSelect(le);
}

void AVConvGUIFrame::OnListCtrlTasksItemSelect(wxListEvent& event)
{
    UpdateSelectedTaskIndices();

    if(SelectedTaskIndices.GetCount() < 1)
    {
        // enable/disable controls
        //{
            ListCtrlSegments->Disable();
            ButtonSegmentAdd->Disable();
            ButtonSegmentDelete->Disable();
            ButtonSegmentFrom->Disable();
            ButtonSegmentTo->Disable();

            ComboBoxFileFormat->Enable();
            TextCtrlFileOut->Disable();

            CheckListBoxVideoStreams->Disable();
            CheckListBoxAudioStreams->Disable();
            CheckListBoxSubtitleStreams->Disable();
        //}

        // set control values
        //{
            CheckListBoxVideoStreams->Clear();
            CheckListBoxAudioStreams->Clear();
            CheckListBoxSubtitleStreams->Clear();

            UpdateSelectedVideoIndices();
            UpdateSelectedAudioIndices();
            UpdateSelectedSubtitleIndices();

            ListCtrlSegments->DeleteAllItems();

            TextCtrlFileOut->Clear();
        //}
    }
    else
    {
        // enable/disable controls
        //{
            ListCtrlSegments->Enable();
            ButtonSegmentAdd->Enable();
            ButtonSegmentDelete->Enable();
            ButtonSegmentFrom->Enable();
            ButtonSegmentTo->Enable();

            ComboBoxFileFormat->Enable();
            TextCtrlFileOut->Enable();

            CheckListBoxVideoStreams->Enable();
            CheckListBoxAudioStreams->Enable();
            CheckListBoxSubtitleStreams->Enable();
        //}

        // set control values
        //{
            long TaskIndex = SelectedTaskIndices[0];
            long ActiveStreamIndex;

            ListCtrlSegments->DeleteAllItems();
            for(size_t i=0; i<EncodingTasks[TaskIndex]->OutputSegments.GetCount(); i++)
            {
                ListCtrlSegments->InsertItem(i, wxEmptyString);
                ListCtrlSegments->SetItem(i, 0, Libav::MilliToSMPTE(EncodingTasks[TaskIndex]->OutputSegments[i]->TimeFrom));
                ListCtrlSegments->SetItem(i, 1, Libav::MilliToSMPTE(EncodingTasks[TaskIndex]->OutputSegments[i]->TimeTo));
            }

            ComboBoxFileFormat->SetValue(FormatFromSetting(EncodingTasks[TaskIndex]->OutputFormat, STR_DEFAULT));
            TextCtrlFileOut->ChangeValue(EncodingTasks[TaskIndex]->OutputFile.GetFullPath());

            CheckListBoxVideoStreams->Clear();
            CheckListBoxAudioStreams->Clear();
            CheckListBoxSubtitleStreams->Clear();

            // add video streams and autodetect the default activated
            ActiveStreamIndex = -1;
            VideoStream* vStream;
            for(size_t f=0; f<EncodingTasks[TaskIndex]->InputFiles.GetCount(); f++)
            {
                for(size_t v=0; v<EncodingTasks[TaskIndex]->InputFiles[f]->VideoStreams.GetCount(); v++)
                {
                    vStream = EncodingTasks[TaskIndex]->InputFiles[f]->VideoStreams[v];
                    CheckListBoxVideoStreams->Append(wxString::Format(wxT("%lu:%lu#%u, ") + vStream->CodecName + wxT(", ") + vStream->Profile + wxT(", %i kb/s, %ix%i, %.3f fps"), (unsigned long)f, (unsigned long)v, vStream->ID, vStream->Bitrate/1024, vStream->Width, vStream->Height, vStream->FrameRate));
                    CheckListBoxVideoStreams->Check(CheckListBoxVideoStreams->GetCount()-1, vStream->Enabled);
                    if(ActiveStreamIndex < 0 && vStream->Enabled)
                    {
                        ActiveStreamIndex = CheckListBoxVideoStreams->GetCount()-1;
                    }
                }
            }
            if(ActiveStreamIndex < 0 && CheckListBoxVideoStreams->GetCount() > 0)
            {
                ActiveStreamIndex = 0;
            }
            CheckListBoxVideoStreams->SetSelection(ActiveStreamIndex);
            vStream = NULL;

            // add audio streams and autodetect the default activated
            ActiveStreamIndex = -1;
            AudioStream* aStream;
            for(size_t f=0; f<EncodingTasks[TaskIndex]->InputFiles.GetCount(); f++)
            {
                for(size_t a=0; a<EncodingTasks[TaskIndex]->InputFiles[f]->AudioStreams.GetCount(); a++)
                {
                    aStream = EncodingTasks[TaskIndex]->InputFiles[f]->AudioStreams[a];
                    CheckListBoxAudioStreams->Append(wxString::Format(wxT("%lu:%lu#%u, [") + aStream->Language + wxT("] ") + aStream->CodecName + wxT(", %i kb/s, %i kHz, %i ch"), (unsigned long)f, (unsigned long)a, aStream->ID, aStream->Bitrate/1024, aStream->SampleRate/1000, aStream->ChannelCount));
                    CheckListBoxAudioStreams->Check(CheckListBoxAudioStreams->GetCount()-1, aStream->Enabled);
                    if(ActiveStreamIndex < 0 && aStream->Enabled)
                    {
                        ActiveStreamIndex = CheckListBoxAudioStreams->GetCount()-1;
                    }
                }
            }
            if(ActiveStreamIndex < 0 && CheckListBoxAudioStreams->GetCount() > 0)
            {
                ActiveStreamIndex = 0;
            }
            CheckListBoxAudioStreams->Select(ActiveStreamIndex);
            aStream = NULL;

            // add subtitle streams and autodetect the default activated
            ActiveStreamIndex = -1;
            SubtitleStream* sStream;
            for(size_t f=0; f<EncodingTasks[TaskIndex]->InputFiles.GetCount(); f++)
            {
                for(size_t s=0; s<EncodingTasks[TaskIndex]->InputFiles[f]->SubtitleStreams.GetCount(); s++)
                {
                    sStream = EncodingTasks[TaskIndex]->InputFiles[f]->SubtitleStreams[s];
                    CheckListBoxSubtitleStreams->Append(wxString::Format(wxT("%lu:%lu#%u, [") + sStream->Language + wxT("] ") + sStream->CodecName + wxT(", ") + sStream->Title, (unsigned long)f, (unsigned long)s, sStream->ID));
                    CheckListBoxSubtitleStreams->Check(CheckListBoxSubtitleStreams->GetCount()-1, sStream->Enabled);
                    if(ActiveStreamIndex < 0 && sStream->Enabled)
                    {
                        ActiveStreamIndex = CheckListBoxSubtitleStreams->GetCount()-1;
                    }
                }
            }
            if(ActiveStreamIndex < 0 && CheckListBoxSubtitleStreams->GetCount() > 0)
            {
                ActiveStreamIndex = 0;
            }
            CheckListBoxSubtitleStreams->Select(ActiveStreamIndex);
            sStream = NULL;
        //}

        // process remaining tasks
        if(SelectedTaskIndices.GetCount() > 1)
        {
            // enable/disable controls
            //{
                ListCtrlSegments->Disable();
                ButtonSegmentAdd->Disable();
                ButtonSegmentDelete->Disable();
                ButtonSegmentFrom->Disable();
                ButtonSegmentTo->Disable();

                //ComboBoxFileFormat->Enable();
                //TextCtrlFileOut->Disable();

                //CheckListBoxVideoStreams->Disable();
                //CheckListBoxAudioStreams->Disable();
                //CheckListBoxSubtitleStreams->Disable();
            //}

            // set control values
            //{
                ListCtrlSegments->DeleteAllItems();

                wxFileName FileOut;
                // loop through all remaining tasks and scan for intersection settings (overlapping settings)
                for(size_t i=1; i<SelectedTaskIndices.GetCount(); i++)
                {
                    TaskIndex = SelectedTaskIndices[i];

                    if(!ComboBoxFileFormat->GetValue().IsSameAs(FormatFromSetting(EncodingTasks[TaskIndex]->OutputFormat, STR_DEFAULT)))
                    {
                        ComboBoxFileFormat->SetValue(wxT("*"));
                    }

                    FileOut = wxFileName(TextCtrlFileOut->GetValue());

                    if(FileOut.GetPath().IsSameAs(EncodingTasks[TaskIndex]->OutputFile.GetPath()))
                    {
                        if(!FileOut.GetName().IsSameAs(wxT("*")))
                        {
                            TextCtrlFileOut->ChangeValue(FileOut.GetPathWithSep() + wxT("*"));
                        }
                    }
                    else
                    {
                        TextCtrlFileOut->ChangeValue(wxString(wxFileName::GetPathSeparator()) + wxT("*"));
                    }

                    // colorify last two characters ("{SEP}*")
                    if(!TextCtrlFileOut->SetStyle(TextCtrlFileOut->GetLastPosition()-2, -1, wxTextAttr(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT))))
                    {
                        // set color failed, check platform support and enable wxTE_RICH2 & wxTE_MULTILINE
                    }
                }

                SelectedStreamIndex StreamIndex;
                wxString FileStreamIndex;
                bool exist;
                bool keepcheck;

                // merge video sreams
                for(int i=CheckListBoxVideoStreams->GetCount()-1; i>=0; i--)
                {
                    FileStreamIndex = CheckListBoxVideoStreams->GetString(i).BeforeFirst('#');
                    StreamIndex.FileIndex = wxAtoi(FileStreamIndex.Before(':'));
                    StreamIndex.StreamIndex = wxAtoi(FileStreamIndex.After(':'));

                    exist = true;
                    keepcheck = true;
                    for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
                    {
                        // get file and stream index
                        TaskIndex = SelectedTaskIndices[t];
                        if(StreamIndex.FileIndex < (long)EncodingTasks[TaskIndex]->InputFiles.GetCount() && StreamIndex.StreamIndex < (long)EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->VideoStreams.GetCount())
                        {
                            if(CheckListBoxVideoStreams->IsChecked(i) != EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->VideoStreams[StreamIndex.StreamIndex]->Enabled)
                            {
                                keepcheck = false;
                            }
                        }
                        else
                        {
                            exist = false;
                        }
                    }
                    if(exist)
                    {
                        bool state = CheckListBoxVideoStreams->IsChecked(i);
                        CheckListBoxVideoStreams->SetString(i, FileStreamIndex + wxT("#*"));
                        if(keepcheck)
                        {
                            CheckListBoxVideoStreams->Check(i, state);
                            //wxMessageBox(wxT("Keep Check: ") + FileStreamIndex);
                        }
                        else
                        {
                            // TODO: set checkbox state to undfined (third state)
                            // remember to reset this undefined state when check event occurs!
                            //CheckListBoxVideoStreams->SetItemForegroundColour(...);
                        }
                    }
                    else
                    {
                        CheckListBoxVideoStreams->Delete(i);
                    }
                }

                // merge audio sreams
                for(int i=CheckListBoxAudioStreams->GetCount()-1; i>=0; i--)
                {
                    FileStreamIndex = CheckListBoxAudioStreams->GetString(i).BeforeFirst('#');
                    StreamIndex.FileIndex = wxAtoi(FileStreamIndex.Before(':'));
                    StreamIndex.StreamIndex = wxAtoi(FileStreamIndex.After(':'));

                    exist = true;
                    keepcheck = true;
                    for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
                    {
                        // get file and stream index
                        TaskIndex = SelectedTaskIndices[t];
                        if(StreamIndex.FileIndex < (long)EncodingTasks[TaskIndex]->InputFiles.GetCount() && StreamIndex.StreamIndex < (long)EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->AudioStreams.GetCount())
                        {
                            if(CheckListBoxAudioStreams->IsChecked(i) != EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->AudioStreams[StreamIndex.StreamIndex]->Enabled)
                            {
                                keepcheck = false;
                            }
                        }
                        else
                        {
                            exist = false;
                        }
                    }
                    if(exist)
                    {
                        bool state = CheckListBoxAudioStreams->IsChecked(i);
                        CheckListBoxAudioStreams->SetString(i, FileStreamIndex + wxT("#*"));
                        if(keepcheck)
                        {
                            CheckListBoxAudioStreams->Check(i, state);
                            //wxMessageBox(wxT("Keep Check: ") + FileStreamIndex);
                        }
                        else
                        {
                            // TODO: set checkbox state to undfined (third state)
                            // remember to reset this undefined state when check event occurs!
                            //CheckListBoxAudioStreams->SetItemForegroundColour(...);
                        }
                    }
                    else
                    {
                        CheckListBoxAudioStreams->Delete(i);
                    }
                }

                // merge subtitle sreams
                for(int i=CheckListBoxSubtitleStreams->GetCount()-1; i>=0; i--)
                {
                    FileStreamIndex = CheckListBoxSubtitleStreams->GetString(i).BeforeFirst('#');
                    StreamIndex.FileIndex = wxAtoi(FileStreamIndex.Before(':'));
                    StreamIndex.StreamIndex = wxAtoi(FileStreamIndex.After(':'));

                    exist = true;
                    keepcheck = true;
                    for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
                    {
                        // get file and stream index
                        TaskIndex = SelectedTaskIndices[t];
                        if(StreamIndex.FileIndex < (long)EncodingTasks[TaskIndex]->InputFiles.GetCount() && StreamIndex.StreamIndex < (long)EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->SubtitleStreams.GetCount())
                        {
                            if(CheckListBoxSubtitleStreams->IsChecked(i) != EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->SubtitleStreams[StreamIndex.StreamIndex]->Enabled)
                            {
                                keepcheck = false;
                            }
                        }
                        else
                        {
                            exist = false;
                        }
                    }
                    if(exist)
                    {
                        bool state = CheckListBoxSubtitleStreams->IsChecked(i);
                        CheckListBoxSubtitleStreams->SetString(i, FileStreamIndex + wxT("#*"));
                        if(keepcheck)
                        {
                            CheckListBoxSubtitleStreams->Check(i, state);
                            //wxMessageBox(wxT("Keep Check: ") + FileStreamIndex);
                        }
                        else
                        {
                            // TODO: set checkbox state to undfined (third state)
                            // remember to reset this undefined state when check event occurs!
                            //CheckListBoxSubtitleStreams->SetItemForegroundColour(...);
                        }
                    }
                    else
                    {
                        CheckListBoxSubtitleStreams->Delete(i);
                    }
                }
            //}
        }
    }

    wxCommandEvent ce;
    OnCheckListBoxVideoStreamsSelect(ce);
    OnCheckListBoxAudioStreamsSelect(ce);
    OnCheckListBoxSubtitleStreamsSelect(ce);

    EnableDisableAVFormatControls();

    RenderFrame();
}

void AVConvGUIFrame::OnListCtrlSegmentsItemSelect(wxListEvent& event)
{
    UpdateSelectedSegmentIndices();
    RenderFrame();
}

void AVConvGUIFrame::OnFrameScroll(wxScrollEvent& event)
{
    RenderFrame();
}

void AVConvGUIFrame::RenderFrame()
{
    // check if control is on display
    if(GLCanvasPreview->GetContext())
    {
        int GlPanelWidth;// = GLCanvasPreview->GetSize().x;
        int GlPanelHeight;// = GLCanvasPreview->GetSize().y;
        GLCanvasPreview->GetClientSize(&GlPanelWidth, &GlPanelHeight);
        wxColour bc = GLCanvasPreview->GetBackgroundColour();

        // BOTTLENECK
        GLCanvasPreview->SetCurrent();

        glClearColor(float(bc.Red())/255.0f, float(bc.Green())/255.0f, float(bc.Blue())/255.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, GlPanelWidth, GlPanelHeight);

        if(SelectedTaskIndices.GetCount() == 1 && SelectedVideoStreamIndices.GetCount() == 1)
        {
            long SelectedTask = SelectedTaskIndices[0];
            long SelectedStream = SelectedVideoStreamIndices[0].StreamIndex;
            long SelectedFrame = (long)SliderFrame->GetValue();
            EncodingFileLoader* efl = EncodingTasks[SelectedTask]->InputFiles[0];

            // BOTTLENECK
            VideoFrame* Texture = efl->GetVideoFrameData(SelectedStream, SelectedFrame, 512, 256); // width & height of texture must be of power 2

            if(Texture != NULL)
            {
                // BOTTLENECK
                TextCtrlTime->SetValue(Libav::MilliToSMPTE(Texture->Timecode) + wxT(" / ") + Libav::MilliToSMPTE(efl->VideoStreams[SelectedStream]->Duration) + wxT(" [") + Texture->GetPicType() + wxT("]"));

                int VideoWidth = efl->VideoStreams[SelectedStream]->Width;
                int VideoHeight = efl->VideoStreams[SelectedStream]->Height;
                int VideoCropTop = SpinCtrlTop->GetValue();
                int VideoCropBottom = SpinCtrlBottom->GetValue();
                int VideoCropLeft = SpinCtrlLeft->GetValue();
                int VideoCropRight = SpinCtrlRight->GetValue();

                // calculate gl-panel mapping area depending on output video-aspect-ratio & crop
                int EncodingWidth;
                int EncodingHeight;
                if(!efl->VideoStreams[SelectedStream]->EncodingSettings.AspectRatio.IsEmpty())
                {
                    double ar;
                    if(efl->VideoStreams[SelectedStream]->EncodingSettings.AspectRatio.Find(wxT(":")) > -1)
                    {
                        double ar_num;
                        double ar_den;
                        efl->VideoStreams[SelectedStream]->EncodingSettings.AspectRatio.BeforeFirst(':').ToDouble(&ar_num);
                        efl->VideoStreams[SelectedStream]->EncodingSettings.AspectRatio.AfterLast(':').ToDouble(&ar_den);

                        ar = ar_num / ar_den;
                    }
                    else
                    {
                        efl->VideoStreams[SelectedStream]->EncodingSettings.AspectRatio.ToDouble(&ar);
                    }
                    EncodingHeight = 720;
                    EncodingWidth = (int)(EncodingHeight * ar);
                }
                else if(!efl->VideoStreams[SelectedStream]->EncodingSettings.FrameSize.IsEmpty())
                {
                    EncodingWidth = wxAtoi(efl->VideoStreams[SelectedStream]->EncodingSettings.FrameSize.BeforeFirst('x'));
                    EncodingHeight = wxAtoi(efl->VideoStreams[SelectedStream]->EncodingSettings.FrameSize.AfterLast('x'));
                }
                else
                {
                    EncodingWidth = VideoWidth-VideoCropLeft-VideoCropRight;
                    EncodingHeight = VideoHeight-VideoCropTop-VideoCropBottom;
                }
                // values are in uv representation (-1 to +1)
                double GlPanelTop = double(EncodingHeight) / double(GlPanelHeight);
                double GlPanelRight = double(EncodingWidth) / double(GlPanelWidth);
                if(GlPanelRight > GlPanelTop)
                {
                    // scale height with width-ratio
                    GlPanelTop = GlPanelTop / GlPanelRight;
                    GlPanelRight = 1.0;
                }
                else
                {
                    // scale width with height-ratio
                    GlPanelRight = GlPanelRight / GlPanelTop;
                    GlPanelTop = 1.0;
                }
                double GlPanelBottom = -GlPanelTop;
                double GlPanelLeft = -GlPanelRight;

                // calculate texture mapping area depending on crop
                // values are in uv representation (+0 to +1)
                double TextureTop = double(VideoCropTop) / double(VideoHeight);
                double TextureBottom = double(VideoHeight-VideoCropBottom) / double(VideoHeight);
                double TextureLeft = double(VideoCropLeft) / double(VideoWidth);
                double TextureRight = double(VideoWidth-VideoCropRight) / double(VideoWidth);

                GLuint TexturePointer;

                glGenTextures(1, &TexturePointer);
                glBindTexture(GL_TEXTURE_2D, TexturePointer);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

                glTexImage2D(GL_TEXTURE_2D, 0, Texture->GetGLFormat(), Texture->Width, Texture->Height, 0, Texture->GetGLFormat(), GL_UNSIGNED_BYTE, Texture->Data);

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, TexturePointer);

                glBegin(GL_QUADS);
                    // top left
                    glTexCoord2d(TextureLeft, TextureTop);
                    glVertex2d(GlPanelLeft, GlPanelTop);
                    // top right
                    glTexCoord2d(TextureRight, TextureTop);
                    glVertex2d(GlPanelRight, GlPanelTop);
                    // bottom right
                    glTexCoord2d(TextureRight, TextureBottom);
                    glVertex2d(GlPanelRight, GlPanelBottom);
                    // bottom left
                    glTexCoord2d(TextureLeft, TextureBottom);
                    glVertex2d(GlPanelLeft, GlPanelBottom);
                glEnd();

                glDisable(GL_TEXTURE_2D);
                // this will not free memory of Texture->Data
                glDeleteTextures(1, &TexturePointer);

                if(SelectedSegmentIndices.GetCount() == 1)
                {
                    FileSegment* Segment = EncodingTasks[SelectedTask]->OutputSegments[SelectedSegmentIndices[0]];
                    if(Texture->Timecode < Segment->TimeFrom || (Texture->Timecode > Segment->TimeTo && Segment->TimeFrom < Segment->TimeTo))
                    {
                        glColor3f(1.0, 0.0, 0.0);
                        glBegin(GL_LINES);
                            glVertex2d(GlPanelLeft, GlPanelTop);
                            glVertex2d(GlPanelRight, GlPanelBottom);
                            glVertex2d(GlPanelRight, GlPanelTop);
                            glVertex2d(GlPanelLeft, GlPanelBottom);
                        glEnd();
                    }
                    else
                    {
                        int64_t time = Texture->Timecode - Segment->TimeFrom;

                        // fade in
                        if(Segment->FilterVideoFadeInStart > 0 && Segment->FilterVideoFadeInDuration > 0)
                        {
                            if(time <= Segment->FilterVideoFadeInStart + Segment->FilterVideoFadeInDuration)
                            {
                                float ratio = 0.0;
                                if(time >= Segment->FilterVideoFadeInStart)
                                {
                                    ratio = (float)(time - Segment->FilterVideoFadeInStart) / (float)Segment->FilterVideoFadeInDuration;
                                }
                                glEnable(GL_BLEND);
                                glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
                                glColor4f(0.0f, 0.0f, 0.0f, (float)ratio);
                                glBegin(GL_QUADS);
                                    glVertex2d(GlPanelLeft, GlPanelTop); // top left
                                    glVertex2d(GlPanelRight, GlPanelTop); // top right
                                    glVertex2d(GlPanelRight, GlPanelBottom); // bottom right
                                    glVertex2d(GlPanelLeft, GlPanelBottom); // bottom left
                                glEnd();
                                glDisable(GL_BLEND);
                            }
                        }

                        // fade out
                        if(Segment->FilterVideoFadeOutStart > 0 && Segment->FilterVideoFadeOutDuration > 0)
                        {
                            if(time >= Segment->FilterVideoFadeOutStart)
                            {
                                float ratio = 0.0;
                                if(time <= Segment->FilterVideoFadeOutStart + Segment->FilterVideoFadeOutDuration)
                                {
                                    ratio = (float)(Segment->FilterVideoFadeOutStart + Segment->FilterVideoFadeOutDuration - time) / (float)Segment->FilterVideoFadeOutDuration;
                                }
                                glEnable(GL_BLEND);
                                glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
                                glColor4f(0.0f, 0.0f, 0.0f, (float)ratio);
                                glBegin(GL_QUADS);
                                    glVertex2d(GlPanelLeft, GlPanelTop); // top left
                                    glVertex2d(GlPanelRight, GlPanelTop); // top right
                                    glVertex2d(GlPanelRight, GlPanelBottom); // bottom right
                                    glVertex2d(GlPanelLeft, GlPanelBottom); // bottom left
                                glEnd();
                                glDisable(GL_BLEND);
                            }
                        }
                    }
                }
            }
            else
            {
                TextCtrlTime->SetValue(Libav::MilliToSMPTE(efl->GetTimeFromFrame(SelectedStream, SelectedFrame)) + wxT(" / ") + Libav::MilliToSMPTE(efl->VideoStreams[SelectedStream]->Duration) + wxT(" []"));
            }

            // dereference pointer (free is done by GOPBuffer)
            Texture = NULL;
            efl = NULL;
        }

        // glFlush(); // will automatically be called by wxGLCanvas->SwapBuffers()

        // BOTTLENECK
        GLCanvasPreview->SwapBuffers();
        glFinish();
    }
}

void AVConvGUIFrame::OnGLCanvasPreviewResize(wxSizeEvent& event)
{
    // NOTE: moved into RenderFrame() because it is a really fast operation
    /*
    // check if control is on display
    if(GLCanvasPreview->GetContext())
    {
        int GlPanelWidth;// = GLCanvasPreview->GetSize().x;
        int GlPanelHeight;// = GLCanvasPreview->GetSize().y;
        GLCanvasPreview->GetClientSize(&GlPanelWidth, &GlPanelHeight);
        GLCanvasPreview->SetCurrent();
        glViewport(0, 0, GlPanelWidth, GlPanelHeight);
    }
    */
}

void AVConvGUIFrame::OnResize(wxSizeEvent& event)
{
    this->Layout();

    // prevent flickering when changing column size...
    ListCtrlTasks->Freeze();
    ListCtrlSegments->Freeze();

    // always assume scrollbar is visible, never use GetClientSize
    int FilesWidth = ListCtrlTasks->GetSize().GetWidth()-24;
    ListCtrlTasks->SetColumnWidth(0, FilesWidth-80-80);
    ListCtrlTasks->SetColumnWidth(1, 80);
    ListCtrlTasks->SetColumnWidth(2, 80);

    int SegmentsWidth = ListCtrlSegments->GetSize().GetWidth()-24;
    ListCtrlSegments->SetColumnWidth(0, SegmentsWidth/2);
    ListCtrlSegments->SetColumnWidth(1, SegmentsWidth/2);

    ListCtrlSegments->Thaw();
    ListCtrlTasks->Thaw();

    RenderFrame();
}

void AVConvGUIFrame::OnSpinCtrlCropChange(wxSpinEvent& event)
{
    int top = SpinCtrlTop->GetValue();
    int bottom = SpinCtrlBottom->GetValue();
    int left = SpinCtrlLeft->GetValue();
    int right = SpinCtrlRight->GetValue();

    long TaskIndex;
    SelectedStreamIndex StreamIndex;
    VideoStream* vStream;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(size_t v=0; v<SelectedVideoStreamIndices.GetCount(); v++)
        {
            StreamIndex = SelectedVideoStreamIndices[v];
            vStream = EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->VideoStreams[StreamIndex.StreamIndex];

            if(top > 0 || bottom > 0 || left > 0 || right > 0)
            {
                vStream->EncodingSettings.Crop[0] = 1;
            }
            else
            {
                vStream->EncodingSettings.Crop[0] = 0;
            }

            vStream->EncodingSettings.Crop[1] = vStream->Width - left - right;
            vStream->EncodingSettings.Crop[2] = vStream->Height - top - bottom;
            vStream->EncodingSettings.Crop[3] = left;
            vStream->EncodingSettings.Crop[4] = top;
        }
    }

    if(SelectedTaskIndices.GetCount() == 1 && SelectedVideoStreamIndices.GetCount() == 1)
    {
        TaskIndex = SelectedTaskIndices[0];
        StreamIndex = SelectedVideoStreamIndices[0];
        vStream = EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->VideoStreams[StreamIndex.StreamIndex];

        if(top > 0 || bottom > 0 || left > 0 || right > 0)
        {
            StaticTextFrameSize->SetLabel(wxString::Format(wxT("%i x %i"), vStream->Width - left - right, vStream->Height - top - bottom));
        }
        else
        {
            StaticTextFrameSize->SetLabel(wxString::Format(wxT("%i x %i"), vStream->Width, vStream->Height));
        }
    }
    else
    {
        StaticTextFrameSize->SetLabel(wxT("0000 x 0000"));
    }

    Layout();

    RenderFrame();

    //wxMessageBox(wxT("Crop Changed"));
}

void AVConvGUIFrame::OnButtonSegmentAddClick(wxCommandEvent& event)
{
    // NOTE: the segment time calculation is based on a selected video stream, so it won't work for multiple task/stream selections!
    if(SelectedTaskIndices.GetCount() == 1 && SelectedVideoStreamIndices.GetCount() == 1)
    {
        long TaskIndex = SelectedTaskIndices[0];
        SelectedStreamIndex StreamIndex = SelectedVideoStreamIndices[0];
        int64_t time = EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->GetTimeFromFrame((int)StreamIndex.StreamIndex, (long)SliderFrame->GetValue());
        long SegmentIndex = EncodingTasks[TaskIndex]->OutputSegments.GetCount();

        EncodingTasks[TaskIndex]->OutputSegments.Add(new FileSegment(EncodingTasks[TaskIndex]->OutputFile, time, time));

        ListCtrlSegments->InsertItem(SegmentIndex, wxEmptyString);
        ListCtrlSegments->SetItem(SegmentIndex, 0, Libav::MilliToSMPTE(time));
        ListCtrlSegments->SetItem(SegmentIndex, 1, Libav::MilliToSMPTE(time));
        ListCtrlSegments->SetItemState(SegmentIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }

    //UpdateSelectedSegmentIndices(); -> triggered by SetItemState
    //wxMessageBox(wxT("Segment Added"));
}

void AVConvGUIFrame::OnButtonSegmentDeleteClick(wxCommandEvent& event)
{
    long TaskIndex;
    long SegmentIndex = -1;

    ListCtrlSegments->Freeze();
    if(SelectedTaskIndices.GetCount() == 1)
    {
        TaskIndex = SelectedTaskIndices[0];
        for(long i=SelectedSegmentIndices.GetCount()-1; i>=0; i--)
        {
            SegmentIndex = SelectedSegmentIndices[i];
            EncodingTasks[TaskIndex]->OutputSegments.RemoveAt(SegmentIndex);
            // triggers update of selected segment indices on msw
            ListCtrlSegments->DeleteItem(SegmentIndex);
        }
        if(SegmentIndex >= ListCtrlSegments->GetItemCount())
        {
            SegmentIndex--;
        }
        ListCtrlSegments->SetItemState(SegmentIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
    ListCtrlSegments->Thaw();

    //wxListEvent le;
    //OnListCtrlSegmentsItemSelect(le); -> triggered by SetItemState
}

void AVConvGUIFrame::OnButtonSegmentFromClick(wxCommandEvent& event)
{
    long SegmentIndex = ListCtrlSegments->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if(SegmentIndex > -1)
    {
        if(SelectedTaskIndices.GetCount() == 1 && SelectedVideoStreamIndices.GetCount() == 1)
        {
            long TaskIndex = SelectedTaskIndices[0];
            SelectedStreamIndex StreamIndex = SelectedVideoStreamIndices[0];
            int64_t time = EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->GetTimeFromFrame((int)StreamIndex.StreamIndex, (long)SliderFrame->GetValue());

            EncodingTasks[TaskIndex]->OutputSegments[SegmentIndex]->TimeFrom = time;

            ListCtrlSegments->SetItem(SegmentIndex, 0, Libav::MilliToSMPTE(time));
        }
    }

    //wxMessageBox(wxT("Set Segment From"));
}

void AVConvGUIFrame::OnButtonSegmentToClick(wxCommandEvent& event)
{
    long SegmentIndex = ListCtrlSegments->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if(SegmentIndex > -1)
    {
        if(SelectedTaskIndices.GetCount() == 1 && SelectedVideoStreamIndices.GetCount() == 1)
        {
            long TaskIndex = SelectedTaskIndices[0];
            SelectedStreamIndex StreamIndex = SelectedVideoStreamIndices[0];
            int64_t time = EncodingTasks[TaskIndex]->InputFiles[StreamIndex.FileIndex]->GetTimeFromFrame((int)StreamIndex.StreamIndex, (long)SliderFrame->GetValue());

            EncodingTasks[TaskIndex]->OutputSegments[SegmentIndex]->TimeTo = time;

            ListCtrlSegments->SetItem(SegmentIndex, 1, Libav::MilliToSMPTE(time));
        }
    }

    //wxMessageBox(wxT("Set Segment To"));
}

void AVConvGUIFrame::OnComboBoxFileFormatSelect(wxCommandEvent& event)
{
    EnableDisableAVFormatControls();

    long TaskIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        EncodingTasks[TaskIndex]->OutputFormat = FormatToSetting(ComboBoxFileFormat->GetValue());
        EncodingTasks[TaskIndex]->OutputFile.SetExt(Libav::FormatExtensionMap[EncodingTasks[TaskIndex]->OutputFormat]);
    }

    if(SelectedTaskIndices.GetCount() == 1)
    {
        TaskIndex = SelectedTaskIndices[0];
        // update modified fileout in textctrl (without trigger event)
        TextCtrlFileOut->ChangeValue(EncodingTasks[TaskIndex]->OutputFile.GetFullPath());
    }

    //wxMessageBox(wxT("FileFormat Changed"));
}

void AVConvGUIFrame::OnTextCtrlFileOutChange(wxCommandEvent& event)
{
    long TaskIndex;
    long CaretPosition;

    // on single task selection: change filename
    if(SelectedTaskIndices.GetCount() == 1)
    {
        TaskIndex = SelectedTaskIndices[0];
        EncodingTasks[TaskIndex]->OutputFile = wxFileName(TextCtrlFileOut->GetValue());
    }

    // on multi task selection: change directory, keep filename
    if(SelectedTaskIndices.GetCount() > 1)
    {
        wxString Seperator = wxFileName::GetPathSeparator();
        wxString Directory = TextCtrlFileOut->GetValue();

        if(!Directory.EndsWith(Seperator + wxT("*")))
        {
            Directory = Directory + Seperator + wxT("*");
            CaretPosition = TextCtrlFileOut->GetInsertionPoint();
            TextCtrlFileOut->ChangeValue(Directory);
            TextCtrlFileOut->SetInsertionPoint(CaretPosition);
        }

        // colorify last two characters ("{SEP}*")
        if(!TextCtrlFileOut->SetStyle(TextCtrlFileOut->GetValue().Len()-2, TextCtrlFileOut->GetValue().Len(), wxTextAttr(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT))))
        {
            // set color failed, check platform support and enable wxTE_RICH2 & wxTE_MULTILINE
        }

        Directory = Directory.BeforeLast('*');

        for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
        {
            TaskIndex = SelectedTaskIndices[i];
            EncodingTasks[TaskIndex]->OutputFile.SetPath(Directory);
        }
    }
}

void AVConvGUIFrame::OnCheckListBoxVideoStreamsSelect(wxCommandEvent& event)
{
    UpdateSelectedVideoIndices();

    if(SelectedTaskIndices.GetCount() < 1 || SelectedVideoStreamIndices.GetCount() < 1)
    {
        // enable/disable controls
        //{
            SliderFrame->Disable();

            SpinCtrlLeft->Disable();
            SpinCtrlRight->Disable();
            SpinCtrlTop->Disable();
            SpinCtrlBottom->Disable();
            StaticTextFrameSize->Disable();

            ComboBoxVideoCodec->Enable();
            ComboBoxVideoBitrate->Enable();
            ComboBoxVideoFrameSize->Enable();
            ComboBoxVideoAspectRatio->Enable();
        //}

        // set control values
        //{
            SliderFrame->SetValue(0);
            SliderFrame->SetRange(0, 1);
            TextCtrlTime->SetValue(wxT("00:00:00.000 / 00:00:00.000 []"));
        //}
    }
    else
    {
        // enable/disable controls
        //{
            SliderFrame->Enable();

            SpinCtrlLeft->Enable();
            SpinCtrlRight->Enable();
            SpinCtrlTop->Enable();
            SpinCtrlBottom->Enable();
            StaticTextFrameSize->Enable();

            ComboBoxVideoCodec->Enable();
            ComboBoxVideoBitrate->Enable();
            ComboBoxVideoFrameSize->Enable();
            ComboBoxVideoAspectRatio->Enable();
        //}

        long TaskIndex = SelectedTaskIndices[0];
        SelectedStreamIndex VideoIndex = SelectedVideoStreamIndices[0];

        // set control values
        //{
            VideoStream* vStream = EncodingTasks[TaskIndex]->InputFiles[VideoIndex.FileIndex]->VideoStreams[VideoIndex.StreamIndex];
            SliderFrame->SetValue(0);
            SliderFrame->SetRange(0, vStream->FrameCount); // keep additional frame that marks full duration of stream (last frame timestamp + last frame duration)
            TextCtrlTime->SetValue(wxT("00:00:00.000 / ") + Libav::MilliToSMPTE(vStream->Duration) + wxT(" []"));
            if(vStream->EncodingSettings.Crop[0] > 0)
            {
                SpinCtrlLeft->SetValue(vStream->EncodingSettings.Crop[3]);
                SpinCtrlTop->SetValue(vStream->EncodingSettings.Crop[4]);
                SpinCtrlRight->SetValue(vStream->Width - vStream->EncodingSettings.Crop[3] - vStream->EncodingSettings.Crop[1]);
                SpinCtrlBottom->SetValue(vStream->Height - vStream->EncodingSettings.Crop[4] - vStream->EncodingSettings.Crop[2]);
                StaticTextFrameSize->SetLabel(wxString::Format(wxT("%i x %i"), vStream->EncodingSettings.Crop[1], vStream->EncodingSettings.Crop[2]));
            }
            else
            {
                SpinCtrlLeft->SetValue(0);
                SpinCtrlTop->SetValue(0);
                SpinCtrlRight->SetValue(0);
                SpinCtrlBottom->SetValue(0);
                StaticTextFrameSize->SetLabel(wxString::Format(wxT("%i x %i"), vStream->Width, vStream->Height));
            }
            ComboBoxVideoCodec->SetValue(FormatFromSetting(vStream->EncodingSettings.Codec, STR_DEFAULT));
            ComboBoxVideoBitrate->SetValue(FormatFromSetting(vStream->EncodingSettings.Bitrate, STR_DEFAULT));
            ComboBoxVideoFrameSize->SetValue(FormatFromSetting(vStream->EncodingSettings.FrameSize, STR_NO_CHANGE));
            ComboBoxVideoAspectRatio->SetValue(FormatFromSetting(vStream->EncodingSettings.AspectRatio, STR_NO_CHANGE));
            vStream = NULL;
        //}

        if(SelectedTaskIndices.GetCount() > 1 || SelectedVideoStreamIndices.GetCount() > 1)
        {
            // enable/disable controls
            //{
                SliderFrame->Disable();
                StaticTextFrameSize->Disable();
            //}

            // set control values
            //{
                SliderFrame->SetValue(0);
                SliderFrame->SetRange(0, 1);
                TextCtrlTime->SetValue(wxT("00:00:00.000 / 00:00:00.000 []"));

                // loop through all remaining tasks & audios and scan for intersection settings (overlapping settings)
                for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
                {
                    TaskIndex = SelectedTaskIndices[t];
                    for(size_t v=0; v<SelectedVideoStreamIndices.GetCount(); v++)
                    {
                        VideoIndex = SelectedVideoStreamIndices[v];
                        vStream = EncodingTasks[TaskIndex]->InputFiles[VideoIndex.FileIndex]->VideoStreams[VideoIndex.StreamIndex];

                        if(SpinCtrlLeft->GetValue() != vStream->EncodingSettings.Crop[3])
                        {
                            SpinCtrlLeft->SetValue(0);
                        }

                        if(SpinCtrlTop->GetValue() != vStream->EncodingSettings.Crop[4])
                        {
                            SpinCtrlTop->SetValue(0);
                        }

                        if(SpinCtrlRight->GetValue() != vStream->Width - vStream->EncodingSettings.Crop[3] - vStream->EncodingSettings.Crop[1])
                        {
                            SpinCtrlRight->SetValue(0);
                        }

                        if(SpinCtrlBottom->GetValue() != vStream->Height - vStream->EncodingSettings.Crop[4] - vStream->EncodingSettings.Crop[2])
                        {
                            SpinCtrlBottom->SetValue(0);
                        }

                        if(!StaticTextFrameSize->GetLabel().IsSameAs(wxString::Format(wxT("%i x %i"), vStream->Width, vStream->Height)))
                        {
                            StaticTextFrameSize->SetLabel(wxT("0000 x 0000"));
                        }

                        if(!ComboBoxVideoCodec->GetValue().IsSameAs(FormatFromSetting(vStream->EncodingSettings.Codec, STR_DEFAULT)))
                        {
                            ComboBoxVideoCodec->SetValue(wxT("*"));
                        }

                        if(!ComboBoxVideoBitrate->GetValue().IsSameAs(FormatFromSetting(vStream->EncodingSettings.Bitrate, STR_DEFAULT)))
                        {
                            ComboBoxVideoBitrate->SetValue(wxT("*"));
                        }

                        if(!ComboBoxVideoFrameSize->GetValue().IsSameAs(FormatFromSetting(vStream->EncodingSettings.FrameSize, STR_NO_CHANGE)))
                        {
                            ComboBoxVideoFrameSize->SetValue(wxT("*"));
                        }

                        if(!ComboBoxVideoAspectRatio->GetValue().IsSameAs(FormatFromSetting(vStream->EncodingSettings.AspectRatio, STR_NO_CHANGE)))
                        {
                            ComboBoxVideoAspectRatio->SetValue(wxT("*"));
                        }

                        vStream = NULL;
                    }
                }
            //}
        }
    }

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        for(size_t f=0; f<EncodingTasks[i]->InputFiles.GetCount(); f++)
        {
            EncodingTasks[i]->InputFiles[f]->FlushBuffer();
        }
    }

    this->Layout();
    RenderFrame();
}

void AVConvGUIFrame::OnCheckListBoxVideoStreamsToggled(wxCommandEvent& event)
{
    long TaskIndex;
    wxString StreamIndex;
    SelectedStreamIndex VideoIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int v=0; v<CheckListBoxVideoStreams->GetCount(); v++)
        {
            // parse the list item to get file and stream index
            StreamIndex = CheckListBoxVideoStreams->GetString(v).BeforeFirst('#');
            VideoIndex.FileIndex = wxAtoi(StreamIndex.Before(':'));
            VideoIndex.StreamIndex = wxAtoi(StreamIndex.After(':'));
            EncodingTasks[TaskIndex]->InputFiles[VideoIndex.FileIndex]->VideoStreams[VideoIndex.StreamIndex]->Enabled = CheckListBoxVideoStreams->IsChecked(v);
        }
    }

    //wxMessageBox(wxT("Video Streams Selected"));
}

void AVConvGUIFrame::OnComboBoxVideoCodecSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex VideoIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int v=0; v<SelectedVideoStreamIndices.GetCount(); v++)
        {
            VideoIndex = SelectedVideoStreamIndices[v];
            EncodingTasks[TaskIndex]->InputFiles[VideoIndex.FileIndex]->VideoStreams[VideoIndex.StreamIndex]->EncodingSettings.Codec = FormatToSetting(ComboBoxVideoCodec->GetValue());
        }
    }

    //wxMessageBox(wxT("Video Codec Changed"));
}

void AVConvGUIFrame::OnComboBoxVideoBitrateSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex VideoIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int v=0; v<SelectedVideoStreamIndices.GetCount(); v++)
        {
            VideoIndex = SelectedVideoStreamIndices[v];
            EncodingTasks[TaskIndex]->InputFiles[VideoIndex.FileIndex]->VideoStreams[VideoIndex.StreamIndex]->EncodingSettings.Bitrate = FormatToSetting(ComboBoxVideoBitrate->GetValue());
        }
    }

    //wxMessageBox(wxT("Video Bitrate Changed"));
}

void AVConvGUIFrame::OnComboBoxVideoFrameSizeSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex VideoIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int v=0; v<SelectedVideoStreamIndices.GetCount(); v++)
        {
            VideoIndex = SelectedVideoStreamIndices[v];
            EncodingTasks[TaskIndex]->InputFiles[VideoIndex.FileIndex]->VideoStreams[VideoIndex.StreamIndex]->EncodingSettings.FrameSize = FormatToSetting(ComboBoxVideoFrameSize->GetValue());
        }
    }

    RenderFrame();

    //wxMessageBox(wxT("Video FrameSize Changed"));
}

void AVConvGUIFrame::OnComboBoxVideoAspectRatioSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex VideoIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int v=0; v<SelectedVideoStreamIndices.GetCount(); v++)
        {
            VideoIndex = SelectedVideoStreamIndices[v];
            EncodingTasks[TaskIndex]->InputFiles[VideoIndex.FileIndex]->VideoStreams[VideoIndex.StreamIndex]->EncodingSettings.AspectRatio = FormatToSetting(ComboBoxVideoAspectRatio->GetValue());
        }
    }

    RenderFrame();

    //wxMessageBox(wxT("Video AspectRatio Changed"));
}

void AVConvGUIFrame::OnCheckListBoxAudioStreamsSelect(wxCommandEvent& event)
{
    UpdateSelectedAudioIndices();

    if(SelectedTaskIndices.GetCount() < 1 || SelectedAudioStreamIndices.GetCount() < 1)
    {
        // enable/disable controls
        //{
            ComboBoxAudioCodec->Enable();
            ComboBoxAudioBitrate->Enable();
            ComboBoxAudioFrequency->Enable();
            ComboBoxAudioChannels->Enable();
        //}

        // set control values
        //{

        //}
    }
    else
    {
        // enable/disable controls
        //{
            ComboBoxAudioCodec->Enable();
            ComboBoxAudioBitrate->Enable();
            ComboBoxAudioFrequency->Enable();
            ComboBoxAudioChannels->Enable();
        //}

        long TaskIndex = SelectedTaskIndices[0];
        SelectedStreamIndex AudioIndex = SelectedAudioStreamIndices[0];

        // set control values
        //{
            AudioStream* aStream = EncodingTasks[TaskIndex]->InputFiles[AudioIndex.FileIndex]->AudioStreams[AudioIndex.StreamIndex];
            ComboBoxAudioCodec->SetValue(FormatFromSetting(aStream->EncodingSettings.Codec, STR_DEFAULT));
            ComboBoxAudioBitrate->SetValue(FormatFromSetting(aStream->EncodingSettings.Bitrate, STR_DEFAULT));
            ComboBoxAudioFrequency->SetValue(FormatFromSetting(aStream->EncodingSettings.Frequency, STR_NO_CHANGE));
            ComboBoxAudioChannels->SetValue(FormatFromSetting(aStream->EncodingSettings.Channels, STR_NO_CHANGE));
            aStream = NULL;
        //}

        if(SelectedTaskIndices.GetCount() > 1 || SelectedAudioStreamIndices.GetCount() > 1)
        {
            // enable/disable controls
            //{

            //}

            // set control values
            //{
                // loop through all remaining tasks & audios and scan for intersection settings (overlapping settings)
                for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
                {
                    TaskIndex = SelectedTaskIndices[t];
                    for(size_t a=0; a<SelectedAudioStreamIndices.GetCount(); a++)
                    {
                        AudioIndex = SelectedAudioStreamIndices[a];
                        aStream = EncodingTasks[TaskIndex]->InputFiles[AudioIndex.FileIndex]->AudioStreams[AudioIndex.StreamIndex];

                        if(!ComboBoxAudioCodec->GetValue().IsSameAs(FormatFromSetting(aStream->EncodingSettings.Codec, STR_DEFAULT)))
                        {
                            ComboBoxAudioCodec->SetValue(wxT("*"));
                        }

                        if(!ComboBoxAudioBitrate->GetValue().IsSameAs(FormatFromSetting(aStream->EncodingSettings.Bitrate, STR_DEFAULT)))
                        {
                            ComboBoxAudioBitrate->SetValue(wxT("*"));
                        }

                        if(!ComboBoxAudioFrequency->GetValue().IsSameAs(FormatFromSetting(aStream->EncodingSettings.Frequency, STR_NO_CHANGE)))
                        {
                            ComboBoxAudioFrequency->SetValue(wxT("*"));
                        }

                        if(!ComboBoxAudioChannels->GetValue().IsSameAs(FormatFromSetting(aStream->EncodingSettings.Channels, STR_NO_CHANGE)))
                        {
                            ComboBoxAudioChannels->SetValue(wxT("*"));
                        }

                        aStream = NULL;
                    }
                }
            //}
        }
    }
}

void AVConvGUIFrame::OnCheckListBoxAudioStreamsToggled(wxCommandEvent& event)
{
    long TaskIndex;
    wxString StreamIndex;
    SelectedStreamIndex AudioIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int a=0; a<CheckListBoxAudioStreams->GetCount(); a++)
        {
            // parse the list item to get file and stream index
            StreamIndex = CheckListBoxAudioStreams->GetString(a).BeforeFirst('#');
            AudioIndex.FileIndex = wxAtoi(StreamIndex.Before(':'));
            AudioIndex.StreamIndex = wxAtoi(StreamIndex.After(':'));
            EncodingTasks[TaskIndex]->InputFiles[AudioIndex.FileIndex]->AudioStreams[AudioIndex.StreamIndex]->Enabled = CheckListBoxAudioStreams->IsChecked(a);
        }
    }

    //wxMessageBox(wxT("Audio Streams Selected"));
}

void AVConvGUIFrame::OnComboBoxAudioCodecSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex AudioIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int a=0; a<SelectedAudioStreamIndices.GetCount(); a++)
        {
            AudioIndex = SelectedAudioStreamIndices[a];
            EncodingTasks[TaskIndex]->InputFiles[AudioIndex.FileIndex]->AudioStreams[AudioIndex.StreamIndex]->EncodingSettings.Codec = FormatToSetting(ComboBoxAudioCodec->GetValue());
        }
    }

    //wxMessageBox(wxT("Audio Codec Changed"));
}

void AVConvGUIFrame::OnComboBoxAudioBitrateSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex AudioIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int a=0; a<SelectedAudioStreamIndices.GetCount(); a++)
        {
            AudioIndex = SelectedAudioStreamIndices[a];
            EncodingTasks[TaskIndex]->InputFiles[AudioIndex.FileIndex]->AudioStreams[AudioIndex.StreamIndex]->EncodingSettings.Bitrate = FormatToSetting(ComboBoxAudioBitrate->GetValue());
        }
    }

    //wxMessageBox(wxT("Audio Bitrate Changed"));
}

void AVConvGUIFrame::OnComboBoxAudioFrequencySelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex AudioIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int a=0; a<SelectedAudioStreamIndices.GetCount(); a++)
        {
            AudioIndex = SelectedAudioStreamIndices[a];
            EncodingTasks[TaskIndex]->InputFiles[AudioIndex.FileIndex]->AudioStreams[AudioIndex.StreamIndex]->EncodingSettings.Frequency = FormatToSetting(ComboBoxAudioFrequency->GetValue());
        }
    }

    //wxMessageBox(wxT("Audio Frequency Changed"));
}

void AVConvGUIFrame::OnComboBoxAudioChannelsSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex AudioIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int a=0; a<SelectedAudioStreamIndices.GetCount(); a++)
        {
            AudioIndex = SelectedAudioStreamIndices[a];
            EncodingTasks[TaskIndex]->InputFiles[AudioIndex.FileIndex]->AudioStreams[AudioIndex.StreamIndex]->EncodingSettings.Channels = FormatToSetting(ComboBoxAudioChannels->GetValue());
        }
    }

    //wxMessageBox(wxT("Audio Channels Changed"));
}

void AVConvGUIFrame::OnCheckListBoxSubtitleStreamsSelect(wxCommandEvent& event)
{
    UpdateSelectedSubtitleIndices();

    if(SelectedTaskIndices.GetCount() < 1 || SelectedSubtitleStreamIndices.GetCount() < 1)
    {
        // enable/disable controls
        //{
            ComboBoxSubtitleCodec->Enable();
        //}

        // set control values
        //{

        //}
    }
    else
    {
        // enable/disable controls
        //{
            ComboBoxSubtitleCodec->Enable();
        //}

        long TaskIndex = SelectedTaskIndices[0];
        SelectedStreamIndex SubtitleIndex = SelectedSubtitleStreamIndices[0];

        // set control values
        //{
            SubtitleStream* sStream = EncodingTasks[TaskIndex]->InputFiles[SubtitleIndex.FileIndex]->SubtitleStreams[SubtitleIndex.StreamIndex];
            ComboBoxSubtitleCodec->SetValue(FormatFromSetting(sStream->EncodingSettings.Codec, STR_DEFAULT));
            sStream = NULL;
        //}

        if(SelectedTaskIndices.GetCount() > 1 || SelectedSubtitleStreamIndices.GetCount() > 1)
        {
            // enable/disable controls
            //{

            //}

            // set control values
            //{
                // loop through all remaining tasks & subtitles and scan for intersection settings (overlapping settings)
                for(size_t t=0; t<SelectedTaskIndices.GetCount(); t++)
                {
                    TaskIndex = SelectedTaskIndices[t];
                    for(size_t s=0; s<SelectedSubtitleStreamIndices.GetCount(); s++)
                    {
                        SubtitleIndex = SelectedSubtitleStreamIndices[s];
                        sStream = EncodingTasks[TaskIndex]->InputFiles[SubtitleIndex.FileIndex]->SubtitleStreams[SubtitleIndex.StreamIndex];

                        if(!ComboBoxSubtitleCodec->GetValue().IsSameAs(FormatFromSetting(sStream->EncodingSettings.Codec, STR_DEFAULT)))
                        {
                            ComboBoxSubtitleCodec->SetValue(wxT("*"));
                        }

                        sStream = NULL;
                    }
                }
            //}
        }
    }
}

void AVConvGUIFrame::OnCheckListBoxSubtitleStreamsToggled(wxCommandEvent& event)
{
    long TaskIndex;
    wxString StreamIndex;
    SelectedStreamIndex SubtitleIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int s=0; s<CheckListBoxSubtitleStreams->GetCount(); s++)
        {
            // parse the list item to get file and stream index
            StreamIndex = CheckListBoxSubtitleStreams->GetString(s).BeforeFirst('#');
            SubtitleIndex.FileIndex = wxAtoi(StreamIndex.Before(':'));
            SubtitleIndex.StreamIndex = wxAtoi(StreamIndex.After(':'));
            EncodingTasks[TaskIndex]->InputFiles[SubtitleIndex.FileIndex]->SubtitleStreams[SubtitleIndex.StreamIndex]->Enabled = CheckListBoxSubtitleStreams->IsChecked(s);
        }
    }

    //wxMessageBox(wxT("Subtitle Streams Selected"));
}

void AVConvGUIFrame::OnComboBoxSubtitleCodecSelect(wxCommandEvent& event)
{
    long TaskIndex;
    SelectedStreamIndex SubtitleIndex;

    for(size_t i=0; i<SelectedTaskIndices.GetCount(); i++)
    {
        TaskIndex = SelectedTaskIndices[i];
        for(unsigned int s=0; s<SelectedSubtitleStreamIndices.GetCount(); s++)
        {
            SubtitleIndex = SelectedSubtitleStreamIndices[s];
            EncodingTasks[TaskIndex]->InputFiles[SubtitleIndex.FileIndex]->SubtitleStreams[SubtitleIndex.StreamIndex]->EncodingSettings.Codec = FormatToSetting(ComboBoxSubtitleCodec->GetValue());
        }
    }

    //wxMessageBox(wxT("Subtitle Codec Changed"));
}

void AVConvGUIFrame::OnMenuPresetsClick(wxCommandEvent& event)
{
    wxArrayString PresetSettings = AVConvSettings::LoadPreset(MenuPresets->GetLabel(event.GetId()));

    wxCommandEvent ce;

    wxString Value;
    for(size_t i=0; i<PresetSettings.GetCount(); i++)
    {
        if(PresetSettings[i].StartsWith(wxT("file_format="), &Value))
        {
            ComboBoxFileFormat->SetValue(Value);
            OnComboBoxFileFormatSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("video_codec="), &Value))
        {
            ComboBoxVideoCodec->SetValue(Value);
            OnComboBoxVideoCodecSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("video_bitrate="), &Value))
        {
            ComboBoxVideoBitrate->SetValue(Value);
            OnComboBoxVideoBitrateSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("video_framesize="), &Value))
        {
            ComboBoxVideoFrameSize->SetValue(Value);
            OnComboBoxVideoFrameSizeSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("video_aspectratio="), &Value))
        {
            ComboBoxVideoAspectRatio->SetValue(Value);
            OnComboBoxVideoAspectRatioSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("audio_codec="), &Value))
        {
            ComboBoxAudioCodec->SetValue(Value);
            OnComboBoxAudioCodecSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("audio_bitrate="), &Value))
        {
            ComboBoxAudioBitrate->SetValue(Value);
            OnComboBoxAudioBitrateSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("audio_frequency="), &Value))
        {
            ComboBoxAudioFrequency->SetValue(Value);
            OnComboBoxAudioFrequencySelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("audio_channels="), &Value))
        {
            ComboBoxAudioChannels->SetValue(Value);
            OnComboBoxAudioChannelsSelect(ce);
        }
        if(PresetSettings[i].StartsWith(wxT("subtitle_codec="), &Value))
        {
            ComboBoxSubtitleCodec->SetValue(Value);
            OnComboBoxSubtitleCodecSelect(ce);
        }
    }
}

void AVConvGUIFrame::OnMainWindowRClick(wxMouseEvent& event)
{
    int id = 0;
    while(MenuPresets->GetMenuItemCount() > 0)
    {
        MenuPresets->Delete(id);
        id++;
    }
    wxArrayString Presets = AVConvSettings::GetPresets();
    for(size_t i=0; i<Presets.GetCount(); i++)
    {
        MenuPresets->Append(i, Presets[i]);
    }
    this->PopupMenu(MenuMain);
}

void AVConvGUIFrame::OnMenuSegmentFiltersClick(wxCommandEvent& event)
{
    //long TaskIndex;
    long SegmentIndex;
    if(SelectedTaskIndices.GetCount() == 1 && SelectedSegmentIndices.GetCount() == 1)
    {
        SegmentIndex = SelectedSegmentIndices[0];

        FileSegment* Segment = EncodingTasks[SelectedTaskIndices[0]]->OutputSegments[SegmentIndex];
        if(event.GetId() == VideoFadeIn)
        {
            wxTextEntryDialog win(NULL, wxT("Please enter the start time and the duration.\nValues must be seperated by : and in milli seconds.\nFrames before the start time are blacked out.\n\nExample:\nFade in from 5.0 over 2.5 seconds -> 5000:2500"), wxT("Video Fade-In"));
            win.SetValue(wxString::Format(wxT("%lu:%lu"), (long)Segment->FilterVideoFadeInStart, (long)Segment->FilterVideoFadeInDuration));
            if(win.ShowModal() == wxID_OK)
            {
                win.GetValue().BeforeFirst(':').ToLong((long*)&Segment->FilterVideoFadeInStart);
                win.GetValue().AfterLast(':').ToLong((long*)&Segment->FilterVideoFadeInDuration);
                RenderFrame();
            }
        }
        if(event.GetId() == VideoFadeOut)
        {
            wxTextEntryDialog win(NULL, wxT("Please enter the start time and the duration.\nValues must be seperated by : and in milli seconds.\nFrames after the duration are blacked out.\n\nExample:\nFade out from 4773.8 over 2.7 seconds -> 4773800:2700"), wxT("Video Fade-Out"));
            win.SetValue(wxString::Format(wxT("%lu:%lu"), (long)Segment->FilterVideoFadeOutStart, (long)Segment->FilterVideoFadeOutDuration));
            if(win.ShowModal() == wxID_OK)
            {
                win.GetValue().BeforeFirst(':').ToLong((long*)&Segment->FilterVideoFadeOutStart);
                win.GetValue().AfterLast(':').ToLong((long*)&Segment->FilterVideoFadeOutDuration);
                RenderFrame();
            }
        }
        if(event.GetId() == AudioFadeIn)
        {
            wxTextEntryDialog win(NULL, wxT("Please enter the start time and the duration.\nValues must be seperated by : and in milli seconds.\nSound before the start time is silenced.\n\nExample:\nFade in from 5.0 over 2.5 seconds -> 5000:2500"), wxT("Audio Fade-In"));
            win.SetValue(wxString::Format(wxT("%lu:%lu"), (long)Segment->FilterAudioFadeInStart, (long)Segment->FilterAudioFadeInDuration));
            if(win.ShowModal() == wxID_OK)
            {
                win.GetValue().BeforeFirst(':').ToLong((long*)&Segment->FilterAudioFadeInStart);
                win.GetValue().AfterLast(':').ToLong((long*)&Segment->FilterAudioFadeInDuration);
            }
        }
        if(event.GetId() == AudioFadeOut)
        {
            wxTextEntryDialog win(NULL, wxT("Please enter the start time and the duration.\nValues must be seperated by : and in milli seconds.\nSound after the duration is silenced.\n\nExample:\nFade out from 4773.8 over 2.7 seconds -> 4773800:2700"), wxT("Audio Fade-Out"));
            win.SetValue(wxString::Format(wxT("%lu:%lu"), (long)Segment->FilterAudioFadeOutStart, (long)Segment->FilterAudioFadeOutDuration));
            if(win.ShowModal() == wxID_OK)
            {
                win.GetValue().BeforeFirst(':').ToLong((long*)&Segment->FilterAudioFadeOutStart);
                win.GetValue().AfterLast(':').ToLong((long*)&Segment->FilterAudioFadeOutDuration);
            }
        }
        Segment = NULL;
    }
}

void AVConvGUIFrame::OnListCtrlSegmentsRClick(wxMouseEvent& event)
{
    if(SelectedTaskIndices.GetCount() == 1 && SelectedSegmentIndices.GetCount() == 1)
    {
        this->PopupMenu(MenuSegmentFilters);
    }
}

void AVConvGUIFrame::OnButtonScriptClick(wxCommandEvent& event)
{
    #ifdef __LINUX__
    FileDialogSaveFile->SetWildcard(wxT("Shell Script (*.sh)|*.sh|All Files (*.*)|*.*"));
    #endif
    #ifdef __WINDOWS__
    FileDialogSaveFile->SetWildcard(wxT("CMD Script (*.cmd)|*.cmd|All Files (*.*)|*.*"));
    #endif

    if(FileDialogSaveFile->ShowModal() == wxID_OK && !FileDialogSaveFile->GetPath().IsEmpty())
    {
        wxTextFile ScriptFile;

        if(!ScriptFile.Create(FileDialogSaveFile->GetPath()))
        {
            ScriptFile.Open(FileDialogSaveFile->GetPath());
            ScriptFile.Clear();
        }

        #ifdef __LINUX__
        ScriptFile.AddLine(wxT("#!/bin/sh"));
        #endif
        #ifdef __WINDOWS__
        ScriptFile.AddLine(wxT("::cmd script"));
        #endif
        ScriptFile.AddLine(wxEmptyString);

        size_t TaskCount = wxMin((size_t)ListCtrlTasks->GetItemCount(), EncodingTasks.GetCount());
        for(size_t t=0; t<TaskCount; t++)
        {
            wxArrayString TaskCommands = EncodingTasks[t]->GetCommands();
            for(size_t c=0; c<TaskCommands.GetCount(); c++)
            {
                ScriptFile.AddLine(TaskCommands[c]);

                #ifdef __LINUX__
                ScriptFile.AddLine(wxT("clear"));
                #endif
                #ifdef __WINDOWS__
                ScriptFile.AddLine(wxT("cls"));
                #endif
            }
        }

        ScriptFile.Write();
        ScriptFile.Close();
    }
}

void AVConvGUIFrame::OnButtonEncodeClick(wxCommandEvent& event)
{
    if(!VerifySettings())
    {
        return;
    }

    long TaskPID;
    wxProcess* TaskProcess;
    wxTextInputStream* errtis;
    //wxTextInputStream* stdtis;
    wxTextOutputStream* stdtos;
    wxTextFile LogFile;
    long StartTime = wxGetLocalTime();

    size_t pos_start = 0;
    size_t pos_end = 0;
    wxString Line;
    wxString Frame;
    wxString Time;
    wxString Size;
    wxString Framerate;
    wxString Bitrate;

    // disable controls
    ListCtrlTasks->Disable();
    // trigger task changed event that will automatically clear/disable controls
    ListCtrlTasks->SetItemState(-1, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    ButtonAddTask->Disable();
    ButtonRemoveTask->Disable();
    ButtonEncode->Disable();
    ButtonAbort->Enable();

    AbortEncoding = false;
    wxArrayString TaskCommands;
    // minor security check
    size_t TaskCount = wxMin((size_t)ListCtrlTasks->GetItemCount(), EncodingTasks.GetCount());
    for(size_t t=0; t<TaskCount; t++)
    {
        if(!LogFile.Create(EncodingTasks[t]->OutputFile.GetFullPath() + wxT(".log")))
        {
            LogFile.Open(EncodingTasks[t]->OutputFile.GetFullPath() + wxT(".log"));
            LogFile.Clear();
        }

        // make current processed item visible
        ListCtrlTasks->EnsureVisible(t);
        // highlight task as currently processed in red
        ListCtrlTasks->SetItemTextColour(t, wxColour(250, 0, 0));

        TaskCommands = EncodingTasks[t]->GetCommands();
        for(size_t c=0; c<TaskCommands.GetCount(); c++)
        {
            LogFile.AddLine(wxEmptyString);
            LogFile.AddLine(wxT(">>"));
            LogFile.AddLine(wxT(">> ") + TaskCommands[c]);
            LogFile.AddLine(wxT(">>"));
            LogFile.AddLine(wxEmptyString);

            StatusBar->SetStatusText(wxString::Format(wxT("[%lu/%lu]: ") + EncodingTasks[t]->OutputFile.GetFullName(), (unsigned long)(c+1), (unsigned long)TaskCommands.GetCount()), 0);

            TaskProcess = new wxProcess();
            // overwriting terminate event prevents from crashing when using wxDELETE(wxProcess)
            TaskProcess->Connect(wxEVT_END_PROCESS, (wxObjectEventFunction)&AVConvGUIFrame::OnProcessTerinate, NULL, this);
            TaskProcess->Redirect();
            TaskPID = wxExecute(TaskCommands[c], wxEXEC_ASYNC, TaskProcess);

            errtis = new wxTextInputStream(*(TaskProcess->GetErrorStream()));
            //stdtis = new wxTextInputStream(*(TaskProcess->GetInputStream()));
            stdtos = new wxTextOutputStream(*(TaskProcess->GetOutputStream()));

            while(wxProcess::Exists(TaskPID))
            {
                if(AbortEncoding)
                {
                    wxBeginBusyCursor();
                    wxProgressDialog* ProgressDialog = new wxProgressDialog(wxT("Terminating Process"), wxT("Terminating process may take a while..."));

                    // ffmpeg uses 'q' keypress
                    if(Libav::ConverterApplication.GetName().StartsWith(wxT("ffmpeg")))
                    {
                        // NOTE: PutChar('q') is working on windows but wxProcess::Exists() can't be used
                        // so we need to terminate process as fast as possible to kill it before pretending loop finish
                        #ifdef __LINUX__
                        stdtos->PutChar('q');
                        #endif
                        #ifdef __WINDOWS__
                        //stdtos->PutChar('q');
                        wxProcess::Kill(TaskPID, wxSIGKILL);
                        #endif
                    }
                    // avconv uses signal handling to exit (ctrl+c / SIGINT)
                    else if(Libav::ConverterApplication.GetName().StartsWith(wxT("avconv")))
                    {
                        // NOTE: The only way to terminate a wxProcess in windows seems to be SIGKILL
                        // on SIGINT the application freezes and the process keep running
                        #ifdef __LINUX__
                        wxProcess::Kill(TaskPID, wxSIGINT);
                        #endif
                        #ifdef __WINDOWS__
                        wxProcess::Kill(TaskPID, wxSIGKILL);
                        #endif
                    }
                    // unknown application: force kill
                    else
                    {
                        wxProcess::Kill(TaskPID, wxSIGKILL);
                    }

                    // wait until process is finished, before going to wxDELETE(process)
                    // wxProcess::Exists() reutrns true on windows
                    // -> http://forums.wxwidgets.org/viewtopic.php?t=24855&p=106240
                    // so we use a fake loop in windows to pretend some activity...
                    #ifdef __LINUX__
                    while(wxProcess::Exists(TaskPID))
                    #endif
                    #ifdef __WINDOWS__
                    for(int i=0; i<30; i++)
                    #endif
                    {
                        ProgressDialog->Pulse();
                        wxMilliSleep(50);
                        // use yield to process the message queue
                        // otherwise process might stuck because
                        // OnProcessTemrinate() will never be executed
                        wxYield();
                    }

                    ProgressDialog->Close();
                    wxDELETE(ProgressDialog);

                    // break out of the process loop (while)
                    break;
                }

                if(TaskProcess->IsErrorAvailable())
                {
                    Line = errtis->ReadLine();
                    // status related line
                    if(Line.StartsWith(wxT("frame=")) || Line.StartsWith(wxT("size=")))
                    {
                        Line.Replace(wxT(" "), wxEmptyString, true); // frame=279fps=20q=-1.0Lsize=2701kBtime=11.36bitrate=1948.6kbits/sdup=0...

                        // assume size is between "size=" and "time="
                        pos_start = Line.find(wxT("size="), pos_end) + 5;
                        pos_end = Line.find(wxT("time="), pos_start);
                        Size = Line.Mid(pos_start, pos_end - pos_start);
                        // assume time is between "time=" and "bitrate="
                        pos_start = Line.find(wxT("time="), pos_end) + 5;
                        pos_end = Line.find(wxT("bitrate="), pos_start);
                        Time = Line.Mid(pos_start, pos_end - pos_start);
                        // assume bitrate starts after "bitrate=" and ends with "/s"
                        pos_start = Line.find(wxT("bitrate="), pos_end) + 8;
                        pos_end = Line.find(wxT("/s"), pos_start) + 2;
                        Bitrate = Line.Mid(pos_start, pos_end - pos_start);

                        // audio || subtitle
                        if(Line.IsEmpty())
                        {
                            StatusBar->SetStatusText(wxT("Time: ") + Time + wxT(", Size: ") + Size + wxT(", ") + Bitrate, 1);
                        }
                        // video && (audio || subtitle)
                        else
                        {
                            // assume frame is between "frame=" and "fps="
                            pos_start = Line.find(wxT("frame="), 0) + 6;
                            pos_end = Line.find(wxT("fps="), pos_start);
                            Frame = Line.Mid(pos_start, pos_end - pos_start);
                            // assume framerate is between "fps=" and "q="
                            pos_start = Line.find(wxT("fps="), 0) + 4;
                            pos_end = Line.find(wxT("q="), pos_start);
                            Framerate = Line.Mid(pos_start, pos_end - pos_start);

                            StatusBar->SetStatusText(wxT("Frame: ") + Frame + wxT(", Time: ") + Time + wxT(", Size: ") + Size + wxT(", ") + Framerate + wxT("fps, ") + Bitrate, 1);
                        }

                        wxMilliSleep(50);
                    }
                    // non status related line, add to log file
                    else
                    {
                        LogFile.AddLine(Line);
                    }
                }
                /*
                if(TaskProcess->IsInputAvailable())
                {
                    // read stack from std stream
                    LogFile.AddLine(stdtis->ReadLine());
                }
                */
                StatusBar->SetStatusText(wxT("Time: ") + Libav::MilliToSMPTE((int64_t)(1000*(wxGetLocalTime()-StartTime))).BeforeLast('.'), 2);

                wxYield();
            }

            wxDELETE(errtis);
            //wxDELETE(stdtis);
            wxDELETE(stdtos);

            wxDELETE(TaskProcess);

            if(AbortEncoding)
            {
                LogFile.AddLine(wxT("ABORTED BY USER"));
                // break out of the task.commands loop (for)
                break;
            }
        }

        LogFile.Write();
        LogFile.Close();

        if(AbortEncoding)
        {
            wxEndBusyCursor();
            // break out of the tasks loop (for)
            break;
        }

        // highlight task as completed in green
        ListCtrlTasks->SetItemTextColour(t, wxColour(0, 200, 0));
    }

    // reset colours of tasks
    for(size_t t=0; t<TaskCount; t++)
    {
        ListCtrlTasks->SetItemTextColour(t, wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOXTEXT));
    }

    // reset status bar
    StatusBar->SetStatusText(wxT(""), 0);
    StatusBar->SetStatusText(wxT(""), 1);
    StatusBar->SetStatusText(wxT(""), 2);

    //enable controls
    ButtonAbort->Disable();
    ButtonEncode->Enable();
    ButtonRemoveTask->Enable();
    ButtonAddTask->Enable();
    ListCtrlTasks->Enable();
}

void AVConvGUIFrame::OnButtonAbortClick(wxCommandEvent& event)
{
    AbortEncoding = true;
}

void AVConvGUIFrame::OnProcessTerinate(wxProcessEvent& event)
{
    if(!AbortEncoding && (event.GetExitCode() != 0))
    {
        wxMessageBox(wxString::Format(wxT("External application exit with code: %i"), event.GetExitCode()));
    }
}

/*
wxInt32 ffGUIFrame::Verify(VideoIO *videoReader, EncodingJob *encodingJob)
{
    //[avi @ 02E620E0] Application provided invalid, non monotonically increasing dts to muxer in stream 1: 312479 >= 0
    //av_interleaved_write_frame(): Invalid argument

    //[libxvid @ 026FCA60] Invalid pixel aspect ratio 357/355
    //Video encoding failed

    //Format:
    //-------
    //flv       // requires audio samplerate < 48kHz
    //mpeg    // no problem

    //ACodec:
    //-------
    //aac       // requires -strict experimental
    //flac    // vlc unsupported
    //mp2       // vlc unsupported

    //VCodec:
    //-------
    //mpeg1video    // no problem
    //mpeg2video
    //mpeg4     // requires framerate with denominator < 65536 (16 bit)

    if(encodingJob->FileFormat == wxT("flv"))
    {
        wxString audioFrequency = encodingJob->AudioFrequency;
        audioFrequency.Replace(wxT(","), wxT("."), true);
        // remove dot '.' ?
        // 48k -> 48000
        // 48.5k -> 48500
        // 48000.5 -> 48000

        //wxString intFreq = audioFrequency.BeforeLast('.');
        //wxString ratFreq = audioFrequency.AfterLast('.');
        //if(ratFreq.EndsWith(wxT("k")))
        //{
            //audioFrequency = ;
        //}
        //else
        //{
            //audioFrequency = intFreq;

        //}

        audioFrequency.Replace(wxT("k"), wxT("000"), true);

        if(wxAtoi(audioFrequency) > 44100)
        {
            wxMessageBox(wxT("Audio frequency not supported in flv container!"));
            return 1;
        }
    }

    if(encodingJob->VideoCodec == wxT("mpeg4"))
    {
        if(encodingJob->VideoFrameRate == wxT("no change"))
        {
            AVRational avg_frame_rate = videoReader->pFormatCtx->streams[videoReader->SelectedVideoStream]->avg_frame_rate;
            if(avg_frame_rate.num > 65535 || avg_frame_rate.den > 65535)
            {
                wxMessageBox(wxT("Video framerate of source file is not supported in mpeg4 codec!\nPlease change the video framerate."));
                return 2;
            }
        }
    }

    if(encodingJob->VideoCodec == wxT("libxvid"))
    {
        AVRational sar;
        if(encodingJob->VideoFrameSize != wxT("no change"))
        {
            // parse SAR from encoding job if possible (drop if invalid [user typing])
        }
        else
        {
            sar.num = videoReader->pVideoCodecCtx->sample_aspect_ratio.num;
            sar.den = videoReader->pVideoCodecCtx->sample_aspect_ratio.den;
        }

        AVRational dar;
        if(encodingJob->VideoAspectRatio != wxT("no change"))
        {
            // parse DAR from encoding job if possible (drop if invalid [user typing])
        }
        else
        {
            dar.num = 0;
            dar.den = 0;
        }

        // calculate PAR
        AVRational par;
        par.num = 0;
        par.den = 0;

        // check if PAR is valid for libxvid
        if(false)
        {
            wxMessageBox(wxT("invalid PAR for libxvid"));
            return 3;
        }
    }

    return 0;
}
*/
bool AVConvGUIFrame::VerifySettings()
{
    wxString warning = wxEmptyString;
    wxString warning_prefix = wxEmptyString;

    VideoSettings* vSettings;
    AudioSettings* aSettings;
    SubtitleSettings* sSettings;

    wxArrayString supported_codecs;
    wxString selected_codec = wxEmptyString;
    bool codec_supported = false;

    for(size_t t=0; t<EncodingTasks.GetCount(); t++)
    {
        warning_prefix = wxString::Format(wxT("\n# Task=%lu"), (unsigned long)t);

        for(size_t f=0; f<EncodingTasks[t]->InputFiles.GetCount(); f++)
        {
            warning_prefix = wxString::Format(wxT("\n# Task=%lu, File=%lu"), (unsigned long)t, (unsigned long)f);

            if(EncodingTasks[t]->OutputFile.GetFullPath() == EncodingTasks[t]->InputFiles[f]->File.GetFullPath())
            {
                warning.Append(warning_prefix + wxT("\nTarget filename equals source filename!"));
            }

            for(size_t v=0; v<EncodingTasks[t]->InputFiles[f]->VideoStreams.GetCount(); v++)
            {
                if(EncodingTasks[t]->InputFiles[f]->VideoStreams[v]->Enabled)
                {
                    vSettings = &(EncodingTasks[t]->InputFiles[f]->VideoStreams[v]->EncodingSettings);
                    warning_prefix = wxString::Format(wxT("\n# Task=%lu, File=%lu, Stream=%lu"), (unsigned long)t, (unsigned long)f, (unsigned long)v);

                    supported_codecs = Libav::FormatVideoCodecs(EncodingTasks[t]->OutputFormat);
                    selected_codec = FormatFromSetting(vSettings->Codec.BeforeFirst(' '), wxT("default"));
                    codec_supported = false;
                    for(size_t c=0; c<supported_codecs.Count(); c++)
                    {
                        if(supported_codecs[c].IsSameAs(selected_codec))
                        {
                            codec_supported = true;
                            break;
                        }
                    }
                    if(!codec_supported)
                    {
                        warning.Append(warning_prefix + wxT("\nContainer format does not support the selected video codec!"));
                    }

                    if(vSettings->Bitrate.StartsWith(wxT("-crf")))
                    {
                        if(!vSettings->Codec.BeforeFirst(' ').IsSameAs(wxT("libx264")))
                        {
                            warning.Append(warning_prefix + wxT("\nConstant quality (-crf) not supported by the selected video codec!"));
                        }
                    }

                    vSettings = NULL;
                }
            }

            for(size_t a=0; a<EncodingTasks[t]->InputFiles[f]->AudioStreams.GetCount(); a++)
            {
                if(EncodingTasks[t]->InputFiles[f]->AudioStreams[a]->Enabled)
                {
                    aSettings = &(EncodingTasks[t]->InputFiles[f]->AudioStreams[a]->EncodingSettings);
                    warning_prefix = wxString::Format(wxT("\n# Task=%lu, File=%lu, Stream=%lu"), (unsigned long)t, (unsigned long)f, (unsigned long)a);

                    supported_codecs = Libav::FormatAudioCodecs(EncodingTasks[t]->OutputFormat);
                    selected_codec = FormatFromSetting(aSettings->Codec.BeforeFirst(' '), wxT("default"));
                    codec_supported = false;
                    for(size_t c=0; c<supported_codecs.Count(); c++)
                    {
                        if(supported_codecs[c].IsSameAs(selected_codec))
                        {
                            codec_supported = true;
                            break;
                        }
                    }
                    if(!codec_supported)
                    {
                        warning.Append(warning_prefix + wxT("\nContainer format does not support the selected audio codec!"));
                    }

                    /*
                    if(EncodingTasks[t]->OutputFormat.IsSameAs(wxT("flv")))
                    {
                        // convert frequency to number
                        int frequency = 0;
                        if(aSettings->Frequency.EndsWith(wxT("k")))
                        {
                            if(aSettings->Frequency.Find(wxT(".")))
                            {
                                // 44.1k -> 44100
                                // 22.05k -> 22050
                                //frequency = 1000 * wxAtoi(aSettings->Frequency.BeforeLast('.'));// + (wxAtoi(aSettings->Frequency.AfterLast('.').BeforeLast('k'));
                            }
                            else
                            {
                                // 48k -> 48000
                                //frequency = 1000 * wxAtoi(audioFrequency);
                                frequency = 1000 * wxAtoi(aSettings->Frequency.BeforeLast('k'));
                            }
                        }
                        else
                        {
                            // 48000 -> 48000
                            // 48000.5 -> 48000
                            frequency = wxAtoi(aSettings->Frequency);
                        }

                        if(frequency < 1 || frequency > 44100)
                        {
                            warning.Append(wxString::Format(wxT("\nTask %lu[%lu:%lu]: audio frequency not supported in flv (max. 44100)!"), (unsigned long)t, (unsigned long)f, (unsigned long)a));
                        }
                    }
                    */

                    aSettings = NULL;
                }
            }

            for(size_t s=0; s<EncodingTasks[t]->InputFiles[f]->SubtitleStreams.GetCount(); s++)
            {
                if(EncodingTasks[t]->InputFiles[f]->SubtitleStreams[s]->Enabled)
                {
                    sSettings = &(EncodingTasks[t]->InputFiles[f]->SubtitleStreams[s]->EncodingSettings);
                    warning_prefix = wxString::Format(wxT("\n# Task=%lu, File=%lu, Stream=%lu"), (unsigned long)t, (unsigned long)f, (unsigned long)s);

                    supported_codecs = Libav::FormatSubtitleCodecs(EncodingTasks[t]->OutputFormat);
                    selected_codec = FormatFromSetting(sSettings->Codec.BeforeFirst(' '), wxT("default"));
                    codec_supported = false;
                    for(size_t c=0; c<supported_codecs.Count(); c++)
                    {
                        if(supported_codecs[c].IsSameAs(selected_codec))
                        {
                            codec_supported = true;
                            break;
                        }
                    }
                    if(!codec_supported)
                    {
                        warning.Append(warning_prefix + wxT("\nContainer format does not support the selected subtitle codec!"));
                    }

                    sSettings = NULL;
                }
            }
        }
    }

    if(warning.IsEmpty())
    {
        return true;
    }
    else
    {
        wxMessageBox(warning);
        return false;
    }
}
