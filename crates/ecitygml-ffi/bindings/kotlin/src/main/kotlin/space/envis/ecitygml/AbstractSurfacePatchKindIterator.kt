package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractSurfacePatchKindIteratorLib: Library {
    fun ecitygml_AbstractSurfacePatchKindIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractSurfacePatchKindIterator_next(handle: Pointer): Pointer?
}
typealias AbstractSurfacePatchKindIteratorIteratorItem = AbstractSurfacePatchKind?
/** Iterates over surface patches, borrowed from a city model.
*/
class AbstractSurfacePatchKindIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractSurfacePatchKind?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractSurfacePatchKindIteratorCleaner(val handle: Pointer, val lib: AbstractSurfacePatchKindIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractSurfacePatchKindIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractSurfacePatchKindIterator.AbstractSurfacePatchKindIteratorCleaner(handle, AbstractSurfacePatchKindIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractSurfacePatchKindIteratorLib> = AbstractSurfacePatchKindIteratorLib::class.java
        internal val lib: AbstractSurfacePatchKindIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractSurfacePatchKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSurfacePatchKindIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractSurfacePatchKind(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractSurfacePatchKind?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}