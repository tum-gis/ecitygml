using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DirectPositionIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DirectPositionIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* Next(DirectPositionIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DirectPositionIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(DirectPositionIterator* handle);
}