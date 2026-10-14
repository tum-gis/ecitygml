package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractFillingSurfacePropertyIteratorLib: Library {
    fun ecitygml_AbstractFillingSurfacePropertyIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractFillingSurfacePropertyIterator_next(handle: Pointer): Pointer?
}
typealias AbstractFillingSurfacePropertyIteratorIteratorItem = AbstractFillingSurfaceProperty?
/** Iterates over filling surface properties, borrowed from a city model.
*/
class AbstractFillingSurfacePropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractFillingSurfaceProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractFillingSurfacePropertyIteratorCleaner(val handle: Pointer, val lib: AbstractFillingSurfacePropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractFillingSurfacePropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractFillingSurfacePropertyIterator.AbstractFillingSurfacePropertyIteratorCleaner(handle, AbstractFillingSurfacePropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractFillingSurfacePropertyIteratorLib> = AbstractFillingSurfacePropertyIteratorLib::class.java
        internal val lib: AbstractFillingSurfacePropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractFillingSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractFillingSurfacePropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractFillingSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractFillingSurfaceProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}