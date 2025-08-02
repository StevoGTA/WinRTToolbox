//----------------------------------------------------------------------------------------------------------------------
//	CWin2DRenderer.cpp			©2025 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#include "CWin2DRenderer.h"

#undef Delete

#include "winrt\Microsoft.Graphics.Canvas.h"
#include "winrt\Microsoft.Graphics.Canvas.Brushes.h"
#include "winrt\Microsoft.Graphics.Canvas.Geometry.h"
#include "winrt\Microsoft.Graphics.Canvas.Text.h"
#include "winrt\Windows.UI.h"

#define Delete(x)	{ delete x; x = nil; }

using namespace winrt::Microsoft::Graphics::Canvas;

using CanvasArcSize = Geometry::CanvasArcSize;
using CanvasGradientStop = Brushes::CanvasGradientStop;
using CanvasLinearGradientBrush = Brushes::CanvasLinearGradientBrush;
using CanvasGeometry = Geometry::CanvasGeometry;
using CanvasHorizontalAlignment = Text::CanvasHorizontalAlignment;
using CanvasPathBuilder = Geometry::CanvasPathBuilder;
using CanvasSweepDirection = Geometry::CanvasSweepDirection;
using CanvasTextFormat = Text::CanvasTextFormat;
using CanvasTextLayout = Text::CanvasTextLayout;
using CanvasVerticalAlignment = Text::CanvasVerticalAlignment;
using Color = winrt::Windows::UI::Color;
using ColorHelper = winrt::Windows::UI::ColorHelper;
using Colors = winrt::Windows::UI::Colors;

//----------------------------------------------------------------------------------------------------------------------
// MARK: Local Data

struct S2DPathIterateInfo {
			CanvasPathBuilder&		mCanvasPathBuilder;
	const	S2DAffineTransformF32&	mAffineTransform;
};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: - CWin2DRenderer::Internals

class CWin2DRenderer::Internals {
	public:
						Internals(const CanvasDrawingSession& canvasDrawingSession) :
							mCanvasDrawingSession(canvasDrawingSession),
									mFillColor(Colors::Black()), mStrokeColor(Colors::Black())
							{}

		static	void	pathSegmentMoveTo32(const S2DPointF32& point, S2DPathIterateInfo* pathIterateInfo)
							{
								// Setup
								S2DPointF32	pointTransformed =
													S2DPointF32(point)
															.applyTransform(pathIterateInfo->mAffineTransform);

								// Begin figure
								pathIterateInfo->mCanvasPathBuilder.BeginFigure(
										{pointTransformed.mX, pointTransformed.mY});
							}
		static	void	pathSegmentLineTo32(const S2DPointF32& point, S2DPathIterateInfo* pathIterateInfo)
							{
								// Setup
								S2DPointF32	pointTransformed =
													S2DPointF32(point)
															.applyTransform(pathIterateInfo->mAffineTransform);

								// Add line
								pathIterateInfo->mCanvasPathBuilder.AddLine({pointTransformed.mX, pointTransformed.mY});
							}
		static	void	pathSegmentQuadCurveTo32(const S2DPointF32& controlPoint, const S2DPointF32& point,
								S2DPathIterateInfo* pathIterateInfo)
							{
								// Setup
								S2DPointF32	controlPointTransformed =
													S2DPointF32(controlPoint)
															.applyTransform(pathIterateInfo->mAffineTransform);
								S2DPointF32	pointTransformed =
													S2DPointF32(point)
															.applyTransform(pathIterateInfo->mAffineTransform);

								// Add quadratic curve
								pathIterateInfo->mCanvasPathBuilder.AddQuadraticBezier(
										{controlPointTransformed.mX, controlPointTransformed.mY},
										{pointTransformed.mX, pointTransformed.mY});
							}
		static	void	pathSegmentCubicCurveTo32(const S2DPointF32& controlPoint1, const S2DPointF32& controlPoint2,
								const S2DPointF32& point, S2DPathIterateInfo* pathIterateInfo)
							{
								// Setup
								S2DPointF32	controlPoint1Transformed =
													S2DPointF32(controlPoint1)
															.applyTransform(pathIterateInfo->mAffineTransform);
								S2DPointF32	controlPoint2Transformed =
													S2DPointF32(controlPoint2)
															.applyTransform(pathIterateInfo->mAffineTransform);
								S2DPointF32	pointTransformed =
													S2DPointF32(point)
															.applyTransform(pathIterateInfo->mAffineTransform);

								// Add cubic bezier curve
								pathIterateInfo->mCanvasPathBuilder.AddCubicBezier(
										{controlPoint1Transformed.mX, controlPoint1Transformed.mY},
										{controlPoint2Transformed.mX, controlPoint2Transformed.mY},
										{pointTransformed.mX, pointTransformed.mY});

							}
		static	void	pathSegmentArcTo32(Float32 radiusX, Float32 radiusY, Float32 rotationAngleRadians,
								bool useLargerArc, bool isClockwise, const S2DPointF32& point,
								S2DPathIterateInfo* pathIterateInfo)
							{
								// Setup
								S2DPointF32	pointTransformed =
													S2DPointF32(point)
															.applyTransform(pathIterateInfo->mAffineTransform);

								// Add arc
								pathIterateInfo->mCanvasPathBuilder.AddArc(
										{pointTransformed.mX, pointTransformed.mY}, radiusX, radiusY,
										rotationAngleRadians,
										isClockwise ?
												CanvasSweepDirection::Clockwise :
												CanvasSweepDirection::CounterClockwise,
										useLargerArc ? CanvasArcSize::Large : CanvasArcSize::Small);
							}

