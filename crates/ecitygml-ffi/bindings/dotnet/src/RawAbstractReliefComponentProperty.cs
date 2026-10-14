using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractReliefComponentProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractReliefComponentProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractReliefComponentKind* Object(AbstractReliefComponentProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractReliefComponentProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(AbstractReliefComponentProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractReliefComponentProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractReliefComponentProperty* handle);
}