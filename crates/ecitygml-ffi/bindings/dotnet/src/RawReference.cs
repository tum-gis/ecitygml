using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Reference
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Reference_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(Reference* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Reference_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Reference* handle);
}