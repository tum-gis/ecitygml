using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingSubdivisionFunctionValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionFunctionValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(BuildingSubdivisionFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionFunctionValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(BuildingSubdivisionFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionFunctionValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingSubdivisionFunctionValue* handle);
}