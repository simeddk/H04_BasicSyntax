using UnrealBuildTool;

public class H04_BasicSyntax : ModuleRules
{
	public H04_BasicSyntax(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.Add(ModuleDirectory);
	}
}
