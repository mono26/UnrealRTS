// Copyright: For learning purposes, Mono Zubiria.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyFirstRTSEditorTarget : TargetRules
{
	public MyFirstRTSEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MyFirstRTS" } );
	}
}
