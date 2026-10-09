using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BoundingShape
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BoundingShape_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* Envelope(BoundingShape* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BoundingShape_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BoundingShape* handle);
}