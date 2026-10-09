using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractFeatureKindRefIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFeatureKindRefIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFeatureKindRef* Next(AbstractFeatureKindRefIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFeatureKindRefIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractFeatureKindRefIterator* handle);
}