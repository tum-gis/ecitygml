using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(BuildingClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(BuildingClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingClassValue* handle);
}