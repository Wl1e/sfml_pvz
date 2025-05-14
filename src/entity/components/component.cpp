#include <functional>

#include <entity/components/component.hpp>

using namespace std;
using namespace demo;

namespace demo {

// template<typename... Args>
// using Creator = function<CompPtr(Args&&...)>;
// class ComponentFactory
// {
// public:
//     void registerComponent(CompType type, Creator creator)
//     {
//         m_creators[type] = move(creator);
//     }

//     CompPtr create(CompType type)
//     {
//         return m_creators.at(type)();
//     }

// private:
//     unordered_map<CompType, Creator> m_creators;
// };

// static ComponentFactory factory;

// template<class T, typename... Args>
// void registerComponent(CompType type)
// {
//     factory.registerComponent(type, []() {
//         return make_unique<Component>()
//     });
// }

// CompPtr createComponent(CompType type)
// {
// }

} // namespace demo