// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class age_of_night : ModuleRules
{
	public age_of_night(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"age_of_night",
			"age_of_night/AgeOfNight",
			"age_of_night/AgeOfNight/Tests",
			"age_of_night/AgeOfNight/Nav",
			"age_of_night/Variant_Horror",
			"age_of_night/Variant_Horror/UI",
			"age_of_night/Variant_Shooter",
			"age_of_night/Variant_Shooter/AI",
			"age_of_night/Variant_Shooter/UI",
			"age_of_night/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
