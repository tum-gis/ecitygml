using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Error
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Error_kind", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ErrorKind Kind(Error* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Error_message", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Message(Error* handle, DiplomatWrite* writeable);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Error_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Error* handle);
}