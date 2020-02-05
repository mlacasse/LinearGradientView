#include "LinearGradientView.h"

#include "utility/InitFromValue.h"
#include "utility/FollyDynamicConverter.h"
#include <framework/YiFramework.h>

using namespace yi::react;

#define TAG "LinearGradientView"

YI_TYPE_DEF_INST(LinearGradientView, ShadowView)


LinearGradientView::LinearGradientView()
{
}

LinearGradientView::~LinearGradientView() = default;

void LinearGradientView::ConfigureDefaultProperties()
{
    // Position
    folly::dynamic start = folly::dynamic::object;
    start["x"] = 0;
    start["y"] = 0;

    folly::dynamic end = folly::dynamic::object;
    end["x"] = 1;
    end["y"] = 1;

    //Colors
    folly::dynamic startColor = folly::dynamic::object;
    startColor["red"] = 0.0f;
    startColor["green"] = 0.0f;
    startColor["blue"] = 0.0f;
    startColor["alpha"] = 1.0f;

    folly::dynamic endColor = folly::dynamic::object;
    endColor["red"] = 100.0f;
    endColor["green"] = 100.0f;
    endColor["blue"] = 100.0f;
    endColor["alpha"] = 0.0f;

    //Default Props
    folly::dynamic defaultProps = folly::dynamic::object;
    defaultProps["start"] = start;
    defaultProps["end"] = end;
    defaultProps["startColor"] = startColor;
    defaultProps["endColor"] = endColor;

    ApplyProps(std::move(defaultProps));
}

bool LinearGradientView::OnInit()
{
    m_controller.SetCounterpart(GetCounterpart());
    m_controller.SetReactComponent(this);
    ConfigureDefaultProperties();
    return true;
}

void LinearGradientView::OnLayoutApplied()
{
    ShadowView::OnLayoutApplied();
    DrawGradient();
}

void LinearGradientView::DrawGradient()
{
    auto *pVectorCanvasNode = GetCounterpart();

    if (pVectorCanvasNode && pVectorCanvasNode->GetParent())
    {
        auto props = m_controller.GetProps();
    
        auto parentWidth = pVectorCanvasNode->GetParent()->GetSize().x;
        auto parentHeight = pVectorCanvasNode->GetParent()->GetSize().y;

        auto gradientStartPosition = glm::vec2(parentWidth * props.start.x , parentHeight * props.start.y);
        auto gradientEndPosition = glm::vec2(parentWidth * props.end.x , parentHeight * props.end.y);
        // auto gradientEndPosition = glm::vec2(parentWidth,parentHeight) * props.end;

        CYIColor startColor = props.startColor;
        CYIColor endColor = props.endColor;

        YI_LOGD(TAG, "start x: %s, y: %s", CYIString::FromValue(props.start.x).GetData(), CYIString::FromValue(props.start.y).GetData());
        YI_LOGD(TAG, "end x: %s, y: %s", CYIString::FromValue(props.end.x).GetData(), CYIString::FromValue(props.end.y).GetData());

        YI_LOGD(TAG, "parentWidth: %s", CYIString::FromValue(parentWidth).GetData());
        YI_LOGD(TAG, "parentHeight: %s", CYIString::FromValue(parentHeight).GetData());

        YI_LOGD(TAG, "gradientStartPosition x: %s, y: %s", CYIString::FromValue(gradientStartPosition.x).GetData(), CYIString::FromValue(gradientStartPosition.y).GetData());
        YI_LOGD(TAG, "gradientEndPosition x: %s, y: %s", CYIString::FromValue(gradientEndPosition.x).GetData(), CYIString::FromValue(gradientEndPosition.y).GetData());

        YI_LOGD(
            TAG, 
            "gradientStartColor r: %s, g: %s, b: %s, a: %s", 
            CYIString::FromValue(startColor.GetRed()).GetData(), 
            CYIString::FromValue(startColor.GetGreen()).GetData(),
            CYIString::FromValue(startColor.GetBlue()).GetData(), 
            CYIString::FromValue(startColor.GetAlpha()).GetData() 
        );

        YI_LOGD(
            TAG, 
            "gradientEndColor r: %s, g: %s, b: %s, a: %s", 
            CYIString::FromValue(endColor.GetRed()).GetData(), 
            CYIString::FromValue(endColor.GetGreen()).GetData(),
            CYIString::FromValue(endColor.GetBlue()).GetData(), 
            CYIString::FromValue(endColor.GetAlpha()).GetData() 
        );

        pVectorCanvasNode->PopGroup();
        pVectorCanvasNode->ClearCommandQueue();
        pVectorCanvasNode->PushBeginPath();
        pVectorCanvasNode->PushRectangle(glm::vec2(0,0), glm::vec2(parentWidth,parentHeight));
        pVectorCanvasNode->PushLinearGradientFill(startColor, endColor, gradientStartPosition, gradientEndPosition);
    }
}

std::unique_ptr<CYISceneNode> LinearGradientView::CreateCounterpart(CYISceneManager *pSceneManager)
{
    std::unique_ptr<CYIVectorCanvasNode> pVectorCanvasNode(new CYIVectorCanvasNode());
    pVectorCanvasNode->SetSceneManager(pSceneManager);
    pVectorCanvasNode->Init();
    return std::unique_ptr<CYISceneNode>{pVectorCanvasNode.release()};
}

const CYIVectorCanvasNode *LinearGradientView::GetCounterpart() const
{
    return static_cast<const CYIVectorCanvasNode *>(ShadowView::GetCounterpart());
}

CYIVectorCanvasNode *LinearGradientView::GetCounterpart()
{
    return static_cast<CYIVectorCanvasNode *>(ShadowView::GetCounterpart());
}

folly::dynamic LinearGradientView::GetNativeProps() const
{
    return folly::dynamic::object("start", "object")("end", "object")("startColor", "object")("endColor", "object")("style", "object");
}

void LinearGradientView::ApplyProps(folly::dynamic properties)
{
    m_controller.ApplyProps(properties);
    ShadowView::ApplyProps(std::move(properties));
    DrawGradient();
}

LinearGradientViewController &LinearGradientView::GetController()
{
    return m_controller;
}
