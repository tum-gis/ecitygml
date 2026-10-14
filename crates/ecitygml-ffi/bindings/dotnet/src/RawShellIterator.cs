using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct ShellIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ShellIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Shell* Next(ShellIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ShellIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(ShellIterator* handle);
}