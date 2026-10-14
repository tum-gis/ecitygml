using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CodeIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CodeIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Next(CodeIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CodeIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CodeIterator* handle);
}