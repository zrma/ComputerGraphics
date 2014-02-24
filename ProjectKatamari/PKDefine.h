#pragma once

//이미지 도큐먼트 헤더 형식 지정 관련 정의
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

//define for memroy leak check
#ifdef _DEBUG
#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif


#define SCREEN_SIZE_X	1120
#define SCREEN_SIZE_Y	680
#define SCREEN_SIZE_Z	1000

#define MAX_INPUT_KEY	256

#define MATRIX_3D_ROW	4
#define MATRIX_3D_COL	4
#define DIMENSION_3D	4

#define	MAX_LIGHT_COUNT	6

#define PI				3.141592653589
#define DTOR			(PI / 180.0f)