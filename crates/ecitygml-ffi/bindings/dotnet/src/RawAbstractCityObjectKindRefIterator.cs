using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractCityObjectKindRefIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKindRefIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCityObjectKindRef* Next(AbstractCityObjectKindRefIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKindRefIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractCityObjectKindRefIterator* handle);
}