#ifndef _SHADOW_LINEAR_GRADIENT_VIEW_H_
#define _SHADOW_LINEAR_GRADIENT_VIEW_H_

#include "youireact/NativeModule.h"
#include "LinearGradientViewManagerModule.h"
#include "LinearGradientViewProps.h"
#include "youireact/nodes/ShadowView.h"

#include <scenetree/YiVectorCanvasNode.h>

namespace yi
{
namespace react
{
class ShadowLinearGradientView : public ShadowView
{
public:
    ShadowLinearGradientView();
    virtual ~ShadowLinearGradientView() final;

    YI_RN_EXPORT_NAME(ShadowLinearGradientView);
    YI_RN_DECLARE_MANAGER(LinearGradientViewManagerModule);

    virtual const CYIVectorCanvasNode *GetCounterpart() const override;
    virtual CYIVectorCanvasNode *GetCounterpart() override;

    virtual LinearGradientViewProps *GetSavedProps() override;
    
    virtual void ApplyProps(folly::dynamic properties) override;

private:
    virtual std::unique_ptr<CYISceneNode> CreateCounterpart(CYISceneManager *pSceneManager) override;

    virtual folly::dynamic GetDefaultProps() const final;

    virtual void OnLayoutApplied() final;
    virtual void DrawGradient() final;

    YI_TYPE_BASES(ShadowLinearGradientView, ShadowView);
};

} // namespace react
} // namespace yi

#endif // _SHADOW_LINEAR_GRADIENT_VIEW_H_
