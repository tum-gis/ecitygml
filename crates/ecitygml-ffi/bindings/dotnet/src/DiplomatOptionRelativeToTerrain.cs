using System;
using System.Runtime.InteropServices;

namespace Ecitygml.Raw;

using Ecitygml;
using Ecitygml.Diplomat;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DiplomatOptionRelativeToTerrain
{
    [StructLayout(LayoutKind.Explicit)]
    private struct InnerUnion
    {
        [FieldOffset(0)] internal RelativeToTerrain value;
    }

    private InnerUnion _inner;

    public DiplomatBool IsSome;

    public RelativeToTerrain Value => IsSome ? _inner.value : throw new InvalidOperationException("Option is None");
}