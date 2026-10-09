package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCityObjectKindRefIteratorLib: Library {
    fun ecitygml_AbstractCityObjectKindRefIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractCityObjectKindRefIterator_next(handle: Pointer): Pointer?
}
typealias AbstractCityObjectKindRefIteratorIteratorItem = AbstractCityObjectKindRef?
/** Iterates over city objects of a city model, which it borrows.
*/
class AbstractCityObjectKindRefIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractCityObjectKindRef?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractCityObjectKindRefIteratorCleaner(val handle: Pointer, val lib: AbstractCityObjectKindRefIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCityObjectKindRefIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCityObjectKindRefIterator.AbstractCityObjectKindRefIteratorCleaner(handle, AbstractCityObjectKindRefIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCityObjectKindRefIteratorLib> = AbstractCityObjectKindRefIteratorLib::class.java
        internal val lib: AbstractCityObjectKindRefIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractCityObjectKindRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKindRefIterator_next(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = AbstractCityObjectKindRef(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractCityObjectKindRef?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}