#ifndef _LINEAR_GRADIENT_VIEW_MANAGER_MODULE_H_
#define _LINEAR_GRADIENT_VIEW_MANAGER_MODULE_H_

#include <youireact/modules/components/AbstractComponentManagerModule.h>
#include <youireact/modules/components/IViewManager.h>

namespace yi
{
namespace react
{
class YI_RN_MODULE(LinearGradientViewManagerModule, AbstractComponentManagerModule), public IViewManager
{
public:
    YI_RN_EXPORT_NAME(LinearGradientViewManager);

    YI_RN_DEFINE_COMPONENT_MODULE();

protected:
    virtual void SetupProperties() override;
};
} // namespace react
} // namespace yi

#endif
