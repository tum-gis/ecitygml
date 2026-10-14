package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractRingKindIteratorLib: Library {
    fun ecitygml_AbstractRingKindIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractRingKindIterator_next(handle: Pointer): Pointer?
}
typealias AbstractRingKindIteratorIteratorItem = AbstractRingKind?
/** Iterates over rings (e.g. a polygon's interior rings), borrowed from a city model.
*/
class AbstractRingKindIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractRingKind?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractRingKindIteratorCleaner(val handle: Pointer, val lib: AbstractRingKindIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractRingKindIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractRingKindIterator.AbstractRingKindIteratorCleaner(handle, AbstractRingKindIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractRingKindIteratorLib> = AbstractRingKindIteratorLib::class.java
        internal val lib: AbstractRingKindIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractRingKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractRingKindIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractRingKind(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractRingKind?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}