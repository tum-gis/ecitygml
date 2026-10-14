using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractGeometryProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractGeometryKind* Object(AbstractGeometryProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(AbstractGeometryProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractGeometryProperty* handle);
}