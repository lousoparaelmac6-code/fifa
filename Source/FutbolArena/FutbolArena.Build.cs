using UnrealBuildTool;
public class FutbolArena : ModuleRules {
 public FutbolArena(ReadOnlyTargetRules Target) : base(Target) {
 PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
 PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
 }
}
