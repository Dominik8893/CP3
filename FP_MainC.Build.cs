// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FP_MainC : ModuleRules
{
	public FP_MainC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","HeadMountedDisplay"});
	}
}
//