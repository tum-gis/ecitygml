using System;
using System.Runtime.InteropServices;

namespace Envis.Ecitygml.Raw;

using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DiplomatOptionSpaceType
{
    [StructLayout(LayoutKind.Explicit)]
    private struct InnerUnion
    {
        [FieldOffset(0)] internal SpaceType value;
    }

    private InnerUnion _inner;

    public DiplomatBool IsSome;

    public SpaceType Value => IsSome ? _inner.value : throw new InvalidOperationException("Option is None");
}