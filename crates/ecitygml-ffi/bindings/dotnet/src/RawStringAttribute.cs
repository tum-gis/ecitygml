using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct StringAttribute
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_StringAttribute_name", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Name(StringAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_StringAttribute_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(StringAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_StringAttribute_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(StringAttribute* handle);
}