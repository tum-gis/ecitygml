using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficSpacePropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpacePropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpaceProperty* Next(TrafficSpacePropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpacePropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficSpacePropertyIterator* handle);
}