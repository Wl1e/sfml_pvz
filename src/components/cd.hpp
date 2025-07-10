#pragma once

namespace demo {

class CD
{
public:
    CD(int interval = 0) : m_interval(interval), m_count(0)
    {
    }
    void setCD(int interval)
    {
        m_interval = interval;
    }
    void update()
    {
        ++m_count;
        if(m_count >= m_interval) {
            m_valid = true;
            m_count = 0;
        }
    }
    void reset()
    {
        m_count = 0;
        m_valid = false;
    }

    bool valid() const
    {
        return m_valid;
    }

private:
    int m_interval;
    int m_count;
    bool m_valid;
};

} // namespace demo