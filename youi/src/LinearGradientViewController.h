#ifndef _LINEAR_GRADIENT_VIEW_CONTROLLER_H_
#define _LINEAR_GRADIENT_VIEW_CONTROLLER_H_

#include "LinearGradientViewProps.h"
#include "youireact/props/ShadowController.h"

class CYIVectorCanvasNode;

namespace yi
{
namespace react
{
enum class LinearGradientViewDirectEvents
{
    // Add more here
    ENUM_MAX
};

class LinearGradientViewController;

extern template class DecoratorMap<LinearGradientViewController>;

class LinearGradientViewController : public ShadowController<CYIVectorCanvasNode, LinearGradientViewDirectEvents>
{
public:
    LinearGradientViewController();
    YI_DEFAULT_MOVE_NO_COPY(LinearGradientViewController);
    virtual ~LinearGradientViewController() final;

    void ApplyProps(const folly::dynamic &properties);

    const LinearGradientViewProps &GetProps() const;

private:
    glm::vec2 ValidatePosition(const folly::dynamic &positionProperty);
    CYIColor ValidateColor(const folly::dynamic &colorProperty);
    LinearGradientViewProps m_props;
};

} // namespace react
} // namespace yi

#endif
