using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingSubdivisionClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(BuildingSubdivisionClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(BuildingSubdivisionClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingSubdivisionClassValue* handle);
}