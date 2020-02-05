#ifndef _LINEAR_GRADIENT_VIEW_PROPS_H
#define _LINEAR_GRADIENT_VIEW_PROPS_H

#include <youireact/JsEnum.h>
#include <youireact/props/ViewStylePropTypes.h>

namespace yi
{
namespace react
{

struct LinearGradientViewProps
{
    glm::vec2 start{};
    glm::vec2 end{};
    
    CYIColor startColor{};
    CYIColor endColor{};
};

} // namespace react

} // namespace yi

#endif // _LINEAR_GRADIENT_VIEW_PROPS_H
