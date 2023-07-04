// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h" // 윈도우 기본 용 헤더 추가
#include "DoubleBuffer.h" // 더블 버퍼링과 다른거의 연동을 위한 헤더 추가
#include "Sprite.h" // 스프라이트와 연동을 위한 추가
#include "BlipObj.h" // 돌고래 오브젝트 헤더
#include "Background.h" // 배경 오브젝트 헤더
#include "AngieObj.h" // 앙기 오브젝트 헤더
#include "MermaidObj.h" // 인어 오브젝터 헤더
#include "AObj.h" // 기주영 오브젝터 헤더
#include "GumboObj.h" // 검보 오브젝터 헤더
#include "NostraObj.h" // 노스트라다머스 헤더
#include "NimbusObj.h" // 님버스 오브젝터 헤더
#include "BalrogObj.h" // 발록 오브젝터 헤더
#include "AmpObj.h" // 엠프 오브젝트 헤더
#include "SummonAObj.h" // 기주영 소환하는 오브젝터 헤더
#include "GameLoop.h" // 게임 루프 헤더
#include "wndGameFramework001.h" // 윈도우 메인 생성을 위한 헤더
#include "MainProc.h" // 기본 대화 상자용 헤더
#include "AboutProc.h" // 정보 대화 상자용 헤더

#endif //PCH_H
