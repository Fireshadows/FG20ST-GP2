// Copyright Epic Games, Inc. All Rights Reserved.

using System.Collections.Generic;
using UnrealBuildTool;

public class FGGP2EditorTarget : TargetRules {
	public FGGP2EditorTarget (TargetInfo Target) : base (Target) {
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add ("FGGP2");
		ExtraModuleNames.AddRange (new string[] { "DialogueEditor" });
	}
}