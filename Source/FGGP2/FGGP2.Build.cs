// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FGGP2 : ModuleRules
{
	public FGGP2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
