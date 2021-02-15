#ifndef HHTOUCHPOINT_H
#define HHTOUCHPOINT_H

enum SpecifiedPenType{
    SpecifiedPenType_THICK = 0,
    SpecifiedPenType_THIN = 1,
    SpecifiedPenType_ERASER = 2
};

class HHTouchPoint
{
public:
    HHTouchPoint() {
        m_extraData = nullptr;
        m_ptx = 0;
        m_pty = 0;
        m_kuan = 0;
        m_gao = 0;
        m_time = 0;
    }

public:
    float       m_ptx;
    float       m_pty;
    float       m_kuan;
    float       m_gao;
    int         m_id;
    int         m_flags;
    int         m_time;
    void        *m_extraData;//QEvent
};

#endif // HHTOUCHPOINT_H
