using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SectionProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Section* Object(SectionProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(SectionProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SectionProperty* handle);
}