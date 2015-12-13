#ifndef HtmGlobal_H
#define HtmGlobal_H

class HtmGlobal
{
public:

    // 一个synapse被认定为 connected 时其permanence的最小值
    static const float    m_fPermConnected;

    // 学习时synapse的permanence的增量
    static const float    m_fDeltaPermInc;
    static const float    m_fDeltaPermDec;

    // 每个column中的cell的个数
    static const int      m_nCellsPerCol;

    // 当一个dendrite segment 被认定为active时的thresh，active的synapse的个数
    static const int      m_nActiveThreshHold;

    // the width and height of the input
    static const int      m_nWidthInput;
    static const int      m_nHeightInput;

    static const int      m_nWidthColumn;
    static const int      m_nHeightColumn;

    // 在所有 columns 当中，active 所占的比例
    static const float    m_fDesiredActiveRatio;

    static float boostFunc(int colActiveTimes, int minColActiveTimes);
};

#endif // HtmGlobal_H
