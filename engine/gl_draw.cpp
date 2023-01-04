#include "glquake.h"

_Draw_String ORIG_Draw_String = NULL;
_GL_Bind ORIG_GL_Bind = NULL;
_Draw_Frame ORIG_Draw_Frame = NULL;
_BoxFilter3x3 ORIG_BoxFilter3x3 = NULL;
_GL_Upload32 ORIG_GL_Upload32 = NULL;
_GL_Upload16 ORIG_GL_Upload16 = NULL;

cvar_t* gl_spriteblend;
cvar_t* gl_dither;

int texels;
extern byte texgammatable[256];

static int scissor_x = 0, scissor_y = 0, scissor_width = 0, scissor_height = 0;
static qboolean giScissorTest = false;

void EnableScissorTest(int x, int y, int width, int height)
{
	x = std::clamp(x, 0, ScreenWidth);
	y = std::clamp(y, 0, ScreenHeight);
	width = std::clamp(width, 0, ScreenWidth - x);
	height = std::clamp(height, 0, ScreenHeight - y);

	scissor_x = x;
	scissor_width = width;
	scissor_y = y;
	scissor_height = height;

	giScissorTest = true;
}

void DisableScissorTest(void)
{
	scissor_x = 0;
	scissor_width = 0;
	scissor_y = 0;
	scissor_height = 0;

	giScissorTest = false;
}

void Draw_FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_LINES);
	glColor4f(r / 255.0, g / 255.0, b / 255.0, a / 255.0);

	glBegin(GL_RELATIVE_HORIZONTAL_LINE_TO_NV);
	glVertex2f(x, y);
	glVertex2f(w + x, y);
	glVertex2f(w + x, h + y);
	glVertex2f(x, h + y);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

int Draw_String(int x, int y, char* str)
{
	return ORIG_Draw_String(x, y, str); // TODO: implement
}

