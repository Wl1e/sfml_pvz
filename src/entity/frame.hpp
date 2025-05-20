#pragma once

#include <defines.h>

namespace demo {

class FrameManager
{
public:
    ~FrameManager() = default;

    Frame getFrame() const
    {
        return m_frame;
    }
    void update()
    {
        ++m_frame;
    }

    static FrameManager& getInstance()
    {
        static FrameManager frameManager;
        return frameManager;
    }

private:
    FrameManager() = default;

private:
    Frame m_frame;
};

} // namespace demo