using UnrealBuildTool;
public class FutbolArenaEditorTarget : TargetRules {
 public FutbolArenaEditorTarget(TargetInfo Target) : base(Target) {
 Type = TargetType.Editor; DefaultBuildSettings = BuildSettingsVersion.V5;
 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6; ExtraModuleNames.Add("FutbolArena");
 }
}
