/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static int floatposgrid_x                  = 5; /* floatpos grid columns */
static int floatposgrid_y                  = 5; /* floatpos grid rows */
static const int smartgaps                 = 1;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps               = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int gappih           = 10; /* horiz inner gap between windows */
static const unsigned int gappiv           = 10; /* vert inner gap between windows */
static const unsigned int gappoh           = 10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 10; /* vert outer gap between windows and screen edge */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const int barheight                 = 10; /* additional pixels added to the font-derived bar height */
static const char *cursor_theme            = "Bibata-Modern-Ice";
static const char cursor_size[]            = "24"; /* Make sure it's a valid integer, otherwise things will break */
static const char *fonts[]                 = { "DWM Layout Glyphs:size=15",
												"Inter Regular:size=12"};
static const float rootcolor[]             = COLOR(0x000000ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm]	= { 0xbbbbbbff,	0x101010ff,	0x444444ff },
	[SchemeSel]		= { 0xeeeeeeff,	0x0000b0ff,	0x61afefff },
	[SchemeFloat]	= { 0,			0,			0xc678ddff },
	[SchemeUrg]		= { 0,			0,			0x770000ff },
	[SchemeLtSym]	= { 0xdddd00ff,	0x101010ff,	0 },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

/* Autostart */
static const char *const autostart[] = {
        "swaybg", "-i", "/usr/share/backgrounds/image05.jpg", "-m", "fill", NULL,
        NULL /* terminate */
};

static const Rule rules[] = {
	/* app_id		title			tags mask	isfloating	floatpos	monitor	scratchkey */
	{ "nwg-look",	NULL,			0,			1,			"50% 50% 80% 80%",		-1,			0 },
	{ "firefox",	NULL,			1 << 1,		0,			NULL,		-1,			0 },
	{ NULL,			"Scratchpad",	0,			1,			NULL,		-1,			't' },
};



/* layout(s) */
static const Layout layouts[] = {
    { "\ue000",		tile },
    { "\ue001",		monocle },
    { "\ue002",		deck },
    { "\ue003",		spiral },
    { "\ue004",		dwindle },
    { "\ue005",		grid },
    { "\ue006",		centeredmaster },
    { "\ue007",		centeredfloatingmaster },
    { "\ue00a",		gaplessgrid },
    { "\ue00b",		col },
    { "\ue00c",		bstack },
    { "\ue00d",		bstackhoriz },
};




/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const MonitorRule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x    y
    * example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 }, */
	{ NULL,       0.5f, 1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	.layout = "gb",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MOD, use WLR_MODIFIER_LOGO */
#define MOD WLR_MODIFIER_LOGO
#define SHIFT WLR_MODIFIER_SHIFT
#define CTRL WLR_MODIFIER_CTRL
#define ALT WLR_MODIFIER_ALT

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MOD,				KEY,		view,			{.ui = 1 << TAG} }, \
	{ MOD|CTRL,  		KEY,		toggleview,		{.ui = 1 << TAG} }, \
	{ MOD|SHIFT,		SKEY,		tag,			{.ui = 1 << TAG} }, \
	{ MOD|CTRL|SHIFT,	SKEY,		toggletag,		{.ui = 1 << TAG} }

/* commands */
static const char *termcmd[]	= { "ghostty", NULL };
static const char *menucmd[]	= { "wmenu-run", NULL };
static const char *webcmd[]		= { "firefox", NULL };

static const char *sptermcmd[]	= { "t", "ghostty", "--title=Scratchpad", NULL };

