using System;
using System.Runtime.InteropServices;

namespace Envis.Ecitygml.Raw;

using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DiplomatOptionBool
{
    [StructLayout(LayoutKind.Explicit)]
    private struct InnerUnion
    {
        [FieldOffset(0)] internal byte value;
    }

    private InnerUnion _inner;

    public DiplomatBool IsSome;

    public bool Value => IsSome ? _inner.value != 0 : throw new InvalidOperationException("Option is None");
}