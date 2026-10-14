using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct ElevationReferenceValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ElevationReferenceValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(ElevationReferenceValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ElevationReferenceValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(ElevationReferenceValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ElevationReferenceValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(ElevationReferenceValue* handle);
}