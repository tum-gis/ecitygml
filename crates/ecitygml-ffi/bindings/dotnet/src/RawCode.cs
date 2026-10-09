using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Code
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Code_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(Code* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Code_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Code* handle);
}