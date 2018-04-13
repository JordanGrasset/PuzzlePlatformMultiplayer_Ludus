// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PuzzleMultiMaster_V1EditorTarget : TargetRules
{
	public PuzzleMultiMaster_V1EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("PuzzleMultiMaster_V1");
	}
}
