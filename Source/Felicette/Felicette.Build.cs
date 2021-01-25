// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Felicette : ModuleRules
{
	public Felicette(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","NavigationSystem", "AIModule", "Niagara", "UMG" });
    }
}