		CanvasDrawingSession	mCanvasDrawingSession;

		Color					mFillColor;
		Color					mStrokeColor;
};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: - CWin2DRenderer

// MARK: Lifecycle methods

//----------------------------------------------------------------------------------------------------------------------
CWin2DRenderer::CWin2DRenderer(const CanvasDrawingSession& canvasDrawingSession) : C2DRenderer()
//----------------------------------------------------------------------------------------------------------------------
{
	mInternals = new Internals(canvasDrawingSession);
}

//----------------------------------------------------------------------------------------------------------------------
CWin2DRenderer::~CWin2DRenderer()
//----------------------------------------------------------------------------------------------------------------------
{
	Delete(mInternals);
}

// MARK: C2DRenderer methods

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::setFillColor(const CColor& color)
//----------------------------------------------------------------------------------------------------------------------
{
	// Update
	mInternals->mFillColor =
			ColorHelper::FromArgb(
					(uint8_t) (color.getRGBValues().getAlpha() * 255.0),
					(uint8_t) (color.getRGBValues().getRed() * 255.0),
					(uint8_t) (color.getRGBValues().getGreen() * 255.0),
					(uint8_t) (color.getRGBValues().getBlue() * 255.0));
}

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::setStrokeColor(const CColor& color)
//----------------------------------------------------------------------------------------------------------------------
{
	// Update
	mInternals->mStrokeColor =
			ColorHelper::FromArgb(
					(uint8_t) (color.getRGBValues().getAlpha() * 255.0),
					(uint8_t) (color.getRGBValues().getRed() * 255.0),
					(uint8_t) (color.getRGBValues().getGreen() * 255.0),
					(uint8_t) (color.getRGBValues().getBlue() * 255.0));
}

// MARK: T2DRenderer methods

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::strokeLine(const S2DPointF32& startPoint, const S2DPointF32& endPoint, bool antiAlias,
		Float32 lineWidth) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Stroke line
	mInternals->mCanvasDrawingSession.Antialiasing(
			antiAlias ? CanvasAntialiasing::Antialiased : CanvasAntialiasing::Aliased);
	mInternals->mCanvasDrawingSession.DrawLine(startPoint.mX, startPoint.mY, endPoint.mX, endPoint.mY,
			mInternals->mStrokeColor, lineWidth);
}

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::strokeLines(const S2DPointF32* points, UInt32 count, bool antiAlias, Float32 lineWidth) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Preflight
	AssertNotNil(points);
	if (points == nil)
		return;

	AssertFailIf(count <= 1);
	if (count <= 1)
		return;

	// Setup
	mInternals->mCanvasDrawingSession.Antialiasing(
			antiAlias ? CanvasAntialiasing::Antialiased : CanvasAntialiasing::Aliased);

	// Iterate points
	for (UInt32 i = 0; i < count - 1; i++)
		// Draw line
		mInternals->mCanvasDrawingSession.DrawLine(points[i].mX, points[i].mY, points[i + 1].mX, points[i + 1].mY,
			mInternals->mStrokeColor, lineWidth);
}

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::fillRect(const S2DRectF32& rect) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Fill rect
	mInternals->mCanvasDrawingSession.FillRectangle(rect.getMinX(), rect.getMinY(), rect.getWidth(), rect.getHeight(),
			mInternals->mFillColor);
}

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::shadeRect(const S2DRectF32& rect, const S2DPointF32& shadeStartPoint,
		const S2DPointF32& shadeEndPoint, const CColor& startColor, const CColor& endColor) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup
	std::vector<CanvasGradientStop>	canvasGradientStops =
											{
												{0.0f,
														ColorHelper::FromArgb(
																(uint8_t) (startColor.getRGBValues().getAlpha() * 255.0),
																(uint8_t)(startColor.getRGBValues().getRed() * 255.0),
																(uint8_t)(startColor.getRGBValues().getGreen() * 255.0),
																(uint8_t)(startColor.getRGBValues().getBlue() * 255.0))},
												{1.0f,
														ColorHelper::FromArgb(
																(uint8_t)(endColor.getRGBValues().getAlpha() * 255.0),
																(uint8_t)(endColor.getRGBValues().getRed() * 255.0),
																(uint8_t)(endColor.getRGBValues().getGreen() * 255.0),
																(uint8_t)(endColor.getRGBValues().getBlue() * 255.0))},
											};
	CanvasLinearGradientBrush	canvasLinearGradientBrush(mInternals->mCanvasDrawingSession, canvasGradientStops);
	canvasLinearGradientBrush.StartPoint({shadeStartPoint.mX, shadeStartPoint.mY});
	canvasLinearGradientBrush.EndPoint({shadeEndPoint.mX, shadeEndPoint.mY});

	// Fill rect
	mInternals->mCanvasDrawingSession.FillRectangle(rect.getMinX(), rect.getMinY(), rect.getWidth(), rect.getHeight(),
			canvasLinearGradientBrush);
}

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::strokeRect(const S2DRectF32& rect) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Draw rect
	mInternals->mCanvasDrawingSession.DrawRectangle(rect.getMinX(), rect.getMinY(), rect.getWidth(), rect.getHeight(),
			mInternals->mStrokeColor);
}

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::strokePath(const S2DPath32& path, Float32 lineWidth,
		const S2DAffineTransformF32& affineTransform) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup
	CanvasPathBuilder	canvasPathBuilder(mInternals->mCanvasDrawingSession.Device());

	// Iterate segments
	S2DPathIterateInfo	pathIterateInfo = {canvasPathBuilder, affineTransform};
	((S2DPath32*) &path)->iterateSegments((S2DPath32::MoveToProc) Internals::pathSegmentMoveTo32,
			(S2DPath32::LineToProc) Internals::pathSegmentLineTo32,
			(S2DPath32::QuadCurveToProc) Internals::pathSegmentQuadCurveTo32,
			(S2DPath32::CubicCurveToProc) Internals::pathSegmentCubicCurveTo32,
			(S2DPath32::ArcToProc) Internals::pathSegmentArcTo32, &pathIterateInfo);

	// Draw
	mInternals->mCanvasDrawingSession.DrawGeometry(CanvasGeometry::CreatePath(canvasPathBuilder),
			mInternals->mStrokeColor, lineWidth);
}

