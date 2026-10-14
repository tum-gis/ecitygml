using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MarkingProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Marking* Object(MarkingProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(MarkingProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MarkingProperty* handle);
}