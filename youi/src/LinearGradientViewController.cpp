#include "LinearGradientViewController.h"
#include "LinearGradientViewProps.h"

#include <scenetree/YiVectorCanvasNode.h>

#define TAG "LinearGradientViewController"

using namespace yi::react;

LinearGradientViewController::LinearGradientViewController() = default;

LinearGradientViewController::~LinearGradientViewController() = default;

glm::vec2 LinearGradientViewController::ValidatePosition(const folly::dynamic &positionProperty)
{
    glm::vec2 position{};

    position.x = *ConvertDynamic<float>(positionProperty["x"]);
    position.y = *ConvertDynamic<float>(positionProperty["y"]);

    bool positionValuesOk = 
        position.x >= 0 && 
        position.x <= 1 &&
        position.y >= 0 &&
        position.y <= 1;
    
    YI_ASSERT(positionValuesOk, TAG, "Gradient x/y values must range between 0 and 1");
    return position;
}

CYIColor LinearGradientViewController::ValidateColor(const folly::dynamic &colorProperty)
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

    YI_ASSERT(allColorsOk, TAG, "Color rgba values must range between 0 and 255");

    color = CYIColor::FromRGBInteger(red, green, blue, alpha);

    return color;
}

void LinearGradientViewController::ApplyProps(const folly::dynamic &properties)
{

    auto startPos = properties.find("start");
    if(startPos != properties.items().end()){
        m_props.start = ValidatePosition(properties["start"]);
    }

    auto endPos = properties.find("end");
    if(endPos != properties.items().end()){
        m_props.end = ValidatePosition(properties["end"]);
    }

    auto startColorPos = properties.find("startColor");
    if(startColorPos != properties.items().end()){
        m_props.startColor = ValidateColor(properties["startColor"]);
    }

    auto endColorPos = properties.find("endColor");
    if(endColorPos != properties.items().end()){
        m_props.endColor = ValidateColor(properties["endColor"]);
    }
}

const LinearGradientViewProps &LinearGradientViewController::GetProps() const
{   
    return m_props;
}
