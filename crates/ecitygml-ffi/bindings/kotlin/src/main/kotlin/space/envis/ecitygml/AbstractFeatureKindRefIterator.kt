package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractFeatureKindRefIteratorLib: Library {
    fun ecitygml_AbstractFeatureKindRefIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractFeatureKindRefIterator_next(handle: Pointer): Pointer?
}
typealias AbstractFeatureKindRefIteratorIteratorItem = AbstractFeatureKindRef?
/** Iterates over features of a city model, which it borrows.
*/
class AbstractFeatureKindRefIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractFeatureKindRef?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractFeatureKindRefIteratorCleaner(val handle: Pointer, val lib: AbstractFeatureKindRefIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractFeatureKindRefIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractFeatureKindRefIterator.AbstractFeatureKindRefIteratorCleaner(handle, AbstractFeatureKindRefIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractFeatureKindRefIteratorLib> = AbstractFeatureKindRefIteratorLib::class.java
        internal val lib: AbstractFeatureKindRefIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractFeatureKindRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractFeatureKindRefIterator_next(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = AbstractFeatureKindRef(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractFeatureKindRef?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}