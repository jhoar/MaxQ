// Copyright 2021 Gamergenic.  See full copyright notice in MainModule.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// This is a sample application demonstrating usage of Module 'Spice',
// an implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/


using UnrealBuildTool;
using EpicGames.Core;
using System.Collections.Generic;
using System.IO;

public class SpiceTarget : TargetRules
{
    public const string RelativePathToCSpiceToolkit = "Source\\SpaceToolkit\\CSpice_Library\\cspice\\";
    public const string RelativePathToCSpiceLib = "Source\\SpaceToolkit\\CSpice_Library\\lib\\Win64\\cspice.lib";

    public SpiceTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange( new string[] { "Spice" } );

        BuildCSpiceLib(this);
    }

    static public string CSpiceLibPath(ReadOnlyTargetRules targetRules)
    {
        string relativePathToCSpiceLib = "Source\\SpaceToolkit\\CSpice_Library\\lib\\" + targetRules.Platform.ToString() + "\\cspice.lib";

        return Path.Combine(targetRules.ProjectFile.Directory.FullName, relativePathToCSpiceLib);
    }

    static public void BuildCSpiceLib(TargetRules targetRules)
    {
        string pathToCSpiceLib = CSpiceLibPath(new ReadOnlyTargetRules(targetRules));

        if (!File.Exists(pathToCSpiceLib))
        {
            // Note :  If the step fails, since it's a prebuild step, these rules will not be rebuilt.
            // So, don't cause a failure here, if you're iterating on these rules.
            // Also, changes to the invocation won't be seen until the following build!
            System.Console.WriteLine("Rebuilding cspice toolkit lib");
            targetRules.PreBuildSteps.Add("$(ProjectDir)\\" + RelativePathToCSpiceToolkit + "makeall_ue.bat \"$(ProjectDir)\\" + RelativePathToCSpiceToolkit + "\"");
        }
        else
        {
            System.Console.WriteLine("cspice toolkit lib is up to date");
        }
    }
}
