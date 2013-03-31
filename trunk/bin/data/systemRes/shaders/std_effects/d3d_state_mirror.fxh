// D3D State define mirrors (matches d3d9types.h)

// D3DBLEND
#define BW_BLEND_ZERO				1
#define BW_BLEND_ONE				2
#define BW_BLEND_SRCCOLOR			3
#define BW_BLEND_INVSRCCOLOR		4
#define BW_BLEND_SRCALPHA			5
#define BW_BLEND_INVSRCALPHA		6
#define BW_BLEND_DESTALPHA			7
#define BW_BLEND_INVDESTALPHA		8
#define BW_BLEND_DESTCOLOR			9
#define BW_BLEND_INVDESTCOLOR		10
#define BW_BLEND_SRCALPHASAT		11
#define BW_BLEND_BOTHSRCALPHA		12
#define BW_BLEND_BOTHINVSRCALPHA	13
#define BW_BLEND_BLENDFACTOR		14
#define BW_BLEND_INVBLENDFACTOR		15

// D3DCMPFUNC
#define BW_CMP_NEVER		1
#define BW_CMP_LESS			2
#define BW_CMP_EQUAL		3
#define BW_CMP_LESSEQUAL	4
#define BW_CMP_GREATER		5
#define BW_CMP_NOTEQUAL		6
#define BW_CMP_GREATEREQUAL	7
#define BW_CMP_ALWAYS		8

// D3DTEXTUREADDRESS
#define BW_WRAP			1
#define BW_MIRROR		2
#define BW_CLAMP		3
#define BW_BORDER		4
#define BW_MIRRORONCE	5 

// D3DCULL
#define BW_CULL_NONE	1
#define BW_CULL_CW		2
#define BW_CULL_CCW		3