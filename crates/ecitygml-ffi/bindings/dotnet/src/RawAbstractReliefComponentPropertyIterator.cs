using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractReliefComponentPropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractReliefComponentPropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractReliefComponentProperty* Next(AbstractReliefComponentPropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractReliefComponentPropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractReliefComponentPropertyIterator* handle);
}