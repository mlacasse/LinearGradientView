#include "ShadowLinearGradientView.h"

#include <youireact/NativeModuleRegistry.h>

using namespace yi::react;

#define LOG_TAG "ShadowLinearGradientView"

YI_TYPE_DEF(ShadowLinearGradientView, ShadowView)

YI_RN_REGISTER_VIEW_MODULE(ShadowLinearGradientView);

ShadowLinearGradientView::ShadowLinearGradientView()
{
    m_savedProps.reset(new LinearGradientViewProps());
}

ShadowLinearGradientView::~ShadowLinearGradientView() = default;

LinearGradientViewProps *ShadowLinearGradientView::GetSavedProps()
{
    return static_cast<LinearGradientViewProps *>(ShadowView::GetSavedProps());
}

std::unique_ptr<CYISceneNode> ShadowLinearGradientView::CreateCounterpart(CYISceneManager *pSceneManager)
{
    std::unique_ptr<CYIVectorCanvasNode> pVectorCanvasNode(new CYIVectorCanvasNode());

    pVectorCanvasNode->SetSceneManager(pSceneManager);
    pVectorCanvasNode->Init();

    return std::unique_ptr<CYISceneNode>{pVectorCanvasNode.release()};
}

const CYIVectorCanvasNode *ShadowLinearGradientView::GetCounterpart() const
{
    return static_cast<const CYIVectorCanvasNode *>(ShadowView::GetCounterpart());
}

CYIVectorCanvasNode *ShadowLinearGradientView::GetCounterpart()
{
    return static_cast<CYIVectorCanvasNode *>(ShadowView::GetCounterpart());
}

folly::dynamic ShadowLinearGradientView::GetDefaultProps() const
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

    return defaultProps;
}

void ShadowLinearGradientView::OnLayoutApplied()
{
    DrawGradient();
}

void ShadowLinearGradientView::DrawGradient()
{
    auto *pVectorCanvasNode = GetCounterpart();

    if (pVectorCanvasNode && pVectorCanvasNode->GetParent())
    {
        auto props = GetSavedProps();
    
        auto parentWidth = pVectorCanvasNode->GetParent()->GetSize().x;
        auto parentHeight = pVectorCanvasNode->GetParent()->GetSize().y;

        auto gradientStartPosition = glm::vec2(parentWidth * props->start.x , parentHeight * props->start.y);
        auto gradientEndPosition = glm::vec2(parentWidth * props->end.x , parentHeight * props->end.y);

        CYIColor startColor = props->startColor;
        CYIColor endColor = props->endColor;

        YI_LOGD(LOG_TAG, "start x: %s, y: %s", CYIString::FromValue(props->start.x).GetData(), CYIString::FromValue(props->start.y).GetData());
        YI_LOGD(LOG_TAG, "end x: %s, y: %s", CYIString::FromValue(props->end.x).GetData(), CYIString::FromValue(props->end.y).GetData());

        YI_LOGD(LOG_TAG, "parentWidth: %s", CYIString::FromValue(parentWidth).GetData());
        YI_LOGD(LOG_TAG, "parentHeight: %s", CYIString::FromValue(parentHeight).GetData());

        YI_LOGD(LOG_TAG, "gradientStartPosition x: %s, y: %s", CYIString::FromValue(gradientStartPosition.x).GetData(), CYIString::FromValue(gradientStartPosition.y).GetData());
        YI_LOGD(LOG_TAG, "gradientEndPosition x: %s, y: %s", CYIString::FromValue(gradientEndPosition.x).GetData(), CYIString::FromValue(gradientEndPosition.y).GetData());

        YI_LOGD(
            LOG_TAG,
            "gradientStartColor r: %s, g: %s, b: %s, a: %s",
            CYIString::FromValue(startColor.GetRed()).GetData(),
            CYIString::FromValue(startColor.GetGreen()).GetData(),
            CYIString::FromValue(startColor.GetBlue()).GetData(),
            CYIString::FromValue(startColor.GetAlpha()).GetData()
        );

        YI_LOGD(
            LOG_TAG,
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

void ShadowLinearGradientView::ApplyProps(folly::dynamic properties)
{
    ShadowView::ApplyProps(std::move(properties));
    DrawGradient();
}
