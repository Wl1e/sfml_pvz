#pragma once

#include <string_view>

#include <base/tools.hpp>
#include <entity/tool/tool.hpp>

namespace demo {

class Background;
class PlantCreator;

// 目前不支持一个实体多个相同类型的组件，所以卡槽背景塞不进PlantCreator
// 暂时新增Card类解决问题
// 这个缺陷也导致了类似打矿工的那个植物（忘记名字了）也难实现

// TODO: 将鼠标点击调整为事件
class Card : public Tool
{
public:
    Card(std::string_view, const PositionType&, const SizeType&);
    ~Card() = default;

    // 这里导致需要entity的update改为virtual，越来越怪了
    void update() override;
    void use(const sf::Vector2i&) override;

private:
    void _initComps(
        std::string_view, const PositionType&, const SizeType&
    );
    void _initEvents();

    // 这是什么邪门歪道??? Σ(°Д°;
    const PlantCreator* operator->() const
    {
        return m_plantCreator.get();
    }

private:
    std::unique_ptr<Background> m_background;
    std::unique_ptr<PlantCreator> m_plantCreator;
};

} // namespace demo