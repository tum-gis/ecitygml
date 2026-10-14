using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractCityObjectPropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectPropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCityObjectProperty* Next(AbstractCityObjectPropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectPropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractCityObjectPropertyIterator* handle);
}