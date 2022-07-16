// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeOutlineEdMode.h"
#include "MazeOutlineAssetEditor.h"

FMazeOutlineEdMode::~FMazeOutlineEdMode()
{
}

bool FMazeOutlineEdMode::UsesToolkits() const
{
	return false;
}

void FMazeOutlineEdMode::Initialize()
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineEdMode::Initialize] Not implemented"));
}

void FMazeOutlineEdMode::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineEdMode::Enter] Not implemented"));
}

void FMazeOutlineEdMode::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineEdMode::Exit] Not implemented"));
}

void FMazeOutlineEdMode::Tick(FEditorViewportClient* ViewportClient, float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineEdMode::Tick] Not implemented"));
}

void FMazeOutlineEdMode::Render(const FSceneView* SceneView, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineEdMode::Render] Not implemented"));
}

bool FMazeOutlineEdMode::HandleClick(FEditorViewportClient* ViewportClient, HHitProxy* HitProxy, const FViewportClick& ClickData)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineEdMode::HandleClick] Not implemented"));
	return false;
}

void FMazeOutlineEdMode::UpdateFragmentDetailsView(int32 Index, TSharedPtr<FStructDetailsTabWrapper> FragmentTab)
{
	if (Editor.IsValid() && FragmentTab.IsValid())
	{
		UMazeOutline* Outline = Editor.Pin()->CurrentOutline.Get();
		if (Outline)
		{
			if (Outline->Fragments.IsValidIndex(Index))
			{
				FragmentTab->SetData(
					FMazeFragmentOutline::StaticStruct(),
					&Outline->Fragments[Index],
					[](const FPropertyChangedEvent& Event)
					{
						// Mark Cached object dirty on ed mode and call HandlePropertyChanged on the ed mode
						UE_LOG(LogTemp, Display, TEXT("%s changed!"), *Event.GetPropertyName().ToString());
					});
			}
		}
	}
}
