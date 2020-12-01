// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class cs378_final : ModuleRules
{
	public cs378_final(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RPGCharacter" });
		
		PublicIncludePaths.AddRange(new string[] { "../Plugins/RPGCharacter/Source/RPGCharacter/Player"});

		PrivateDependencyModuleNames.AddRange(new string[] { "RPGCharacter" });
		PrivateIncludePathModuleNames.AddRange(new string[] { "RPGCharacter" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