//----------------------------------------------------------------------------------------------------------------------
S2DSizeF32 CWin2DRenderer::getTextSize(const CString& string, const Font& font) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup
	CanvasTextFormat	canvasTextFormat;
	canvasTextFormat.FontFamily(font.getName().getOSString());
	canvasTextFormat.FontSize(font.getSize());

	CanvasTextLayout	canvasTextLayout(mInternals->mCanvasDrawingSession.Device(), string.getOSString(),
								canvasTextFormat, FLT_MAX, FLT_MAX);

	return S2DSizeF32(canvasTextLayout.LayoutBounds().Width, canvasTextLayout.LayoutBounds().Height);
}

//----------------------------------------------------------------------------------------------------------------------
void CWin2DRenderer::strokeText(const CString& string, const Font& font, const S2DPointF32& point,
		TextPositioning textPositioning) const
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup
	float				x = point.mX;
	float				y = point.mY;

	CanvasTextFormat	canvasTextFormat;
	canvasTextFormat.FontFamily(font.getName().getOSString());
	canvasTextFormat.FontSize(font.getSize());
	switch (textPositioning) {
		case kTextPositioningTowardTrailingAbove:
			// Toward trailing, above
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Left);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Bottom);
			y += font.getSize() / 2.0f;
			break;

		case kTextPositioningTowardTrailingCenter:
			// Toward trailing, center
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Left);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Center);
			break;

		case kTextPositioningTowardTrailingBelow:
			// Toward trailing, below
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Left);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Top);
			y -= font.getSize() / 2.0f;
			break;

		case kTextPositioningCenterAbove:
			// Center, above
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Center);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Bottom);
			y += font.getSize() / 2.0f;
			break;

		case kTextPositioningCenter:
			// Center, center
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Center);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Center);
			break;

		case kTextPositioningCenterBelow:
			// Center, below
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Center);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Top);
			y -= font.getSize() / 2.0f;
			break;

		case kTextPositioningTowardLeadingAbove:
			// Toward leading, above
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Right);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Bottom);
			y += font.getSize() / 2.0f;
			break;

		case kTextPositioningTowardLeadingCenter:
			// Toward leading, center
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Right);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Center);
			break;

		case kTextPositioningTowardLeadingBelow:
			// Toward leading, below
			canvasTextFormat.HorizontalAlignment(CanvasHorizontalAlignment::Right);
			canvasTextFormat.VerticalAlignment(CanvasVerticalAlignment::Top);
			y -= font.getSize() / 2.0f;
			break;
	}

	// Draw text
	mInternals->mCanvasDrawingSession.DrawText(string.getOSString(), x, y, mInternals->mStrokeColor, canvasTextFormat);
}
