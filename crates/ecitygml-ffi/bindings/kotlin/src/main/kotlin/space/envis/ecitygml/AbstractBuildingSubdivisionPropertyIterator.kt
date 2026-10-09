package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractBuildingSubdivisionPropertyIteratorLib: Library {
    fun ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(handle: Pointer): Pointer?
}
typealias AbstractBuildingSubdivisionPropertyIteratorIteratorItem = AbstractBuildingSubdivisionProperty?
/** Iterates over building subdivision properties, borrowed from a city model.
*/
class AbstractBuildingSubdivisionPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractBuildingSubdivisionProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractBuildingSubdivisionPropertyIteratorCleaner(val handle: Pointer, val lib: AbstractBuildingSubdivisionPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractBuildingSubdivisionPropertyIterator.AbstractBuildingSubdivisionPropertyIteratorCleaner(handle, AbstractBuildingSubdivisionPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractBuildingSubdivisionPropertyIteratorLib> = AbstractBuildingSubdivisionPropertyIteratorLib::class.java
        internal val lib: AbstractBuildingSubdivisionPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractBuildingSubdivisionProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractBuildingSubdivisionProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractBuildingSubdivisionProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}