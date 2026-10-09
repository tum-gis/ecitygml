using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct HRef
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HRef_is_local", CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.U1)]
    internal static unsafe extern bool IsLocal(HRef* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HRef_to_string", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void ToString(HRef* handle, DiplomatWrite* writeable);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HRef_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(HRef* handle);
}