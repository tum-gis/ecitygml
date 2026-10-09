using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct PlantCoverFunctionValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverFunctionValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(PlantCoverFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverFunctionValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(PlantCoverFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverFunctionValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(PlantCoverFunctionValue* handle);
}