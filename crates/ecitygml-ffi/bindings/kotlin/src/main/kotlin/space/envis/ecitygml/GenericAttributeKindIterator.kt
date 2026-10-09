package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface GenericAttributeKindIteratorLib: Library {
    fun ecitygml_GenericAttributeKindIterator_destroy(handle: Pointer)
    fun ecitygml_GenericAttributeKindIterator_next(handle: Pointer): Pointer?
}
typealias GenericAttributeKindIteratorIteratorItem = GenericAttributeKind?
/** Iterates over generic attributes, borrowed from a city model.
*/
class GenericAttributeKindIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<GenericAttributeKind?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class GenericAttributeKindIteratorCleaner(val handle: Pointer, val lib: GenericAttributeKindIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_GenericAttributeKindIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, GenericAttributeKindIterator.GenericAttributeKindIteratorCleaner(handle, GenericAttributeKindIterator.lib));
    }

    companion object {
        internal val libClass: Class<GenericAttributeKindIteratorLib> = GenericAttributeKindIteratorLib::class.java
        internal val lib: GenericAttributeKindIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): GenericAttributeKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GenericAttributeKindIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = GenericAttributeKind(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): GenericAttributeKind?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}