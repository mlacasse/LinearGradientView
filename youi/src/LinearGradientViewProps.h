#ifndef _LINEAR_GRADIENT_VIEW_PROPS_H
#define _LINEAR_GRADIENT_VIEW_PROPS_H

#include <youireact/props/PropTypes.h>

namespace yi
{
namespace react
{

struct LinearGradientViewProps : public PropTypes
{
    glm::vec2 start{};
    glm::vec2 end{};
    
    CYIColor startColor{};
    CYIColor endColor{};
};

} // namespace react

} // namespace yi

#endif // _LINEAR_GRADIENT_VIEW_PROPS_H
