using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AuxiliaryTrafficSpaceFunctionValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AuxiliaryTrafficSpaceFunctionValue* Next(AuxiliaryTrafficSpaceFunctionValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AuxiliaryTrafficSpaceFunctionValueIterator* handle);
}