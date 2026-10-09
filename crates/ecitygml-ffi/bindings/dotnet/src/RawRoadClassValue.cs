using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct RoadClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoadClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(RoadClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoadClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(RoadClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoadClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(RoadClassValue* handle);
}