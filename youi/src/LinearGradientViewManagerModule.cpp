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

glm::vec2 ValidatePosition(std::map<CYIString, float> positionProperty)
{
    glm::vec2 position{};

    position.x = positionProperty["x"];
    position.y = positionProperty["y"];

    bool positionValuesOk =
        position.x >= 0 &&
        position.x <= 1 &&
        position.y >= 0 &&
        position.y <= 1;
    
    YI_ASSERT(positionValuesOk, LOG_TAG, "Gradient x/y values must range between 0 and 1");
    return position;
}

CYIColor ValidateColor(std::map<CYIString, int32_t> &colorProperty)
{
    CYIColor color{};

    int32_t red = colorProperty["red"];
    int32_t green = colorProperty["green"];
    int32_t blue = colorProperty["blue"];
    int32_t alpha = colorProperty["alpha"];

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
    folly::dynamic props = folly::dynamic::object("start", "object")("end", "object")("startColor", "object")("endColor", "object");
    return folly::dynamic::merge(superProps, props);
}

void LinearGradientViewManagerModule::SetupProperties()
{
    IViewManager::SetupProperties();

    YI_RN_DEFINE_PROPERTY("start", [](ShadowLinearGradientView &self, std::map<CYIString, float> start) {
        self.GetSavedProps()->start = ValidatePosition(start);
    });

    YI_RN_DEFINE_PROPERTY("end", [](ShadowLinearGradientView &self, std::map<CYIString, float> end) {
        self.GetSavedProps()->end = ValidatePosition(end);
    });

    YI_RN_DEFINE_PROPERTY("startColor", [](ShadowLinearGradientView &self, std::map<CYIString, int32_t>  startColor) {
        self.GetSavedProps()->startColor = ValidateColor(startColor);
    });

    YI_RN_DEFINE_PROPERTY("endColor", [](ShadowLinearGradientView &self, std::map<CYIString, int32_t> endColor) {
       self.GetSavedProps()->endColor = ValidateColor(endColor);
    });
}
