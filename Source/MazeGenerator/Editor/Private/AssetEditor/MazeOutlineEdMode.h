// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "EdMode.h"

class FMazeOutlineEdMode : public FEdMode
{
	friend struct FMazeOutlineAssetEditor;

public:
	~FMazeOutlineEdMode();

public:

	virtual bool UsesToolkits() const override;

	virtual void Initialize() override;
	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime);
	virtual void Render(const FSceneView* SceneView, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;

	virtual bool HandleClick(FEditorViewportClient* ViewportClient, HHitProxy* HitProxy, const FViewportClick& ClickData) override;
};