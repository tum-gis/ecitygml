using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractBuildingSubdivisionPropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractBuildingSubdivisionPropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractBuildingSubdivisionProperty* Next(AbstractBuildingSubdivisionPropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractBuildingSubdivisionPropertyIterator* handle);
}