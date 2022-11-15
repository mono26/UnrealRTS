// Copyright: For learning purposes, Mono Zubiria.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyFirstRTSTarget : TargetRules
{
	public MyFirstRTSTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MyFirstRTS" } );
	}
}