static const Key keys[] = {
	{ MOD, 			XKB_KEY_Return,			spawn,					{.v = termcmd} },
	{ MOD,			XKB_KEY_p,				spawn,					{.v = menucmd} },
	{ MOD,			XKB_KEY_w,				spawn,					{.v = webcmd} },
	{ MOD,			XKB_KEY_grave,			togglescratch,			{.v = sptermcmd } },
	{ MOD,			XKB_KEY_j,				focusstack,				{.i = +1} },
	{ MOD,			XKB_KEY_k,				focusstack,				{.i = -1} },
	{ MOD,			XKB_KEY_i,				incnmaster,				{.i = +1} },
	{ MOD,			XKB_KEY_d,				incnmaster,				{.i = -1} },
	{ MOD,			XKB_KEY_h,				setmfact,				{.f = -0.05f} },
	{ MOD,			XKB_KEY_l,				setmfact,				{.f = +0.05f} },
	{ MOD, 			XKB_KEY_q,				killclient,				{0} },
	{ MOD|SHIFT,	XKB_KEY_q,				quit,					{0} },
	{ MOD,			XKB_KEY_t,				setlayout,				{.v = &layouts[0]} },
	{ MOD,			XKB_KEY_m,				setlayout,				{.v = &layouts[1]} },
	{ MOD,			XKB_KEY_s,				setlayout,				{.v = &layouts[2]} },
	{ MOD,			XKB_KEY_Up,				cyclelayout,			{.i = +1} },
	{ MOD,			XKB_KEY_Down,			cyclelayout,			{.i = -1} },
	{ MOD|SHIFT,	XKB_KEY_b,				togglebar,				{0} },
	{ MOD|SHIFT, 	XKB_KEY_space,			togglefloating,			{0} },
	{ MOD,			XKB_KEY_e,				togglefullscreen,		{0} },
	{ MOD|SHIFT,	XKB_KEY_g,				togglegaps,				{0} },
	{ MOD,			XKB_KEY_0,				view,					{.ui = ~0} },
	{ MOD|SHIFT,	XKB_KEY_parenright,		tag,					{.ui = ~0} },
	{ MOD,			XKB_KEY_Left,			cycleview,				{.i = -1} },
	{ MOD,			XKB_KEY_Right,			cycleview,				{.i = +1} },
	{ MOD|SHIFT,	XKB_KEY_Left,			shifttag,				{.i = -1} },
	{ MOD|SHIFT,	XKB_KEY_Right,			shifttag,				{.i = +1} },
	{ MOD|CTRL,		XKB_KEY_Left,			shifttagview,			{.i = -1} },
	{ MOD|CTRL,		XKB_KEY_Right,			shifttagview,			{.i = +1} },

	TAGKEYS(		XKB_KEY_1,				XKB_KEY_exclam,			0),
	TAGKEYS(		XKB_KEY_2,				XKB_KEY_quotedbl,		1),
	TAGKEYS(		XKB_KEY_3,				XKB_KEY_sterling,		2),
	TAGKEYS(		XKB_KEY_4,				XKB_KEY_dollar,			3),
	TAGKEYS(		XKB_KEY_5,				XKB_KEY_percent,		4),
	TAGKEYS(		XKB_KEY_6,				XKB_KEY_asciicircum,	5),
	TAGKEYS(		XKB_KEY_7,				XKB_KEY_ampersand,		6),
	TAGKEYS(		XKB_KEY_8,				XKB_KEY_asterisk,		7),
	TAGKEYS(		XKB_KEY_9,				XKB_KEY_parenleft,		8),

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ CTRL|ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { CTRL|ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol,	0,		BTN_LEFT,		setlayout,		{.v = &layouts[0]} },
	{ ClkLtSymbol,	0,		BTN_RIGHT,		setlayout,		{.v = &layouts[2]} },
	{ ClkTitle,		0,		BTN_MIDDLE,		zoom,			{0} },
	{ ClkStatus,	0,		BTN_MIDDLE,		spawn,			{.v = termcmd} },
	{ ClkClient,	MOD,	BTN_LEFT,		moveresize,		{.ui = CurMove} },
	{ ClkClient,	MOD,	BTN_MIDDLE,		togglefloating,	{0} },
	{ ClkClient,	MOD,	BTN_RIGHT,		moveresize,		{.ui = CurResize} },
	{ ClkTagBar,	0,		BTN_LEFT,		view,			{0} },
	{ ClkTagBar,	0,		BTN_RIGHT,		toggleview,		{0} },
	{ ClkTagBar,	MOD,	BTN_LEFT,		tag,			{0} },
	{ ClkTagBar,	MOD,	BTN_RIGHT,		toggletag,		{0} },
};
