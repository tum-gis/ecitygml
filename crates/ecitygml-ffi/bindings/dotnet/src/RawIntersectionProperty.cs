using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct IntersectionProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntersectionProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Intersection* Object(IntersectionProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntersectionProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(IntersectionProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntersectionProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(IntersectionProperty* handle);
}