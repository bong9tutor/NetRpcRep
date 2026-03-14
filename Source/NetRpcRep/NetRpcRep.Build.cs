// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NetRpcRep : ModuleRules
{
	public NetRpcRep(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "SlateCore" });

		PublicIncludePaths.AddRange(new string[]
		{
			"NetRpcRep"
		});
	}
}
