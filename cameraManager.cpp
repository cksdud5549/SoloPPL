#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}

// 초기 세팅, _L, _T가 카메라의 LEFT, TOP
void cameraManager::setConfig(float L, float T, float width, float height, float minL, float minT, float maxL, float maxT)
{
	_L = L;
	_T = T;
	_width = width;
	_height = height;
	_minL = minL;
	_minT = minT;
	_maxL = maxL;
	_maxT = maxT;

	_x = _L + (_width / 2);
	_y = _T + (_height / 2);
	_minX = _minL + (_width / 2);
	_minY = _minT + (_height / 2);
	_maxX = _maxL + (_width / 2);
	_maxY = _maxT + (_height / 2);
}

void cameraManager::setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_minX = minX;
	_minY = minY;
	_maxX = maxX;
	_maxY = maxY;

	_L = _x - (width / 2);
	_T = _y - (height / 2);
	_minL = _minX - (width / 2);
	_minT = _minY - (height / 2);
	_maxL = _maxX - (width / 2);
	_maxT = _minY - (height / 2);
}

float cameraManager::getL()
{
	return _L;
}

float cameraManager::getT()
{
	return _T;
}

float cameraManager::getX()
{
	return _x;
}

float cameraManager::getY()
{
	return _y;
}

void cameraManager::setL(float newL)
{
	newL = min(_maxL, newL);
	newL = max(_minL, newL);
	_L = floor(newL);
	_x = _L + (_width / 2);
}

void cameraManager::setT(float newT)
{
	newT = min(_maxT, newT);
	newT = max(_minT, newT);
	_T = floor(newT);
	_y = _T + (_height / 2);
}

// 카메라의 기준점 X을 정함
void cameraManager::setX(float newX)
{
	newX = min(_maxX, newX);
	newX = max(_minX, newX);
	_x = floor(newX);
	_L = _x - (_width / 2);
}

// 카메라의 기준점 Y을 정함
void cameraManager::setY(float newY)
{
	newY = min(_maxY, newY);
	newY = max(_minY, newY);
	_y = floor(newY);
	_T = _y - (_height / 2);
}

// 카메라의 기준점을 이동시킴
void cameraManager::movePivot(float offsetX, float offsetY)
{
	setL(_L + offsetX);
	setT(_T + offsetY);
	setX(_x + offsetX);
	setY(_y + offsetY);
}

// 카메라의 기준점을 기준으로 상대좌표 X값을 구함
float cameraManager::getRelativeX(float x)
{
	float newX = x - _L;
	return newX;
}

// 카메라의 기준점을 기준으로 상대좌표 Y값을 구함
float cameraManager::getRelativeY(float y)
{
	float newY = y - _T;
	return  newY;
}

// 사각형 그리기 MYRECT 사용
void cameraManager::rectangle(HDC hdc, TTYONE_UTIL::MYRECT mrec)
{
	RECT rect = { getRelativeX(mrec.left), getRelativeY(mrec.top), getRelativeX(mrec.right), getRelativeY(mrec.bottom) };
	Rectangle(hdc, rect);
}

// 동그라미 그리기 MYRECT 사용
void cameraManager::ellipse(HDC hdc, TTYONE_UTIL::MYRECT mrec)
{
	RECT rect = { getRelativeX(mrec.left), getRelativeY(mrec.top), getRelativeX(mrec.right), getRelativeY(mrec.bottom) };
	Ellipse(hdc, rect);
}

void cameraManager::render(HDC hdc, image * img)
{
	if (img) img->render(hdc, _x, _y);
}

void cameraManager::render(HDC hdc, image * img, float destX, float destY)
{
	float newX = getRelativeX(destX);
	float newY = getRelativeY(destY);
	if (img) img->render(hdc, newX, newY);
}

void cameraManager::render(HDC hdc, image * img, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	float newX = getRelativeX(destX);
	float newY = getRelativeY(destY);
	if (img) img->render(hdc, newX, newY, sourX, sourY, sourWidth, sourHeight);
}

