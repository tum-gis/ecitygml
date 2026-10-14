using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SolitaryVegetationObjectFunctionValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolitaryVegetationObjectFunctionValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolitaryVegetationObjectFunctionValue* Next(SolitaryVegetationObjectFunctionValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolitaryVegetationObjectFunctionValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SolitaryVegetationObjectFunctionValueIterator* handle);
}