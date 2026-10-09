using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityObjectRelationPropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelationPropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationProperty* Next(CityObjectRelationPropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelationPropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityObjectRelationPropertyIterator* handle);
}