void cameraManager::frameRender(HDC hdc, image * img, float destX, float destY)
{
	float newX = getRelativeX(destX);
	float newY = getRelativeY(destY);
	if (img) img->frameRender(hdc, newX, newY);
}

void cameraManager::frameRender(HDC hdc, image * img, float destX, float destY, int frameX, int frameY)
{
	float newX = getRelativeX(destX);
	float newY = getRelativeY(destY);
	if (img) img->frameRender(hdc, newX, newY, frameX, frameY);
}

void cameraManager::aniRender(HDC hdc, int destX, int destY, image * img ,animation * ani)
{
	float newX = getRelativeX(destX);
	float newY = getRelativeY(destY);
	if (img) img->aniRender(hdc, newX, newY, ani);
}

void cameraManager::alphaFrameRender(HDC hdc, int destX, int destY,  int currentFrameX, int currentFrameY, image * img, BYTE alpha)
{
	float newX = getRelativeX(destX);
	float newY = getRelativeY(destY);

	img->_imageInfo->currentFrameX = currentFrameX;
	img->_imageInfo->currentFrameY = currentFrameY;

	img->_blendFunc.SourceConstantAlpha = alpha;
	
	if (img->_trans)
	{
		BitBlt(img->_blendImage->hMemDC,  // origin DC
			0, // origin x
			0, // origin y
			img->_imageInfo->frameWidth, // origin width
			img->_imageInfo->frameHeight, // origin height
			hdc, // source DC
			newX, // source x
			newY,  // source y
			SRCCOPY);
		// 블렌드용 DC에 기존 DC의 그림 복사

		GdiTransparentBlt(
			img->_blendImage->hMemDC,					// origin DC
			0,					// origin X
			0,					// origin Y
			img->_imageInfo->frameWidth,	// origin width
			img->_imageInfo->frameHeight,// origin height
			img->_imageInfo->hMemDC,		// source DC
			img->_imageInfo->currentFrameX * img->_imageInfo->frameWidth,  // source x
			img->_imageInfo->currentFrameY *img->_imageInfo->frameHeight, // source y
			img->_imageInfo->frameWidth,								// source width
			img->_imageInfo->frameHeight,							// source height
			img->_transColor);			// transparent RGB
		// 블렌드용 DC에 이미지 그림(transparent RGB 제외)

		AlphaBlend(hdc, // origin DC
			newX,  // origin x
			newY, // origin y
			img->_imageInfo->frameWidth, // origin width
			img->_imageInfo->frameHeight, // origin height
			img->_blendImage->hMemDC,  // source DC
			0,  // source x
			0,  // source y
			img->_imageInfo->frameWidth, // source width
			img->_imageInfo->frameHeight, // source height
			img->_blendFunc); // blend function
	}
	else
	{
		AlphaBlend(hdc, newX, newY,
			img->_imageInfo->frameWidth, // origin width
			img->_imageInfo->frameHeight, // origin height
			img->_blendImage->hMemDC,
			img->_imageInfo->currentFrameX * img->_imageInfo->frameWidth,  // source x
			img->_imageInfo->currentFrameY * img->_imageInfo->frameHeight,  // source y
			img->_imageInfo->frameWidth, // source width
			img->_imageInfo->frameHeight, // source height
			img->_blendFunc);
	}
}

void cameraManager::zoom(HDC hdc, float ratio)
{
	if (ratio == 1) return;

	float newWidth = (float)_width / ratio;
	float newHeight = (float)_height / ratio;

	float zoomL = WINSIZEX / 2 - (newWidth / 2);
	float zoomT = WINSIZEY / 2 - (newHeight / 2);

	StretchBlt(hdc, 0, 0, _width, _height,
		hdc, zoomL, zoomT, newWidth, newHeight,
		SRCCOPY);

	// 위 과정을 통한 Zoom 구현
}
