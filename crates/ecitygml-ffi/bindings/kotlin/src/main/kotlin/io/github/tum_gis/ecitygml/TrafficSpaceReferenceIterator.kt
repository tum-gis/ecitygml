package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficSpaceReferenceIteratorLib: Library {
    fun ecitygml_TrafficSpaceReferenceIterator_destroy(handle: Pointer)
    fun ecitygml_TrafficSpaceReferenceIterator_next(handle: Pointer): Pointer?
}
typealias TrafficSpaceReferenceIteratorIteratorItem = TrafficSpaceReference?
/** Iterates over a list of traffic space references, borrowed from a city model.
*/
class TrafficSpaceReferenceIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TrafficSpaceReference?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TrafficSpaceReferenceIteratorCleaner(val handle: Pointer, val lib: TrafficSpaceReferenceIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficSpaceReferenceIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficSpaceReferenceIterator.TrafficSpaceReferenceIteratorCleaner(handle, TrafficSpaceReferenceIterator.lib));
    }

    companion object {
        internal val libClass: Class<TrafficSpaceReferenceIteratorLib> = TrafficSpaceReferenceIteratorLib::class.java
        internal val lib: TrafficSpaceReferenceIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TrafficSpaceReference? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpaceReferenceIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficSpaceReference(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TrafficSpaceReference?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}