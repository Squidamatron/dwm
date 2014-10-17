/* See LICENSE file for copyright and license details. */

// Allows the use of keyboard media keys
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "-*-xbmicons-medium-r-*-*-12-*-*-*-*-*-*-*" "," "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*" "," "-misc-kochi gothic-medium-r-normal-*-12-0-0-0-p-0-jisx0201.1976-0";
/*
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
*/
/* Molokai Colors 
static const char normbordercolor[] = "#222222";
static const char normbgcolor[]     = "#212021";
static const char normfgcolor[]     = "#DDDDDD";
static const char selbordercolor[]  = "#908884";
static const char selbgcolor[]      = "#212021";
static const char selfgcolor[]      = "#D81860";
*/

/* hybrid colors */
static const char normbordercolor[] = "#222222";
static const char normbgcolor[]     = "#1D1F21";
static const char normfgcolor[]     = "#C5C8C6";
static const char selbordercolor[]  = "#908884";
static const char selbgcolor[]      = "#1D1F21";
static const char selfgcolor[]      = "#CC6666";

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Steam",     NULL,       NULL,       0,            True,        -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
	{ "Firefox",  NULL,       NULL,       0,            False,       -1 },
	{ "feh",      NULL,       NULL,       0,            True,        -1 },
	{ "Viewnior", NULL,       NULL,       0,            True,        -1 },
	{ "Transmission", NULL,   NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
//static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", "-e", "tmux", NULL };
static const char *mpdplaypause[] = { "ncmpcpp", "-h", "ArchieMPD@localhost", "toggle", NULL };
static const char *mpdprev[] = { "ncmpcpp", "-h", "ArchieMPD@localhost", "prev", NULL };
static const char *mpdnext[] = { "ncmpcpp", "-h", "ArchieMPD@localhost", "next", NULL };
static const char *mpdvoldown[] = { "ncmpcpp", "-h", "ArchieMPD@localhost", "volume", "-1", NULL };
static const char *mpdvolup[] = { "ncmpcpp", "-h", "ArchieMPD@localhost", "volume", "+1", NULL };
static const char *mpdstop[] = { "ncmpcpp", "-h", "ArchieMPD@localhost", "stop", NULL };
static const char *launchncmpcpp[] = { "urxvtc", "-geometry", "130x44", "-e", "ncmpcpp", "-h", "ArchieMPD@localhost", NULL };
static const char *filemanager[] = { "thunar", NULL };
static const char *clifilemanager[] = { "urxvtc", "-geometry", "130x44", "-e", "ranger", NULL };
static const char *scrot[] = { "scrotscript", NULL }; 


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XF86XK_AudioPlay, spawn,   {.v = mpdplaypause } },
	{ 0,                            XF86XK_AudioPrev, spawn,   {.v = mpdprev } },
	{ 0,                            XF86XK_AudioNext, spawn,   {.v = mpdnext } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,   {.v = mpdvoldown } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,   {.v = mpdvolup } },
	{ 0,                            XF86XK_AudioMute, spawn,   {.v = mpdstop } },
	{ 0,                            XF86XK_Tools, spawn,       {.v = launchncmpcpp } },
	{ 0,                            XF86XK_HomePage, spawn,    {.v = filemanager } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = clifilemanager } },
	{ 0,                            XK_Print,  spawn,          {.v = scrot } },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

