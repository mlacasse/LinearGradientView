#ifndef _YOUIREACT_LINEAR_GRADIENT_VIEW_H_
#define _YOUIREACT_LINEAR_GRADIENT_VIEW_H_

#include "youireact/nodes/ShadowView.h"
#include "LinearGradientViewController.h"

#include <scenetree/YiVectorCanvasNode.h>

namespace yi
{
namespace react
{
class LinearGradientView : public ShadowView
{
public:
    LinearGradientView();

    virtual ~LinearGradientView() final;

    virtual bool OnInit() override;
    virtual void OnLayoutApplied() override;

    YI_RN_EXPORT_NAME(LinearGradientView);

    virtual folly::dynamic GetNativeProps() const override;
    virtual void ApplyProps(folly::dynamic properties) override;

    virtual const CYIVectorCanvasNode *GetCounterpart() const final;
    virtual CYIVectorCanvasNode *GetCounterpart() final;
    LinearGradientViewController &GetController();

private:
    virtual std::unique_ptr<CYISceneNode> CreateCounterpart(CYISceneManager *pSceneManager) final;
    virtual void ConfigureDefaultProperties() final;
    virtual void DrawGradient() final;

    LinearGradientViewController m_controller;

    YI_TYPE_BASES(LinearGradientView, ShadowView);
};

} // namespace react

} // namespace yi

#endif // _YOUIREACT_LINEAR_GRADIENT_H_
