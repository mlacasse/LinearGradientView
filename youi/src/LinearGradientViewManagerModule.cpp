#include "LinearGradientViewManagerModule.h"
#include "ShadowLinearGradientView.h"

#include <youireact/NativeModuleRegistry.h>

using namespace yi::react;

#define LOG_TAG "LinearGradientViewManagerModule"

YI_RN_INSTANTIATE_MODULE(LinearGradientViewManagerModule, AbstractComponentManagerModule);
YI_RN_REGISTER_MODULE(LinearGradientViewManagerModule);

YI_RN_OVERRIDE_OnInit(LinearGradientViewManagerModule);
YI_RN_OVERRIDE_OnLayoutApplied(LinearGradientViewManagerModule);
YI_RN_OVERRIDE_ApplyProps(LinearGradientViewManagerModule);
YI_RN_OVERRIDE_DismantleCounterpart(LinearGradientViewManagerModule);
YI_RN_OVERRIDE_ConfigureCounterpart(LinearGradientViewManagerModule);

glm::vec2 ValidatePosition(const folly::dynamic &positionProperty)
{
    glm::vec2 position{};

    position.x = *ConvertDynamic<float>(positionProperty["x"]);
    position.y = *ConvertDynamic<float>(positionProperty["y"]);

    bool positionValuesOk =
        position.x >= 0 &&
        position.x <= 1 &&
        position.y >= 0 &&
        position.y <= 1;
    
    YI_ASSERT(positionValuesOk, LOG_TAG, "Gradient x/y values must range between 0 and 1");
    return position;
}

CYIColor ValidateColor(const folly::dynamic &colorProperty)
{
    CYIColor color{};

    int32_t red = *ConvertDynamic<int32_t>(colorProperty["red"]);
    int32_t green = *ConvertDynamic<int32_t>(colorProperty["green"]);
    int32_t blue = *ConvertDynamic<int32_t>(colorProperty["blue"]);
    int32_t alpha = *ConvertDynamic<int32_t>(colorProperty["alpha"]);

    bool redOk = red >= 0 && red <= 255;
    bool greenOk = green >= 0 && green <= 255;
    bool blueOk = blue >= 0 && blue <= 255;
    bool alphaOk = alpha >= 0 && alpha <= 255;

    bool allColorsOk = redOk && greenOk && blueOk && alphaOk;

    YI_ASSERT(allColorsOk, LOG_TAG, "Color rgba values must range between 0 and 255");

    color = CYIColor::FromRGBInteger(red, green, blue, alpha);

    return color;
}

folly::dynamic LinearGradientViewManagerModule::GetNativeProps()
{
    folly::dynamic superProps = IViewManager::GetNativeProps();
    folly::dynamic props = folly::dynamic::object("start", "object")("end", "object")("startColor", "object")("endColor", "object")("style", "object");
    return folly::dynamic::merge(superProps, props);
}

void LinearGradientViewManagerModule::SetupProperties()
{
    IViewManager::SetupProperties();

    YI_RN_DEFINE_PROPERTY("start", [](ShadowLinearGradientView &self, folly::dynamic start) {
        self.GetSavedProps()->start = ValidatePosition(start);
    });

    YI_RN_DEFINE_PROPERTY("end", [](ShadowLinearGradientView &self, folly::dynamic end) {
        self.GetSavedProps()->end = ValidatePosition(end);
    });

    YI_RN_DEFINE_PROPERTY("startColor", [](ShadowLinearGradientView &self, folly::dynamic startColor) {
        self.GetSavedProps()->startColor = ValidateColor(startColor);
    });

    YI_RN_DEFINE_PROPERTY("endColor", [](ShadowLinearGradientView &self, folly::dynamic endColor) {
        self.GetSavedProps()->endColor = ValidateColor(endColor);
    });
}

void LinearGradientViewManagerModule::ConfigureCounterpartPriv(ReactComponent &inst)
{
    // available to connect to signals
    YI_UNUSED(inst);
}

void LinearGradientViewManagerModule::DismantleCounterpartPriv(ReactComponent &inst)
{
    // available to disconnect to signals
    YI_UNUSED(inst);
}
