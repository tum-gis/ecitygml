package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TriangleIteratorLib: Library {
    fun ecitygml_TriangleIterator_destroy(handle: Pointer)
    fun ecitygml_TriangleIterator_next(handle: Pointer): Pointer?
}
typealias TriangleIteratorIteratorItem = Triangle?
/** Iterates over triangles (e.g. of a triangulated surface), borrowed from a city model.
*/
class TriangleIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<Triangle?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TriangleIteratorCleaner(val handle: Pointer, val lib: TriangleIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TriangleIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TriangleIterator.TriangleIteratorCleaner(handle, TriangleIterator.lib));
    }

    companion object {
        internal val libClass: Class<TriangleIteratorLib> = TriangleIteratorLib::class.java
        internal val lib: TriangleIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): Triangle? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TriangleIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Triangle(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): Triangle?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}