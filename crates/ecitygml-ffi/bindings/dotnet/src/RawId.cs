using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Id
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Id_as_str", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 AsStr(Id* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Id_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Id* handle);
}