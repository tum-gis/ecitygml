using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractSpaceBoundaryPropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSpaceBoundaryPropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryProperty* Next(AbstractSpaceBoundaryPropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractSpaceBoundaryPropertyIterator* handle);
}