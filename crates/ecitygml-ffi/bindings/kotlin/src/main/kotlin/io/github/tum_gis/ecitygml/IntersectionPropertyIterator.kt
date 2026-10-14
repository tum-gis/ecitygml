package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface IntersectionPropertyIteratorLib: Library {
    fun ecitygml_IntersectionPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_IntersectionPropertyIterator_next(handle: Pointer): Pointer?
}
typealias IntersectionPropertyIteratorIteratorItem = IntersectionProperty?
/** Iterates over intersection properties, borrowed from a city model.
*/
class IntersectionPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<IntersectionProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class IntersectionPropertyIteratorCleaner(val handle: Pointer, val lib: IntersectionPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_IntersectionPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, IntersectionPropertyIterator.IntersectionPropertyIteratorCleaner(handle, IntersectionPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<IntersectionPropertyIteratorLib> = IntersectionPropertyIteratorLib::class.java
        internal val lib: IntersectionPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): IntersectionProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_IntersectionPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = IntersectionProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): IntersectionProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}