void Draw_FillRGBABlend(int x, int y, int w, int h, int r, int g, int b, int a)
{
	//g_engdstAddrs.pfnFillRGBA(&x, &y, &w, &h, &r, &g, &b, &a);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(r / 255.0, g / 255.0, b / 255.0, a / 255.0);

	glBegin(GL_RELATIVE_HORIZONTAL_LINE_TO_NV);
	glVertex2f(x, y);
	glVertex2f(w + x, y);
	glVertex2f(w + x, h + y);
	glVertex2f(x, h + y);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

GLuint GL_GenTexture()
{
	GLuint tex;

	glGenTextures(1, &tex);

	return tex;
}

void GL_Bind(int texnum)
{
	ORIG_GL_Bind(texnum); // TODO: implement
}

bool ValidateWRect(const wrect_t* prc)
{
	if (!prc)
		return false;

	if ((prc->left >= prc->right) || (prc->top >= prc->bottom))
		return false;

	return true;
}

bool IntersectWRect(const wrect_t* prc1, const wrect_t* prc2, wrect_t* prc)
{
	wrect_t rc;

	if (!prc)
		prc = &rc;

	prc->left = V_max(prc1->left, prc2->left);
	prc->right = V_min(prc1->right, prc2->right);

	if (prc->left < prc->right)
	{
		prc->top = V_max(prc1->top, prc2->top);
		prc->bottom = V_min(prc1->bottom, prc2->bottom);

		if (prc->top < prc->bottom)
			return true;
	}

	return false;
}

void AdjustSubRect(mspriteframe_t* pFrame, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom, int* pw, int* ph, const wrect_t* prcSubRect)
{
	wrect_t wrect;

	if (!ValidateWRect(prcSubRect))
		return;

	wrect.left = 0;
	wrect.top = 0;
	wrect.right = *pw;
	wrect.bottom = *ph;

	if (!IntersectWRect(prcSubRect, &wrect, &wrect))
		return;

	*pw = wrect.right - wrect.left;
	*ph = wrect.bottom - wrect.top;

#ifdef REGS_FIXES
	*pfLeft = (wrect.left) * 1.0 / pFrame->width;
	*pfRight = (wrect.right) * 1.0 / pFrame->width;

	*pfTop = (wrect.top) * 1.0 / pFrame->height;
	*pfBottom = (wrect.bottom) * 1.0 / pFrame->height;
#else
	*pfLeft = (wrect.left + 0.5) * 1.0 / pFrame->width;
	*pfRight = (wrect.right - 0.5) * 1.0 / pFrame->width;

	*pfTop = (wrect.top + 0.5) * 1.0 / pFrame->height;
	*pfBottom = (wrect.bottom - 0.5) * 1.0 / pFrame->height;
#endif
}

void Draw_Frame(mspriteframe_t* pFrame, int ix, int iy, const wrect_t* prcSubRect)
{
	float fLeft = 0.0;
	float fRight = 1.0;
	float fTop = 0.0;
	float fBottom = 1.0;

	int iWidth = pFrame->width;
	int iHeight = pFrame->height;

#ifdef REGS_FIXES
	float x = (float)ix;
	float y = (float)iy;
#else
	float x = (float)ix + 0.5;
	float y = (float)iy + 0.5;
#endif

	VGUI2_ResetCurrentTexture();

	if (giScissorTest)
	{
		glScissor(scissor_x, scissor_y, scissor_width, scissor_height);
		glEnable(GL_SCISSOR_TEST);
	}

	if (prcSubRect)
		AdjustSubRect(pFrame, &fLeft, &fRight, &fTop, &fBottom, &iWidth, &iHeight, prcSubRect);

	glDepthMask(GL_FALSE);

	GL_Bind(pFrame->gl_texturenum);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_QUADS);
	glTexCoord2f(fLeft, fTop);
	glVertex2f(x, y);
	glTexCoord2f(fRight, fTop);
	glVertex2f(iWidth + x, y);
	glTexCoord2f(fRight, fBottom);
	glVertex2f(iWidth + x, iHeight + y);
	glTexCoord2f(fLeft, fBottom);
	glVertex2f(x, iHeight + y);
	glEnd();

	glDepthMask(GL_TRUE);
	glDisable(GL_SCISSOR_TEST);
}

void Draw_SpriteFrame(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect)
{
	Draw_Frame(pFrame, x, y, prcSubRect);
}

void Draw_SpriteFrameHoles(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect)
{
	glEnable(GL_ALPHA_TEST);

	if (gl_spriteblend->value != 0.0)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	Draw_Frame(pFrame, x, y, prcSubRect);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
}

void Draw_SpriteFrameAdditive(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	Draw_Frame(pFrame, x, y, prcSubRect);
	glDisable(GL_BLEND);
}

void Draw_SpriteFrameGeneric(mspriteframe_t* pFrame, unsigned short* pPalette, int x, int y, const wrect_t* prcSubRect, int src, int dest, int width, int height)
{
	int w, h;

	w = pFrame->width;
	pFrame->width = width;

	h = pFrame->height;
	pFrame->height = height;

	glEnable(GL_BLEND);
	glBlendFunc(src, dest);
	Draw_Frame(pFrame, x, y, prcSubRect);
	glDisable(GL_BLEND);

	pFrame->width = w;
	pFrame->height = h;
}

void BoxFilter3x3(byte* out, byte* in, int w, int h, int x, int y)
{
	ORIG_BoxFilter3x3(out, in, w, h, x, y); // TODO: implement
}

void GL_Upload32(unsigned int* data, int width, int height, qboolean mipmap, int iType, int filter)
{
	ORIG_GL_Upload32(data, width, height, mipmap, iType, filter);
}

