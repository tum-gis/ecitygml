package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficSpacePropertyIteratorLib: Library {
    fun ecitygml_TrafficSpacePropertyIterator_destroy(handle: Pointer)
    fun ecitygml_TrafficSpacePropertyIterator_next(handle: Pointer): Pointer?
}
typealias TrafficSpacePropertyIteratorIteratorItem = TrafficSpaceProperty?
/** Iterates over traffic space properties, borrowed from a city model.
*/
class TrafficSpacePropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TrafficSpaceProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TrafficSpacePropertyIteratorCleaner(val handle: Pointer, val lib: TrafficSpacePropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficSpacePropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficSpacePropertyIterator.TrafficSpacePropertyIteratorCleaner(handle, TrafficSpacePropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<TrafficSpacePropertyIteratorLib> = TrafficSpacePropertyIteratorLib::class.java
        internal val lib: TrafficSpacePropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TrafficSpaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpacePropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficSpaceProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TrafficSpaceProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}