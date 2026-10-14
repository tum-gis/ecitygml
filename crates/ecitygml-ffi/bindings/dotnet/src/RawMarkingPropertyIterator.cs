using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MarkingPropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingPropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MarkingProperty* Next(MarkingPropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingPropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MarkingPropertyIterator* handle);
}