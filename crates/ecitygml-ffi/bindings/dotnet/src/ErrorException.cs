using System;

namespace Ecitygml;

/// <summary>
/// If <c>Error</c> is an opaque error that borrows from an opaque
/// parameter or the receiver, that dependency is retained by <c>Inner</c>'s
/// own native resource state (see <c>RustHandle.cs</c>) rather than by
/// this exception class — so no separate keep-alive plumbing is needed here.
/// </summary>
public class ErrorException : Exception
{
    public Error Inner { get; }

    public ErrorException(Error inner) : base(
        $"Error: {inner}"
    )
    {
        Inner = inner;
    }
}