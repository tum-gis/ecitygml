using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficSpaceReferenceIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceReferenceIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpaceReference* Next(TrafficSpaceReferenceIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceReferenceIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficSpaceReferenceIterator* handle);
}