#pragma once

#include <system/base.hpp>

namespace demo {

void initSystems();
void updateSystems();
BaseSystem* getSystem(const std::string&);

} // namespace demo