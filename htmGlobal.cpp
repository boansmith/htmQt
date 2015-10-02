#include "htmGlobal.h"

const float HtmGlobal::m_fPermConnected      = 0.2;
const int   HtmGlobal::m_nActiveThreshHold   = 80;
const int   HtmGlobal::m_nCellsPerCol        = 4;
const int   HtmGlobal::m_nWidthInput         = 20;
const int   HtmGlobal::m_nHeightInput        = 20;
const float HtmGlobal::m_fDeltaPermInc       = 0.01;
const float HtmGlobal::m_fDeltaPermDec       = 0.01;
const int   HtmGlobal::m_nWidthColumn        = 10;
const int   HtmGlobal::m_nHeightColumn       = 10;
const float HtmGlobal::m_fDesiredActiveRatio        = 0.2;


float HtmGlobal::boostFunc(int colActiveTimes, int minColActiveTimes)
{
    if (colActiveTimes >= minColActiveTimes)
    {
        return 1.0f;
    }
    else
    {
        return 1.0f + (minColActiveTimes-colActiveTimes)/2.0f;
    }
}
