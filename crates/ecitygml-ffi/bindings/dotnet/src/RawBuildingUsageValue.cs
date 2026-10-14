using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingUsageValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUsageValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(BuildingUsageValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUsageValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(BuildingUsageValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUsageValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingUsageValue* handle);
}