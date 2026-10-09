using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SolidProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolidProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Solid* Object(SolidProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolidProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(SolidProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolidProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SolidProperty* handle);
}