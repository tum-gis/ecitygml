using System;

namespace Envis.Ecitygml.Diplomat;

#nullable enable

public delegate void DiplomatBorrowedSpanAction<T>(ReadOnlySpan<T> span) where T : unmanaged;

/// <summary>
/// A zero-copy view over memory Rust still owns (a borrowed <c>&amp;str</c> /
/// <c>&amp;[T]</c> return). Unlike <c>RustVec</c>, there's nothing to free
/// here — Rust still owns this memory, so there's no <c>IDisposable</c> and
/// no native allocation of its own to free. <c>edges</c> contains retained
/// references to whatever opaque values this was borrowed from, keeping their
/// native allocations alive while this view is reachable.
/// </summary>
/// <remarks>
/// This intentionally does not expose a public <c>Span</c>-returning
/// property. A caller could extract it, let this object go, and be left
/// holding a span with nothing keeping <c>edges</c> (and the parent allocations
/// roots) alive — exactly the trap <c>RustVec</c> avoids by not implementing
/// <c>MemoryManager&lt;T&gt;</c>. <see cref="WithSpan"/> gives synchronous,
/// zero-copy, read-only access instead: the callback receives the span
/// directly, so it can never outlive this object's own lifetime. This is a
/// reference type: assigning it to another variable aliases the same object,
/// so the retained parent references are released exactly once after all
/// aliases become unreachable. <see cref="Clone"/> is the explicit,
/// independent data copy.
/// </remarks>
public sealed unsafe class DiplomatBorrowedSpan<T> where T : unmanaged
{
    private readonly T* _ptr;
    private readonly int _len;
    private readonly object[] _edges;

    internal DiplomatBorrowedSpan(T* ptr, nuint len, object[] edges)
    {
        // Mirror RustVec: .NET Span/Memory lengths are int-sized. Call sites
        // build retain-token edges before construction; on the oversize path
        // release them and suppress this incomplete finalizer before throwing.
        // Otherwise ~DiplomatBorrowedSpan NREs on the still-null `_edges`
        // field, catch {} swallows it, and the parent retain leaks.
        if (len > (nuint)int.MaxValue)
        {
            foreach (object edge in edges)
            {
                (edge as IDisposable)?.Dispose();
            }
            GC.SuppressFinalize(this);
            throw new IndexOutOfRangeException("Borrowed Rust slice is too large for a .NET Span/Memory");
        }
        _ptr = ptr;
        _len = (int)len;
        _edges = edges;
    }

    public int Length => _len;

    /// <summary>
    /// Synchronous, zero-copy, read-only access. The span is valid only for
    /// the duration of this callback.
    /// </summary>
    public void WithSpan(DiplomatBorrowedSpanAction<T> action)
    {
        if (action is null)
        {
            throw new ArgumentNullException(nameof(action));
        }
        action(new ReadOnlySpan<T>(_ptr, _len));
        GC.KeepAlive(this);
    }

    /// <summary>An explicit, independent copy — never implicit.</summary>
    public T[] Clone()
    {
        T[] result = new ReadOnlySpan<T>(_ptr, _len).ToArray();
        GC.KeepAlive(this);
        return result;
    }

    ~DiplomatBorrowedSpan()
    {
        try
        {
            foreach (object edge in _edges)
            {
                (edge as IDisposable)?.Dispose();
            }
        }
        catch
        {
        }
    }
}