void GL_Upload16(unsigned char* data, int width, int height, qboolean mipmap, int iType, unsigned char* pPal, int filter)
{
	static unsigned trans[640 * 480];
	unsigned char* pb, *ppix;
	bool noalpha = true;
	int texturebytes = width * height;
	int p;

	if (texturebytes > sizeof(trans))
	{
		gEngfuncs.Con_Printf("Can't upload (%ix%i) texture, it's > 640*480 bytes\n", width, height);
		return;
	}

	if (iType != TEX_TYPE_LUM)
	{
		if (!pPal)
			return;

		for (int i = 0; i < 768; i++)
			pPal[i] = texgammatable[pPal[i]];
	}

	if (TEX_IS_ALPHA(iType))
	{
		if (iType == TEX_TYPE_ALPHA_GRADIENT)
		{
			for (int i = 0; i < texturebytes; i++)
			{
				p = data[i];
				pb = reinterpret_cast<byte*>(&trans[i]);

				pb[0] = pPal[765];
				pb[1] = pPal[766];
				pb[2] = pPal[767];
				pb[3] = p;

				noalpha = false;
			}
		}
		else if (iType == TEX_TYPE_RGBA)
		{
			for (int i = 0; i < texturebytes; i++)
			{
				p = data[i];
				pb = reinterpret_cast<byte*>(&trans[i]);

				pb[0] = pPal[p * 3 + 0];
				pb[1] = pPal[p * 3 + 1];
				pb[2] = pPal[p * 3 + 2];
				pb[3] = p;

				noalpha = false;
			}
		}
		else if (iType == TEX_TYPE_ALPHA)
		{
			for (int i = 0; i < texturebytes; i++)
			{
				p = data[i];
				pb = reinterpret_cast<byte*>(&trans[i]);

				if (p == 255)
				{
					pb[0] = pb[1] = pb[2] = pb[3] = NULL;
					noalpha = false;
				}
				else
				{
					pb[0] = pPal[p * 3 + 0];
					pb[1] = pPal[p * 3 + 1];
					pb[2] = pPal[p * 3 + 2];
					pb[3] = 255;
				}
			}
		}

		if (noalpha)
			iType = TEX_TYPE_NONE;
	}
	else if (iType == TEX_TYPE_NONE)
	{
		if (texturebytes & 3)
			gEngfuncs.Con_Printf("GL_Upload16: s&3\n"); // TODO: implement Sys_Error and replace Con_Printf with Sys_Error

		if (gl_dither->value != 0.0f)
		{
			for (int i = 0; i < texturebytes; i++)
			{
				p = data[i];
				pb = reinterpret_cast<byte*>(&trans[i]);
				ppix = &pPal[p * 3];

				pb[0] = ppix[0] |= (ppix[0] >> 6);
				pb[1] = ppix[1] |= (ppix[1] >> 6);
				pb[2] = ppix[2] |= (ppix[2] >> 6);
				pb[3] = 255;
			}
		}
		else
		{
			for (int i = 0; i < texturebytes; i++)
			{
				p = data[i];
				pb = reinterpret_cast<byte*>(&trans[i]);

				pb[0] = pPal[p * 3 + 0];
				pb[1] = pPal[p * 3 + 1];
				pb[2] = pPal[p * 3 + 2];
				pb[3] = 255;
			}
		}
	}
	else if (iType == TEX_TYPE_LUM)
		memcpy(trans, data, texturebytes);
	else
		gEngfuncs.Con_Printf("GL_Upload16: Bogus texture type!\n");

	GL_Upload32(trans, width, height, mipmap, iType, filter);
}

void GLDraw_Hook()
{
	gl_spriteblend = gEngfuncs.pfnGetCvarPointer("gl_spriteblend");
	gl_dither = gEngfuncs.pfnGetCvarPointer("gl_dither");

	Hook(Draw_String);
	Hook(GL_Bind);
	Hook(Draw_Frame);
	Hook(BoxFilter3x3);
	Hook(GL_Upload32);
	Hook(GL_Upload16);

	gEngfuncs.pfnFillRGBA = Draw_FillRGBA;
}