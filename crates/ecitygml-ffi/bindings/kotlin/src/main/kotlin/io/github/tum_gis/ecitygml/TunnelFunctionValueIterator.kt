package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TunnelFunctionValueIteratorLib: Library {
    fun ecitygml_TunnelFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_TunnelFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias TunnelFunctionValueIteratorIteratorItem = TunnelFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class TunnelFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TunnelFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TunnelFunctionValueIteratorCleaner(val handle: Pointer, val lib: TunnelFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TunnelFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TunnelFunctionValueIterator.TunnelFunctionValueIteratorCleaner(handle, TunnelFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<TunnelFunctionValueIteratorLib> = TunnelFunctionValueIteratorLib::class.java
        internal val lib: TunnelFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TunnelFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TunnelFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TunnelFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TunnelFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}