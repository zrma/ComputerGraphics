// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <windowsx.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <dwrite.h>
#include <timeapi.h>
#include <string>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <gl/glut.h>
#include <gl/GLEXT.H>
#include <windows.h>
#include <math.h>

// 필요한 자료구조용 헤더
#include <list>
#include <array>

// For Debug - Memory Leak Check
#include <crtdbg.h>