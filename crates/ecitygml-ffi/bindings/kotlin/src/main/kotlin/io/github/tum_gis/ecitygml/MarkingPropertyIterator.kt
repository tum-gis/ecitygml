package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MarkingPropertyIteratorLib: Library {
    fun ecitygml_MarkingPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_MarkingPropertyIterator_next(handle: Pointer): Pointer?
}
typealias MarkingPropertyIteratorIteratorItem = MarkingProperty?
/** Iterates over marking properties, borrowed from a city model.
*/
class MarkingPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<MarkingProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class MarkingPropertyIteratorCleaner(val handle: Pointer, val lib: MarkingPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_MarkingPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MarkingPropertyIterator.MarkingPropertyIteratorCleaner(handle, MarkingPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<MarkingPropertyIteratorLib> = MarkingPropertyIteratorLib::class.java
        internal val lib: MarkingPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): MarkingProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MarkingPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MarkingProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): MarkingProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}