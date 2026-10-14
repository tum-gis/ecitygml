package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TunnelPartPropertyIteratorLib: Library {
    fun ecitygml_TunnelPartPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_TunnelPartPropertyIterator_next(handle: Pointer): Pointer?
}
typealias TunnelPartPropertyIteratorIteratorItem = TunnelPartProperty?
/** Iterates over tunnel part properties, borrowed from a city model.
*/
class TunnelPartPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TunnelPartProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TunnelPartPropertyIteratorCleaner(val handle: Pointer, val lib: TunnelPartPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TunnelPartPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TunnelPartPropertyIterator.TunnelPartPropertyIteratorCleaner(handle, TunnelPartPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<TunnelPartPropertyIteratorLib> = TunnelPartPropertyIteratorLib::class.java
        internal val lib: TunnelPartPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TunnelPartProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TunnelPartPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TunnelPartProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TunnelPartProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}