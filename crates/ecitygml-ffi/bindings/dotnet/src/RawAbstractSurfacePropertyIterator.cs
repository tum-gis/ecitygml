using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractSurfacePropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfacePropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSurfaceProperty* Next(AbstractSurfacePropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfacePropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractSurfacePropertyIterator* handle);
}