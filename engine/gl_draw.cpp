#include "glquake.h"

_GL_Bind ORIG_GL_Bind = NULL;
_Draw_Frame ORIG_Draw_Frame = NULL;

static int scissor_x = 0, scissor_y = 0, scissor_width = 0, scissor_height = 0;
static qboolean giScissorTest = false;

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

void GLDraw_Hook()
{
	Hook(GL_Bind);
	Hook(Draw_Frame);

	gEngfuncs.pfnFillRGBA = Draw_FillRGBA;
}