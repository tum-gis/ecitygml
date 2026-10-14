using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct PlantCoverClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(PlantCoverClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(PlantCoverClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(PlantCoverClassValue* handle);
}