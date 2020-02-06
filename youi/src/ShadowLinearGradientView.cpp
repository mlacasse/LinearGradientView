#include "ShadowLinearGradientView.h"

#include <youireact/NativeModuleRegistry.h>

using namespace yi::react;

#define LOG_TAG "ShadowLinearGradientView"

YI_TYPE_DEF_INST(ShadowLinearGradientView, ShadowView)

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

        YI_LOGD(LOG_TAG, "start x: %f, y: %f", props->start.x, props->start.y);
        YI_LOGD(LOG_TAG, "end x: %f, y: %f", props->end.x, props->end.y);

        YI_LOGD(LOG_TAG, "parentWidth: %f", parentWidth);
        YI_LOGD(LOG_TAG, "parentHeight: %f", parentHeight);

        YI_LOGD(LOG_TAG, "gradientStartPosition x: %f, y: %f", gradientStartPosition.x, gradientStartPosition.y);
        YI_LOGD(LOG_TAG, "gradientEndPosition x: %f, y: %f", gradientEndPosition.x, gradientEndPosition.y);

        YI_LOGD(LOG_TAG, "gradientStartColor r: %f, g: %f, b: %f, a: %f", startColor.GetRed(), startColor.GetGreen(), startColor.GetBlue(), startColor.GetAlpha());
        YI_LOGD(LOG_TAG, "gradientEndColor r: %f, g: %f, b: %f, a: %f", endColor.GetRed(), endColor.GetGreen(), endColor.GetBlue(), endColor.GetAlpha());

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
